#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
class LongBuffer final : public IBuffer {
 public:
  explicit LongBuffer(std::size_t capacity);

  /// @brief Get the current value from the buffer
  /// @return The current value
  auto get() -> int64_t;

  /// @brief Put a value into the buffer
  /// @param value The value to put
  auto put(int64_t value) -> void;

 private:
  std::vector<int64_t> buffer_{};
};
}  // namespace common
