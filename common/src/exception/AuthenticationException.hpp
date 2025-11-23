#pragma once
#include <stdexcept>

namespace common
{
    /// @brief Custom exception class for authentication-related errors
    class AuthenticationException : public std::runtime_error
    {
    public:
        /// @brief Constructor with error message
        /// @param message Error description
        explicit AuthenticationException(const std::string& message);
    };
}
