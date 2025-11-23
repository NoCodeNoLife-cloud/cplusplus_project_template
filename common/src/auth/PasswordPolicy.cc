#include "PasswordPolicy.hpp"

namespace common
{
    PasswordPolicy::PasswordPolicy(const size_t min_length, const size_t max_length, const bool require_uppercase, const bool require_lowercase, const bool require_digits, const bool require_special, const size_t max_login_attempts)
        : min_length_(min_length),
          max_length_(max_length),
          require_uppercase_(require_uppercase),
          require_lowercase_(require_lowercase),
          require_digits_(require_digits),
          require_special_(require_special),
          max_login_attempts_(max_login_attempts)
    {
    }

    auto PasswordPolicy::validate(const std::string& password) const -> bool
    {
        if (password.length() < min_length_ || password.length() > max_length_)
        {
            return false;
        }

        bool has_upper = require_uppercase_ ? false : true;
        bool has_lower = require_lowercase_ ? false : true;
        bool has_digit = require_digits_ ? false : true;
        bool has_special = require_special_ ? false : true;

        for (const char c : password)
        {
            if (std::isupper(static_cast<unsigned char>(c))) has_upper = true;
            if (std::islower(static_cast<unsigned char>(c))) has_lower = true;
            if (std::isdigit(static_cast<unsigned char>(c))) has_digit = true;
            if (std::ispunct(static_cast<unsigned char>(c)) || std::isspace(static_cast<unsigned char>(c))) has_special = true;
        }

        return has_upper && has_lower && has_digit && has_special;
    }

    auto PasswordPolicy::set_min_length(const size_t length) -> void
    {
        min_length_ = length;
    }

    auto PasswordPolicy::set_max_length(const size_t length) -> void
    {
        max_length_ = length;
    }

    auto PasswordPolicy::set_require_uppercase(const bool require) -> void
    {
        require_uppercase_ = require;
    }

    auto PasswordPolicy::set_require_lowercase(const bool require) -> void
    {
        require_lowercase_ = require;
    }

    auto PasswordPolicy::set_require_digits(const bool require) -> void
    {
        require_digits_ = require;
    }

    auto PasswordPolicy::set_require_special(const bool require) -> void
    {
        require_special_ = require;
    }
} // common
