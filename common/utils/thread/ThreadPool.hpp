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
  template <class F, class... Args>
  auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;
  auto Shutdown() -> void;
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
  auto worker() -> void;
  auto addWorker() -> bool;
};
}  // namespace common
