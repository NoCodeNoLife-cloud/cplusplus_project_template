#pragma once
#include <mutex>
#include <random>

namespace common {
class ExponentialBackoff {
 public:
  /// @brief Construct a new Exponential Backoff object
  /// @param max_retries Maximum number of retries
  /// @param initial_delay Initial delay (unit: milliseconds)
  /// @param multiplier Backoff multiplier (>1)
  /// @param min_delay Minimum delay (unit: milliseconds, optional, default is 0)
  /// @param max_cap Maximum delay limit (unit: milliseconds, optional, default is infinity)
  /// @param seed Random number seed (for testing, optional, default use random_device)
  /// @param thread_safe thread_safe whether to enable thread safety mode (optional, default false)
  ExponentialBackoff(unsigned int max_retries, double initial_delay, double multiplier, double min_delay = 0.0, double max_cap = std::numeric_limits<double>::infinity(), unsigned int seed = std::random_device{}(), bool thread_safe = false);

  /// @brief Get the next delay.
  /// @return The next delay
  auto getNextDelay() -> double;

  /// @brief Reset the backoff.
  auto reset() -> void;

  /// @brief Check if the backoff is exhausted.
  /// @return True if the backoff is exhausted, false otherwise
  auto isExhausted() const -> bool;

  /// @brief Get the maximum number of retries.
  /// @return The maximum number of retries
  auto getMaxRetries() const -> unsigned int;

 private:
  unsigned int current_retry_{0};
  const unsigned int max_retries_{0};
  const double initial_delay_{0.0};
  const double multiplier_{0.0};
  const double min_delay_{0.0};
  const double max_cap_{std::numeric_limits<double>::infinity()};
  std::mt19937 rng_;
  mutable std::mutex mutex_;
  const bool thread_safe_{false};
};
}  // namespace common
