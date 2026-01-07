#include "src/thread/DelayedTaskActuator.hpp"

#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <cstdint>

namespace common
{
    template <typename ResultType>
    auto DelayedTaskActuator<ResultType>::scheduleTask(const int32_t delayMs,
                                                       std::function<ResultType()> task) -> int32_t
    {
        std::lock_guard lock(mutex_);
        const int32_t taskId = nextTaskId_++;
        std::packaged_task<ResultType()> packagedTask(std::move(task));
        std::future<ResultType> result = packagedTask.get_future();

        std::thread([this, delayMs, packagedTask = std::move(packagedTask)]() mutable
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            packagedTask();
            {
                std::lock_guard lock1(mutex_);
                cv_.notify_one();
            }
        }).detach();

        results_[taskId] = std::move(result);
        return taskId;
    }

    template <typename ResultType>
    auto DelayedTaskActuator<ResultType>::getTaskResult(const int32_t taskId) -> std::future<ResultType>
    {
        std::unique_lock lock(mutex_);

        cv_.wait(lock, [this, taskId] { return results_.contains(taskId); });

        std::future<ResultType> result = std::move(results_[taskId]);
        results_.erase(taskId);
        return result;
    }
}
