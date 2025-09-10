#pragma once
#include <mutex>
#include <random>

namespace fox {
/// @brief A utility class for exponential backoff algorithm.
/// @details This class implements an exponential backoff strategy,
///          where the delay time increases exponentially after each retry attempt.
///          It supports thread safety and customizable parameters such as initial delay,
///          multiplier, minimum delay, maximum delay cap, and maximum number of retries.
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
  ExponentialBackoff(const uint32_t max_retries, const double initial_delay, const double multiplier, const double min_delay, const double max_cap, const uint32_t seed, const bool thread_safe) : max_retries_(max_retries), initial_delay_(initial_delay), multiplier_(multiplier), min_delay_(min_delay), max_cap_(max_cap), rng_(seed), thread_safe_(thread_safe) {
    if (initial_delay <= 0) throw std::invalid_argument("Initial delay must be greater than 0.");
    if (multiplier <= 1) throw std::invalid_argument("Multiplier must be greater than 1.");
    if (min_delay < 0) throw std::invalid_argument("Minimum delay must be non-negative.");
    if (max_cap < 0) throw std::invalid_argument("Max cap must be non-negative.");
    if (min_delay > max_cap) throw std::invalid_argument("Minimum delay must not exceed max cap.");
    if (initial_delay < min_delay) throw std::invalid_argument("Initial delay must be greater than or equal to min_delay.");
  }

  /// @brief Get the next delay.
  /// @return The next delay
  auto getNextDelay() -> double {
    if (isExhausted()) {
      throw std::runtime_error("Max retries exceeded. Cannot get next delay.");
    }

    if (thread_safe_) {
      std::lock_guard lock(mutex_);
    }

    // Calculate max delay
    const double calculated_max_delay = initial_delay_ * std::pow(multiplier_, current_retry_);
    const double effective_max_delay = std::min(calculated_max_delay, max_cap_);
    const double effective_min_delay = std::min(min_delay_, effective_max_delay);
    std::uniform_real_distribution dist(effective_min_delay, effective_max_delay);
    const double delay = dist(rng_);

    // Increment retry count
    if (thread_safe_) {
      std::lock_guard lock(mutex_);
    }
    current_retry_++;
    return delay;
  }

  /// @brief Reset the backoff.
  auto reset() -> void {
    if (thread_safe_) {
      std::lock_guard lock(mutex_);
    }
    current_retry_ = 0;
  }

  /// @brief Check if the backoff is exhausted.
  /// @return True if the backoff is exhausted, false otherwise
  auto isExhausted() const -> bool {
    if (thread_safe_) {
      std::lock_guard lock(mutex_);
    }
    return current_retry_ >= max_retries_;
  }

  /// @brief Get the maximum number of retries.
  /// @return The maximum number of retries
  auto getMaxRetries() const -> uint32_t { return max_retries_; }

 private:
  uint32_t current_retry_{0};
  const uint32_t max_retries_{0};
  const double initial_delay_{0.0};
  const double multiplier_{0.0};
  const double min_delay_{0.0};
  const double max_cap_{std::numeric_limits<double>::infinity()};
  std::mt19937 rng_;
  mutable std::mutex mutex_;
  const bool thread_safe_{false};
};
}  // namespace fox
