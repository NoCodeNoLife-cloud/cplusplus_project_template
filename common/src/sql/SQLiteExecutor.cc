#include "SQLiteExecutor.hpp"
#include <glog/logging.h>

namespace common
{
    SQLiteExecutor::SQLiteExecutor(const std::string& db_path)
        : db(nullptr)
    {
        if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK)
        {
            throw std::runtime_error("Database open failed: " + std::string(sqlite3_errmsg(db)));
        }
        LOG(INFO) << "Database connection established: " << db_path;
    }

    SQLiteExecutor::~SQLiteExecutor()
    {
        if (db)
        {
            sqlite3_close(db);
            LOG(INFO) << "Database connection closed";
        }
    }

    auto SQLiteExecutor::exec(const std::string& sql,
                              const std::vector<std::string>& params) const
        -> int
    {
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            throw std::runtime_error("SQL prepare failed: " + std::string(sqlite3_errmsg(db)));
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
        const int affected = sqlite3_changes(db);

        // Cleanup
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            throw std::runtime_error("SQL execution failed: " + std::string(sqlite3_errmsg(db)));
        }

        return affected;
    }

    auto SQLiteExecutor::query(const std::string& sql,
                               const std::vector<std::string>& params) const
        -> std::vector<std::vector<std::string>>
    {
        std::vector<std::vector<std::string>> results;
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            throw std::runtime_error("Query preparation failed: " + std::string(sqlite3_errmsg(db)));
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
} // common
