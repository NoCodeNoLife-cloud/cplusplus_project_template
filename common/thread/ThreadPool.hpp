#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace common::thread
{
    class ThreadPool
    {
    public:
        ThreadPool(const size_t core_threads, const size_t max_threads, const size_t queue_size, const std::chrono::milliseconds idle_time) : stop_(false), coreThreadCount_(core_threads), maxThreadCount_(max_threads), maxQueueSize_(queue_size), threadIdleTime_(idle_time)
        {
            for (size_t i = 0; i < coreThreadCount_; ++i)
            {
                AddWorker();
            }
        }

        ~ThreadPool()
        {
            Shutdown();
        }

        template <class F, class... Args>
        auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
        {
            using return_type = std::invoke_result_t<F, Args...>;
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            std::future<return_type> res = task->get_future();
            {
                std::unique_lock lock(queueMutex_);
                if (task_queue_.size() >= maxQueueSize_)
                {
                    throw std::runtime_error("Task queue is full");
                }
                task_queue_.emplace([task]
                {
                    (*task)();
                });
            }
            condition_.notify_one();
            return res;
        }

        auto Shutdown() -> void
        {
            {
                std::unique_lock lock(queueMutex_);
                stop_ = true;
            }
            condition_.notify_all();
            for (std::thread& worker : workers_)
            {
                if (worker.joinable()) worker.join();
            }
        }

        auto ShutdownNow() -> void
        {
            {
                std::unique_lock lock(queueMutex_);
                stop_ = true;
                while (!task_queue_.empty())
                {
                    task_queue_.pop();
                }
            }
            condition_.notify_all();
            for (std::thread& worker : workers_)
            {
                if (worker.joinable()) worker.join();
            }
        }

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

        auto Worker() -> void
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock lock(queueMutex_);
                    condition_.wait_for(lock, threadIdleTime_, [this]
                    {
                        return stop_ || !task_queue_.empty();
                    });
                    if (stop_ && task_queue_.empty()) return;
                    if (task_queue_.empty() && activeThreadCount_ > coreThreadCount_)
                    {
                        --activeThreadCount_;
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

        auto AddWorker() -> bool
        {
            if (activeThreadCount_ >= maxThreadCount_)
            {
                return false;
            }
            ++activeThreadCount_;
            workers_.emplace_back([this]
            {
                Worker();
            });
            return true;
        }
    };
}
