#include "src/thread/SpinlockMutex.hpp"

#include <atomic>
#include <thread>

namespace fox
{
    SpinlockMutex::SpinlockMutex() noexcept = default;

    auto SpinlockMutex::lock() noexcept -> void
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    auto SpinlockMutex::unlock() noexcept -> void
    {
        flag_.clear(std::memory_order_release);
    }
}
