#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <unordered_map>
#include <cstdint>

namespace fox
{
    /// @brief A class that executes tasks with a specified delay.
    /// @tparam ResultType The type of the result returned by the task.
    template <typename ResultType>
    class DelayedTaskActuator
    {
    public:
        /// @brief Schedules a task to be executed after a specified delay.
        /// @param delayMs The delay in milliseconds before the task is executed.
        /// @param task The task to be executed.
        /// @return The ID of the scheduled task.
        [[nodiscard]] auto scheduleTask(int32_t delayMs, std::function<ResultType()> task) -> int32_t;

        /// @brief Retrieves the result of a scheduled task.
        /// @param taskId The ID of the task whose result is to be retrieved.
        /// @return A future object that will hold the result of the task.
        [[nodiscard]] auto getTaskResult(int32_t taskId) -> std::future<ResultType>;

    private:
        mutable std::mutex mutex_{};
        std::condition_variable cv_{};
        std::unordered_map<int32_t, std::future<ResultType>> results_{};
        int32_t nextTaskId_{0};
    };
}
