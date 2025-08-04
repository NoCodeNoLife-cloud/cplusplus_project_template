#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
/// @brief A buffer for short integer (int16_t) data.
/// ShortBuffer provides a way to store, read, and write short integer data in a
/// sequential manner. It implements the IBuffer interface and supports operations
/// like get, put, and rewind.
class ShortBuffer final : public IBuffer {
 public:
  explicit ShortBuffer(size_t capacity);

  /// @brief Wraps an existing array of int16_t data into a ShortBuffer.
  /// @param data Pointer to the data to wrap.
  /// @param size Size of the data array.
  /// @return A new ShortBuffer instance wrapping the provided data.
  static auto wrap(const int16_t* data, size_t size) -> ShortBuffer;

  /// @brief Reads the next int16_t value from the buffer.
  /// @return The next int16_t value.
  auto get() -> int16_t;

  /// @brief Reads an int16_t value at the specified index.
  /// @param index Index of the value to read.
  /// @return The int16_t value at the specified index.
  [[nodiscard]] auto get(size_t index) const -> int16_t;

  /// @brief Writes an int16_t value to the buffer at the current position.
  /// @param value The value to write.
  auto put(int16_t value) -> void;

  /// @brief Writes an int16_t value to the buffer at the specified index.
  /// @param index Index where the value should be written.
  /// @param value The value to write.
  auto put(size_t index, int16_t value) -> void;

  /// @brief Resets the position of the buffer to zero.
  auto rewind() -> void override;

  /// @brief Returns a pointer to the underlying data array.
  /// @return Pointer to the data array.
  auto data() -> int16_t*;

  /// @brief Returns a const pointer to the underlying data array.
  /// @return Const pointer to the data array.
  [[nodiscard]] auto data() const -> const int16_t*;

 private:
  std::vector<int16_t> buffer_{};
};
}  // namespace common
