#pragma once
#include <mutex>

namespace common {
enum class SnowflakeOption {
  machine_bits_ = 10,
  sequence_bits_ = 12,
  max_sequence_ = ~(-1LL << sequence_bits_),
  max_machine_id_ = ~(-1LL << 5),
  max_datacenter_id_ = ~(-1LL << 5),
};

class SnowflakeGenerator {
 public:
  SnowflakeGenerator(int16_t machine_id, int16_t datacenter_id);

  /// @brief Generate the next unique ID.
  /// @return The next unique ID.
  auto NextId() -> int64_t;

 private:
  int64_t last_timestamp_{-1};
  int64_t sequence_{0};
  int16_t machine_id_;
  std::mutex mutex_;

  /// @brief Get current timestamp in milliseconds.
  /// @return Current timestamp.
  static auto GetCurrentTimestamp() -> int64_t;

  /// @brief Wait until next millisecond when sequence number overflows.
  /// @param last_timestamp The last timestamp.
  /// @return The next valid timestamp.
  static auto TilNextMillis(int64_t last_timestamp) -> int64_t;
};
}  // namespace common
