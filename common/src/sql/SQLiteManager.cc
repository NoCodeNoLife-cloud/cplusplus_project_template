#include "SQLiteManager.hpp"
#include <glog/logging.h>

namespace common
{
    SQLiteManager::SQLiteManager()
        : db_(nullptr, &sqlite3_close)
    {
    }

    SQLiteManager::SQLiteManager(const std::string& db_path)
        : db_(nullptr, &sqlite3_close)
    {
        createDatabase(db_path);
    }

    SQLiteManager::~SQLiteManager()
    {
        closeDatabase();
    }

    void SQLiteManager::createDatabase(const std::string& db_path)
    {
        if (db_)
        {
            closeDatabase();
        }

        sqlite3* raw_db;
        if (sqlite3_open(db_path.c_str(), &raw_db) != SQLITE_OK)
        {
            throw std::runtime_error("Database open failed: " + std::string(sqlite3_errmsg(raw_db)));
        }

        db_.reset(raw_db);
        LOG(INFO) << "Database connection established: " << db_path;
    }

    void SQLiteManager::closeDatabase()
    {
        if (db_)
        {
            db_.reset(nullptr);
            LOG(INFO) << "Database connection closed";
        }
    }

    auto SQLiteManager::exec(const std::string& sql, const std::vector<std::string>& params) const -> int
    {
        if (!db_)
        {
            throw std::runtime_error("Database not open");
        }

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db_.get(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            throw std::runtime_error("SQL prepare failed: " + std::string(sqlite3_errmsg(db_.get())));
        }

        // Bind parameters
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (sqlite3_bind_text(stmt, static_cast<int>(i + 1), params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
            {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Parameter binding failed");
            }
        }

        // Execute statement
        const int rc = sqlite3_step(stmt);
        const int affected = sqlite3_changes(db_.get());

        // Cleanup
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            throw std::runtime_error("SQL execution failed: " + std::string(sqlite3_errmsg(db_.get())));
        }

        return affected;
    }

    auto SQLiteManager::query(const std::string& sql, const std::vector<std::string>& params) const -> std::vector<std::vector<std::string>>
    {
        if (!db_)
        {
            throw std::runtime_error("Database not open");
        }

        std::vector<std::vector<std::string>> results;
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db_.get(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            throw std::runtime_error("Query preparation failed: " + std::string(sqlite3_errmsg(db_.get())));
        }

        // Bind parameters
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (sqlite3_bind_text(stmt, static_cast<int>(i + 1), params[i].c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
            {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Parameter binding failed");
            }
        }

        // Process results
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::vector<std::string> row;
            const int cols = sqlite3_column_count(stmt);

            for (int i = 0; i < cols; ++i)
            {
                const unsigned char* col = sqlite3_column_text(stmt, i);
                row.emplace_back(col ? reinterpret_cast<const char*>(col) : "NULL");
            }
            results.push_back(row);
        }

        sqlite3_finalize(stmt);
        return results;
    }

    auto SQLiteManager::isOpen() const -> bool { return db_ != nullptr; }
} // common
