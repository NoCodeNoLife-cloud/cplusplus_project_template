#pragma once
#include <atomic>

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
}
