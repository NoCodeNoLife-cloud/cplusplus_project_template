#pragma once
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace common {
/// @brief A class that executes tasks with a specified delay.
/// @tparam ResultType The type of the result returned by the task.
template <typename ResultType>
class DelayedTaskActuator {
 public:
  /// @brief Schedules a task to be executed after a specified delay.
  /// @param delayMs The delay in milliseconds before the task is executed.
  /// @param task The task to be executed.
  /// @return The ID of the scheduled task.
  auto scheduleTask(int delayMs, std::function<ResultType()> task) -> int;

  /// @brief Retrieves the result of a scheduled task.
  /// @param taskId The ID of the task whose result is to be retrieved.
  /// @return A future object that will hold the result of the task.
  auto getTaskResult(int taskId) -> std::future<ResultType>;

 private:
  mutable std::mutex mutex_;
  std::condition_variable cv_;
  std::unordered_map<int, std::future<ResultType>> results_;
  int nextTaskId_{0};
};

template <typename ResultType>
auto DelayedTaskActuator<ResultType>::scheduleTask(int delayMs, std::function<ResultType()> task) -> int {
  std::lock_guard lock(mutex_);
  int taskId = nextTaskId_++;
  std::packaged_task<ResultType()> packagedTask(task);
  std::future<ResultType> result = packagedTask.get_future();

  std::thread([this, delayMs, packagedTask = std::move(packagedTask)]() mutable {
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
auto DelayedTaskActuator<ResultType>::getTaskResult(int taskId) -> std::future<ResultType> {
  std::unique_lock lock(mutex_);

  cv_.wait(lock, [this, taskId] { return results_.contains(taskId); });

  std::future<ResultType> result = std::move(results_[taskId]);
  results_.erase(taskId);
  return result;
}
}  // namespace common
