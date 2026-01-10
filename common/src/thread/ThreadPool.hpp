#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>
#include <type_traits>

namespace common
{
    /// @brief A thread pool implementation that manages a pool of worker threads to execute tasks asynchronously
    /// The ThreadPool class provides a way to manage a collection of threads and distribute work among them.
    /// It supports dynamic thread creation up to a maximum limit, and allows for graceful or immediate shutdown.
    class ThreadPool
    {
    public:
        /// @brief Construct a ThreadPool with specified parameters
        /// @param core_threads The number of core threads to maintain
        /// @param max_threads The maximum number of threads allowed
        /// @param queue_size The maximum size of the task queue
        /// @param idle_time The time after which excess threads will be terminated
        ThreadPool(size_t core_threads, size_t max_threads, size_t queue_size, std::chrono::milliseconds idle_time) noexcept;

        /// @brief Destructor that gracefully shuts down the thread pool
        ~ThreadPool();

        /// @brief Submit a task to the thread pool
        /// @tparam F The type of the function to be executed
        /// @tparam Args The types of the arguments to pass to the function
        /// @param f The function to be executed
        /// @param args The arguments to pass to the function
        /// @return A future that will hold the result of the function execution
        /// @throws std::runtime_error If the task queue is full
        template <class F, class... Args>
        [[nodiscard]] auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

        /// @brief Gracefully shutdown the thread pool, waiting for all tasks to complete
        auto Shutdown() -> void;

        /// @brief Immediately shutdown the thread pool, abandoning any remaining tasks
        auto ShutdownNow() -> void;

    private:
        std::vector<std::thread> workers_{};
        std::queue<std::function<void()>> task_queue_{};
        std::condition_variable condition_{};
        std::mutex queue_mutex_{};
        std::atomic<bool> stop_{false};
        std::atomic<size_t> core_thread_count_{0};
        std::atomic<size_t> active_thread_count_{0};
        size_t max_thread_count_{0};
        size_t max_queue_size_{0};
        std::chrono::milliseconds thread_idle_time_{};

        /// @brief Worker thread function that processes tasks from the queue
        auto worker() -> void;

        /// @brief Add a new worker thread to the pool if possible
        /// @return true if a new worker was added, false otherwise
        auto addWorker() -> bool;
    };
}
