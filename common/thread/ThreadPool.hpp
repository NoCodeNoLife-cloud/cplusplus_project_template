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
    std::mutex queueMutex_;
    std::atomic<bool> stop_;
    std::atomic<size_t> coreThreadCount_;
    std::atomic<size_t> activeThreadCount_;
    size_t maxThreadCount_;
    size_t maxQueueSize_;
    std::chrono::milliseconds threadIdleTime_;

    auto Worker() -> void;

    auto AddWorker() -> bool;
  };
}
