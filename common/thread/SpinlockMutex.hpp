#pragma once
#include <atomic>
#include <thread>

namespace common::thread
{
    class SpinlockMutex
    {
    public:
        SpinlockMutex() = default;

        auto lock() -> void
        {
            while (flag_.test_and_set(std::memory_order_acquire))
            {
                std::this_thread::yield();
            }
        }

        auto unlock() -> void
        {
            flag_.clear(std::memory_order_release);
        }

    private:
        std::atomic_flag flag_;
    };
}
