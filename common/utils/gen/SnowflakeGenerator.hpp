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
  auto NextId() -> int64_t;

 private:
  int64_t last_timestamp_{-1};
  int64_t sequence_{0};
  int16_t machine_id_;
  std::mutex mutex_;
  static auto GetCurrentTimestamp() -> int64_t;
  static auto TilNextMillis(int64_t last_timestamp) -> int64_t;
};
}  // namespace common
