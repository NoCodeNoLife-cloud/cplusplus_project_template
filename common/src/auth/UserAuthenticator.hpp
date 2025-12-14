#pragma once
#include <mutex>
#include <regex>
#include <unordered_map>
#include <optional>

#include "PasswordPolicy.hpp"
#include "UserCredentials.hpp"
#include "src/sql/PasswordSQL.hpp"

namespace common
{
    /// @brief Main authentication class providing user management and verification
    class UserAuthenticator
    {
    public:
        /// @brief Constructor with database path and optional custom password policy
        /// @param db_path Path to SQLite database file
        /// @param policy Custom password policy (default: standard policy)
        explicit UserAuthenticator(const std::string& db_path,
                                  const PasswordPolicy& policy = PasswordPolicy());

        /// @brief Register new user with username and password
        /// @param username User identifier to register
        /// @param password Plaintext password for new account
        /// @return true if registration successful
        /// @throws AuthenticationException if username invalid, exists, or password fails policy
        bool register_user(const std::string& username,
                           const std::string& password);

        /// @brief Authenticate user with username and password
        /// @param username User identifier
        /// @param password Plaintext password to verify
        /// @return true if authentication successful
        /// @throws AuthenticationException if user not found, password incorrect, or account locked
        bool authenticate(const std::string& username,
                          const std::string& password);

        /// @brief Change user password after verifying current password
        /// @param username User identifier
        /// @param current_password Current plaintext password for verification
        /// @param new_password New plaintext password to set
        /// @return true if password changed successfully
        /// @throws AuthenticationException if current password incorrect or new password fails policy
        bool change_password(const std::string& username,
                             const std::string& current_password,
                             const std::string& new_password);

        /// @brief Reset user password (administrative function)
        /// @param username User identifier
        /// @param new_password New plaintext password to set
        /// @return true if password reset successful
        /// @throws AuthenticationException if user not found or new password fails policy
        bool reset_password(const std::string& username,
                            const std::string& new_password);

        /// @brief Check if user exists in the system
        /// @param username User identifier to check
        /// @return true if user exists, false otherwise
        bool user_exists(const std::string& username) const;

        /// @brief Delete user from the system
        /// @param username User identifier to delete
        /// @return true if user deleted successfully
        bool delete_user(const std::string& username);

        /// @brief Set custom password policy
        /// @param policy New password policy configuration
        void set_password_policy(const PasswordPolicy& policy);

        /// @brief Get reference to the users map for administrative operations
        /// @return Reference to the users map
        auto get_users()
            -> std::unordered_map<std::string, std::unique_ptr<UserCredentials>>&;

        /// @brief Get reference to the mutex protecting the users map
        /// @return Reference to the users mutex
        auto get_users_mutex() const
            -> std::mutex&;

    private:
        /// @brief Validate username format against security requirements
        /// @param username Username string to validate
        /// @return true if username format is valid, false otherwise
        static bool validate_username(const std::string& username);

        /// @brief Load user credentials from database
        /// @param username User identifier to load
        /// @return User credentials if found, nullopt otherwise
        auto load_user_from_db(const std::string& username) const
            -> std::optional<UserCredentials>;

        PasswordPolicy password_policy_;
        std::unordered_map<std::string, std::unique_ptr<UserCredentials>> users_;
        mutable std::mutex users_mutex_;
        server_app::PasswordSQL password_sql_;
    };
} // common
