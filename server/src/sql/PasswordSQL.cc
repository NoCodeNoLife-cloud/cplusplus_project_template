#include "PasswordSQL.hpp"
#include <glog/logging.h>

namespace server_app
{
    PasswordSQL::PasswordSQL(const std::string& db_path) noexcept(false)
        : sqlite_manager_(db_path)
    {
        /// @brief Create users table if not exists during initialization
        constexpr auto create_table_sql = R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )";

        [[maybe_unused]] const auto result = sqlite_manager_.exec(create_table_sql);
        LOG(INFO) << "PasswordSQL initialized with database: " << db_path;
    }

    auto PasswordSQL::RegisterUser(const std::string& username,
                                   const std::string& password) const noexcept
        -> bool
    {
        try
        {
            constexpr auto insert_sql = R"(
                INSERT INTO users (username, password) VALUES (?, ?);
            )";

            [[maybe_unused]] const auto result = sqlite_manager_.exec(insert_sql, {username, password});
            LOG(INFO) << "User registered successfully: " << username;
            return true;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to register user " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::AuthenticateUser(const std::string& username,
                                       const std::string& password) const noexcept
        -> bool
    {
        try
        {
            constexpr auto select_sql = R"(
                SELECT 1 FROM users WHERE username = ? AND password = ?;
            )";

            const auto result = sqlite_manager_.query(select_sql, {username, password});
            return !result.empty();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Authentication failed for user " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::ChangePassword(const std::string& username,
                                     const std::string& old_password,
                                     const std::string& new_password) const noexcept
        -> bool
    {
        try
        {
            /// @brief First check if the old credentials are correct
            if (!AuthenticateUser(username, old_password))
            {
                LOG(WARNING) << "Password change failed: invalid old credentials for user " << username;
                return false;
            }

            constexpr auto update_sql = R"(
                UPDATE users SET password = ? WHERE username = ?;
            )";

            if (const int affected_rows = sqlite_manager_.exec(update_sql, {new_password, username}); affected_rows > 0)
            {
                LOG(INFO) << "Password changed successfully for user: " << username;
                return true;
            }

            LOG(WARNING) << "Password change affected no rows for user: " << username;
            return false;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to change password for user " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::ResetPassword(const std::string& username,
                                    const std::string& new_password) const noexcept
        -> bool
    {
        try
        {
            constexpr auto update_sql = R"(
                UPDATE users SET password = ? WHERE username = ?;
            )";

            if (const int affected_rows = sqlite_manager_.exec(update_sql, {new_password, username}); affected_rows > 0)
            {
                LOG(INFO) << "Password reset successfully for user: " << username;
                return true;
            }

            LOG(WARNING) << "Password reset affected no rows for user: " << username;
            return false;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to reset password for user " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::DeleteUser(const std::string& username) const noexcept
        -> bool
    {
        try
        {
            constexpr auto delete_sql = R"(
                DELETE FROM users WHERE username = ?;
            )";

            if (const int affected_rows = sqlite_manager_.exec(delete_sql, {username}); affected_rows > 0)
            {
                LOG(INFO) << "User deleted successfully: " << username;
                return true;
            }

            LOG(WARNING) << "User deletion affected no rows for user: " << username;
            return false;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to delete user " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::UserExists(const std::string& username) const noexcept
        -> bool
    {
        try
        {
            constexpr auto select_sql = R"(
                SELECT 1 FROM users WHERE username = ?;
            )";

            const auto result = sqlite_manager_.query(select_sql, {username});
            return !result.empty();
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to check if user exists " << username << ": " << e.what();
            return false;
        }
    }

    auto PasswordSQL::GetUser(const std::string& username) const noexcept
        -> std::string
    {
        try
        {
            constexpr auto select_sql = R"(
                SELECT username FROM users WHERE username = ?;
            )";

            if (const auto result = sqlite_manager_.query(select_sql, {username}); !result.empty() && !result[0].empty())
            {
                return result[0][0];
            }

            return {};
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to get user " << username << ": " << e.what();
            return {};
        }
    }

    auto PasswordSQL::GetAllUsers() const noexcept
        -> std::vector<std::string>
    {
        try
        {
            constexpr auto select_sql = R"(
                SELECT username FROM users ORDER BY username;
            )";

            const auto result = sqlite_manager_.query(select_sql);
            std::vector<std::string> users;

            for (const auto& row : result)
            {
                if (!row.empty())
                {
                    users.push_back(row[0]);
                }
            }

            return users;
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Failed to get all users: " << e.what();
            return {};
        }
    }
}
