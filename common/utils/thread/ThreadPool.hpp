#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>
#include <stdexcept>
#include <type_traits>

namespace fox
{
    class ThreadPool
    {
    public:
        ThreadPool(size_t core_threads, size_t max_threads, size_t queue_size,
                   std::chrono::milliseconds idle_time) noexcept;

        ~ThreadPool();

        /// @brief Submit a task to the thread pool
        /// @tparam F The type of the function to be executed
        /// @tparam Args The types of the arguments to pass to the function
        /// @param f The function to be executed
        /// @param args The arguments to pass to the function
        /// @return A future that will hold the result of the function execution
        template <class F, class... Args>
        [[nodiscard]] auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

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

    inline ThreadPool::ThreadPool(const size_t core_threads, const size_t max_threads, const size_t queue_size,
                                  const std::chrono::milliseconds idle_time) noexcept : stop_(false),
        core_thread_count_(core_threads), active_thread_count_(0),
        max_thread_count_(max_threads), max_queue_size_(queue_size),
        thread_idle_time_(idle_time)
    {
        for (size_t i = 0; i < core_thread_count_; ++i)
        {
            addWorker();
        }
    }

    inline ThreadPool::~ThreadPool()
    {
        Shutdown();
    }

    template <class F, class... Args>
    auto ThreadPool::Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
    {
        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (task_queue_.size() >= max_queue_size_)
            {
                throw std::runtime_error("Task queue is full");
            }
            task_queue_.emplace([task] { (*task)(); });
        }
        condition_.notify_one();
        return res;
    }

    inline auto ThreadPool::Shutdown() -> void
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& worker : workers_)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    inline auto ThreadPool::ShutdownNow() -> void
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
            while (!task_queue_.empty())
            {
                task_queue_.pop();
            }
        }
        condition_.notify_all();
        for (std::thread& worker : workers_)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    inline auto ThreadPool::worker() -> void
    {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                condition_.wait_for(lock, thread_idle_time_, [this] { return stop_ || !task_queue_.empty(); });
                if (stop_ && task_queue_.empty())
                    return;
                if (task_queue_.empty() && active_thread_count_ > core_thread_count_)
                {
                    --active_thread_count_;
                    return;
                }
                if (!task_queue_.empty())
                {
                    task = std::move(task_queue_.front());
                    task_queue_.pop();
                }
            }
            if (task)
            {
                task();
            }
        }
    }

    inline auto ThreadPool::addWorker() -> bool
    {
        if (active_thread_count_ >= max_thread_count_)
        {
            return false;
        }
        ++active_thread_count_;
        workers_.emplace_back([this] { worker(); });
        return true;
    }
}
