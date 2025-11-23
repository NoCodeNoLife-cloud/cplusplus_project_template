#pragma once
#include <cstdint>

namespace service
{
    /// @brief Interface for application execution functionality.
    /// This interface defines the contract for classes that execute applications
    /// with command-line arguments. Implementations should handle the application
    /// lifecycle and return appropriate success/failure status.
    class IApplicationExecutor
    {
    public:
        virtual ~IApplicationExecutor() = default;

        /// @brief Executes the application with the given command-line arguments.
        /// @param argc The number of command-line arguments.
        /// @param argv An array of pointers to null-terminated strings representing the command-line arguments.
        /// @return true if the execution was successful, false otherwise.
        [[nodiscard]] virtual auto execute(int32_t argc,
                                           char* argv[]) noexcept
            -> bool = 0;
    };
} // namespace service
