#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
class DoubleBuffer final : public IBuffer {
 public:
  explicit DoubleBuffer(size_t capacity);

  /// @brief Puts a single double value into the buffer.
  /// @param value The double value to be put into the buffer.
  /// @return Reference to the current DoubleBuffer object.
  auto put(double value) -> DoubleBuffer&;

  /// @brief Puts a vector of double values into the buffer.
  /// @param values The vector of double values to be put into the buffer.
  /// @return Reference to the current DoubleBuffer object.
  auto put(const std::vector<double>& values) -> DoubleBuffer&;

  /// @brief Gets a single double value from the buffer.
  /// @return The double value retrieved from the buffer.
  auto get() -> double;

 private:
  std::vector<double> buffer_;
};
}  // namespace common
