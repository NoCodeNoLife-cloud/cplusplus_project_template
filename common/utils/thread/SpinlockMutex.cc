#include "SpinlockMutex.hpp"

#include <thread>

namespace fox {
SpinlockMutex::SpinlockMutex() = default;

auto SpinlockMutex::lock() -> void {
  while (flag_.test_and_set(std::memory_order_acquire)) {
    std::this_thread::yield();
  }
}

auto SpinlockMutex::unlock() -> void { flag_.clear(std::memory_order_release); }
}  // namespace fox
