#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
class FloatBuffer final : public IBuffer {
 public:
  explicit FloatBuffer(size_t capacity);

  /// @brief Allocates a new FloatBuffer with the specified capacity.
  /// @param capacity The capacity of the buffer.
  /// @return A new FloatBuffer instance.
  static auto allocate(size_t capacity) -> FloatBuffer;

  /// @brief Puts a single float value into the buffer.
  /// @param value The float value to put.
  auto put(float value) -> void;

  /// @brief Puts a vector of float values into the buffer.
  /// @param values The vector of float values to put.
  auto put(const std::vector<float>& values) -> void;

  /// @brief Gets a single float value from the buffer.
  /// @return The float value retrieved.
  auto get() -> float;

  /// @brief Gets a vector of float values from the buffer.
  /// @param length The number of elements to retrieve.
  /// @return A vector containing the retrieved float values.
  auto get(size_t length) -> std::vector<float>;

 private:
  std::vector<float> buffer_{};
};
}  // namespace common
