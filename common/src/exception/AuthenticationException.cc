#include "AuthenticationException.hpp"

namespace common
{
    AuthenticationException::AuthenticationException(const std::string& message)
        : std::runtime_error(message)
    {
    }
} // common
