#pragma once
#include <sqlite3.h>
#include <vector>
#include <string>
#include <stdexcept>

namespace common
{
    /// @brief SQLite database executor with RAII management and parameterized queries
    class SQLiteExecutor
    {
    public:
        /// @brief Constructor that opens the database file (creates it if not exists)
        /// @param db_path Path to the SQLite database file
        /// @throws std::runtime_error if database cannot be opened
        explicit SQLiteExecutor(const std::string& db_path);

        /// @brief Destructor that automatically closes the database connection
        ~SQLiteExecutor();

        /// @brief Executes non-query SQL statements (INSERT/UPDATE/DELETE)
        /// @param sql SQL statement to execute
        /// @param params Parameter values for prepared statement
        /// @return Number of affected rows
        /// @throws std::runtime_error if execution fails
        [[nodiscard]] auto exec(const std::string& sql,
                                const std::vector<std::string>& params = {}) const
            -> int;

        /// @brief Executes a query and returns results as a 2D string vector
        /// @param sql SQL query to execute
        /// @param params Parameter values for prepared statement
        /// @return Query results in format [rows][columns]
        /// @throws std::runtime_error if query fails
        [[nodiscard]] auto query(const std::string& sql,
                                 const std::vector<std::string>& params = {}) const
            -> std::vector<std::vector<std::string>>;

    private:
        sqlite3* db;
    };
} // common
