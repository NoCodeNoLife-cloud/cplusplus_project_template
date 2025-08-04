#pragma once
#include <span>
#include <vector>

#include "interface/IBuffer.hpp"

namespace common {
/// @brief A byte buffer implementation that manages a fixed-size buffer of bytes.
/// This class provides methods for putting and getting bytes, supporting both
/// single-byte operations and bulk operations with vectors of bytes.
class ByteBuffer final : public IBuffer {
 public:
  explicit ByteBuffer(size_t capacity);

  /// @brief Puts bytes from a vector into the buffer
  /// @param src The source vector of bytes to put into the buffer
  void put(const std::vector<std::byte>& src);

  /// @brief Puts a single byte into the buffer
  /// @param value The byte value to put into the buffer
  void put(std::byte value);

  /// @brief Gets a single byte from the buffer
  /// @return The byte retrieved from the buffer
  auto get() -> std::byte;

  /// @brief Gets a specified number of bytes from the buffer
  /// @param length The number of bytes to retrieve
  /// @return A vector containing the retrieved bytes
  auto get(size_t length) -> std::vector<std::byte>;

 private:
  std::vector<std::byte> buffer_;
};
}  // namespace common
