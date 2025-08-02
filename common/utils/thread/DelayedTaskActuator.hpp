#pragma once
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace common {
template <typename ResultType>
class DelayedTaskActuator {
 public:
  auto scheduleTask(int delayMs, std::function<ResultType()> task) -> int;
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
