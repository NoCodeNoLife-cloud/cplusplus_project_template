#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace common {
class ThreadPool {
 public:
  ThreadPool(size_t core_threads, size_t max_threads, size_t queue_size, std::chrono::milliseconds idle_time);
  ~ThreadPool();

  /// @brief Submit a task to the thread pool
  /// @tparam F The type of the function to be executed
  /// @tparam Args The types of the arguments to pass to the function
  /// @param f The function to be executed
  /// @param args The arguments to pass to the function
  /// @return A future that will hold the result of the function execution
  template <class F, class... Args>
  auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

  /// @brief Gracefully shutdown the thread pool, waiting for all tasks to complete
  auto Shutdown() -> void;

  /// @brief Immediately shutdown the thread pool, abandoning any remaining tasks
  auto ShutdownNow() -> void;

 private:
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> task_queue_;
  std::condition_variable condition_;
  std::mutex queue_mutex_;
  std::atomic<bool> stop_;
  std::atomic<size_t> core_thread_count_;
  std::atomic<size_t> active_thread_count_;
  size_t max_thread_count_;
  size_t max_queue_size_;
  std::chrono::milliseconds thread_idle_time_;

  /// @brief Worker thread function that processes tasks from the queue
  auto worker() -> void;

  /// @brief Add a new worker thread to the pool if possible
  /// @return true if a new worker was added, false otherwise
  auto addWorker() -> bool;
};
}  // namespace common
