#pragma once
#include <atomic>

namespace framework::thread {
  class SpinlockMutex {
  public:
    SpinlockMutex();

    auto lock() -> void;

    auto unlock() -> void;

  private:
    std::atomic_flag flag_;
  };
} // namespace framework::thread
