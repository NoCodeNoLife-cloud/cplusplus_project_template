#include "src/thread/ThreadPool.hpp"

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
    ThreadPool::ThreadPool(const size_t core_threads, const size_t max_threads, const size_t queue_size,
                           const std::chrono::milliseconds idle_time) noexcept :
        core_thread_count_(core_threads), max_thread_count_(max_threads),
        max_queue_size_(queue_size), thread_idle_time_(idle_time)
    {
        for (size_t i = 0; i < core_thread_count_; ++i)
        {
            addWorker();
        }
    }

    ThreadPool::~ThreadPool()
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
            std::unique_lock lock(queue_mutex_);
            if (task_queue_.size() >= max_queue_size_)
            {
                throw std::runtime_error("Task queue is full");
            }
            task_queue_.emplace([task] { (*task)(); });
        }
        condition_.notify_one();
        return res;
    }

    auto ThreadPool::Shutdown() -> void
    {
        {
            std::unique_lock lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& worker : workers_)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    auto ThreadPool::ShutdownNow() -> void
    {
        {
            std::unique_lock lock(queue_mutex_);
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

    auto ThreadPool::worker() -> void
    {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock lock(queue_mutex_);
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

    auto ThreadPool::addWorker() -> bool
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
