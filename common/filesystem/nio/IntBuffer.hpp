#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
class IntBuffer final : public IBuffer {
 public:
  explicit IntBuffer(size_t capacity);

  /// @brief Get the current element and advance the position.
  /// @return The current element.
  auto get() -> int32_t;

  /// @brief Get the element at the specified index.
  /// @param index The index of the element to get.
  /// @return The element at the specified index.
  [[nodiscard]] auto get(size_t index) const -> int32_t;

  /// @brief Put the specified value at the current position and advance the position.
  /// @param value The value to put.
  auto put(int32_t value) -> void;

  /// @brief Put the specified value at the specified index.
  /// @param index The index at which to put the value.
  /// @param value The value to put.
  auto put(size_t index, int32_t value) -> void;

 private:
  std::vector<int32_t> buffer_{};
};
}  // namespace common
