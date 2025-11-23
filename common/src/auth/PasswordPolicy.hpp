#pragma once
#include <string>

namespace common
{
    /// @brief Password policy configuration class with configurable security rules
    class PasswordPolicy
    {
    public:
        /// @brief Constructor with default security parameters
        /// @param min_length Minimum password length (default: 8)
        /// @param max_length Maximum password length (default: 64)
        /// @param require_uppercase Require uppercase letters (default: true)
        /// @param require_lowercase Require lowercase letters (default: true)
        /// @param require_digits Require numeric digits (default: true)
        /// @param require_special Require special characters (default: true)
        /// @param max_login_attempts Maximum failed login attempts before lockout (default: 5)
        explicit PasswordPolicy(size_t min_length = 8,
                                size_t max_length = 64,
                                bool require_uppercase = true,
                                bool require_lowercase = true,
                                bool require_digits = true,
                                bool require_special = true,
                                size_t max_login_attempts = 5);

        /// @brief Validate password against current policy rules
        /// @param password Password string to validate
        /// @return true if password meets all requirements, false otherwise
        [[nodiscard]] auto validate(const std::string& password) const
            -> bool;

        /// @brief Set minimum password length requirement
        /// @param length New minimum length value
        auto set_min_length(size_t length)
            -> void;

        /// @brief Set maximum password length requirement
        /// @param length New maximum length value
        auto set_max_length(size_t length)
            -> void;

        /// @brief Enable/disable uppercase letter requirement
        /// @param require true to require uppercase letters
        auto set_require_uppercase(bool require)
            -> void;

        /// @brief Enable/disable lowercase letter requirement
        /// @param require true to require lowercase letters
        auto set_require_lowercase(bool require)
            -> void;

        /// @brief Enable/disable digit requirement
        /// @param require true to require numeric digits
        auto set_require_digits(bool require)
            -> void;

        /// @brief Enable/disable special character requirement
        /// @param require true to require special characters
        auto set_require_special(bool require)
            -> void;

    private:
        size_t min_length_;
        size_t max_length_;
        bool require_uppercase_;
        bool require_lowercase_;
        bool require_digits_;
        bool require_special_;
        size_t max_login_attempts_;
    };
} // common
