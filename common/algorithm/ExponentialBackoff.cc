#include "ExponentialBackoff.hpp"

namespace common {
ExponentialBackoff::ExponentialBackoff(const unsigned int max_retries, const double initial_delay, const double multiplier, const double min_delay, const double max_cap, const unsigned int seed, const bool thread_safe) : max_retries_(max_retries), initial_delay_(initial_delay), multiplier_(multiplier), min_delay_(min_delay), max_cap_(max_cap), rng_(seed), thread_safe_(thread_safe) {
  if (initial_delay <= 0) throw std::invalid_argument("Initial delay must be greater than 0.");
  if (multiplier <= 1) throw std::invalid_argument("Multiplier must be greater than 1.");
  if (min_delay < 0) throw std::invalid_argument("Minimum delay must be non-negative.");
  if (max_cap < 0) throw std::invalid_argument("Max cap must be non-negative.");
  if (min_delay > max_cap) throw std::invalid_argument("Minimum delay must not exceed max cap.");
  if (initial_delay < min_delay) throw std::invalid_argument("Initial delay must be greater than or equal to min_delay.");
}

auto ExponentialBackoff::getNextDelay() -> double {
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

auto ExponentialBackoff::reset() -> void {
  if (thread_safe_) {
    std::lock_guard lock(mutex_);
  }
  current_retry_ = 0;
}

auto ExponentialBackoff::isExhausted() const -> bool {
  if (thread_safe_) {
    std::lock_guard lock(mutex_);
  }
  return current_retry_ >= max_retries_;
}

auto ExponentialBackoff::getMaxRetries() const -> unsigned int { return max_retries_; }
}  // namespace common
