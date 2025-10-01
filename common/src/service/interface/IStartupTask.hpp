#pragma once

namespace service
{
    /// @brief Interface for startup tasks that need to be executed when the service starts.
    /// Startup tasks are used to perform initialization operations that are required
    /// for the service to function properly. These tasks are executed in the order
    /// they are registered.
    class IStartupTask
    {
    public:
        virtual ~IStartupTask() = default;

        /// @brief Executes the startup task.
        /// @return True if the task was executed successfully, false otherwise.
        [[nodiscard]] virtual auto execute() -> bool = 0;
    };
} // namespace service
