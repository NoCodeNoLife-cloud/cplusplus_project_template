#pragma once
#include <vector>

#include "FilterOutputStream.hpp"

namespace common {
/// @brief A buffered output stream that writes data to an underlying output stream.
/// This class buffers the data written to it and flushes it to the underlying stream
/// when the buffer is full or when explicitly requested.
class BufferedOutputStream final : public FilterOutputStream {
 public:
  explicit BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out);
  BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, size_t size);
  ~BufferedOutputStream() override;

  /// @brief Writes a single byte to the buffer.
  /// @param b The byte to write.
  auto write(std::byte b) -> void override;

  /// @brief Writes a sequence of bytes to the buffer.
  /// @param data The data to write.
  /// @param offset The start offset in the data.
  /// @param len The number of bytes to write.
  auto write(const std::vector<std::byte>& data, size_t offset, size_t len) -> void override;

  /// @brief Flushes the buffer by writing all buffered bytes to the underlying output stream.
  auto flush() -> void override;

  /// @brief Closes the stream by flushing the buffer and closing the underlying output stream.
  auto close() -> void override;

 protected:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
  size_t bufferSize_;
  std::vector<std::byte> buffer_;
  size_t buffer_position_;
  auto flushBuffer() -> void;
};
}  // namespace common
