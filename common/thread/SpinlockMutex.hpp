#pragma once
#include <atomic>
#include <thread>

namespace common::thread
{
    class SpinlockMutex
    {
    public:
        SpinlockMutex();
        auto lock() -> void;
        auto unlock() -> void;
    private:
        std::atomic_flag flag_;
    };

    inline SpinlockMutex::SpinlockMutex() = default;

    inline auto SpinlockMutex::lock() -> void
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    inline auto SpinlockMutex::unlock() -> void
    {
        flag_.clear(std::memory_order_release);
    }
}
