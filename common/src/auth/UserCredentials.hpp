#pragma once
#include <chrono>
#include <string>

namespace common
{
    /// @brief User credentials storage with security features
    class UserCredentials
    {
    public:
        /// @brief Constructor for new user credentials
        /// @param username User identifier
        /// @param hashed_password Hashed password value
        /// @param salt Salt used for password hashing
        UserCredentials(std::string username,
                        std::string hashed_password,
                        std::string salt);

        /// @brief Get username
        /// @return Username string
        [[nodiscard]] auto get_username() const
            -> const std::string&;

        /// @brief Get hashed password
        /// @return Hashed password string
        [[nodiscard]] auto get_hashed_password() const
            -> const std::string&;

        /// @brief Get salt value
        /// @return Salt string used for hashing
        [[nodiscard]] auto get_salt() const
            -> const std::string&;

        /// @brief Get number of failed login attempts
        /// @return Count of failed attempts
        [[nodiscard]] auto get_failed_attempts() const
            -> size_t;

        /// @brief Increment failed login attempt counter
        auto increment_failed_attempts()
            -> void;

        /// @brief Reset failed attempt counter
        auto reset_failed_attempts()
            -> void;

        /// @brief Check if account is locked due to excessive failed attempts
        /// @return true if account is locked, false otherwise
        [[nodiscard]] auto is_locked() const
            -> bool;

    private:
        std::string username_;
        std::string hashed_password_;
        std::string salt_;
        size_t failed_attempts_;
        std::chrono::system_clock::time_point last_failed_attempt_;
    };
} // common
