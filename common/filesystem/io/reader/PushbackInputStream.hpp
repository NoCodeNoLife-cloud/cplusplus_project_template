#pragma once
#include "FilterInputStream.hpp"

namespace fox {
/// @brief A pushback input stream allows bytes to be pushed back into the stream.
/// This class wraps another input stream and provides the ability to "unread" bytes,
/// making them available to be read again. This is useful for parsers that need to
/// look ahead in the input stream.
class PushbackInputStream final : public FilterInputStream {
 public:
  PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, const size_t bufferSize) : FilterInputStream(std::move(inputStream)), pushback_buffer_(bufferSize), buffer_pos_(bufferSize) {}
  ~PushbackInputStream() override = default;

  /// @brief Returns the number of bytes that can be read from this input stream without blocking.
  /// @return the number of bytes that can be read from this input stream without blocking.
  auto available() -> size_t override { return pushback_buffer_.size() - buffer_pos_ + input_stream_->available(); }

  /// @brief Reads the next byte of data from the input stream.
  /// @return the next byte of data, or -1 if the end of the stream is reached.
  auto read() -> std::byte override {
    if (buffer_pos_ < pushback_buffer_.size()) {
      return pushback_buffer_[buffer_pos_++];
    }
    return input_stream_->read();
  }

  /// @brief Reads up to `buffer.size()` bytes of data from the input stream into the buffer.
  /// @param buffer the buffer into which the data is read.
  /// @return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
  auto read(std::vector<std::byte>& buffer) -> size_t override { return read(buffer, 0, buffer.size()); }

  /// @brief Reads up to `len` bytes of data from the input stream into the buffer starting at `offset`.
  /// @param buffer the buffer into which the data is read.
  /// @param offset the start offset in the buffer at which the data is written.
  /// @param len the maximum number of bytes to read.
  /// @return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
  auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t override {
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    size_t bytesRead = 0;
    while (bytesRead < len && buffer_pos_ < pushback_buffer_.size()) {
      buffer[offset + bytesRead++] = pushback_buffer_[buffer_pos_++];
    }
    if (bytesRead < len) {
      bytesRead += input_stream_->read(buffer, offset + bytesRead, len - bytesRead);
    }
    return bytesRead;
  }

  /// @brief Pushes back the entire buffer into the stream.
  /// @param buffer the buffer to push back.
  void unread(const std::vector<std::byte>& buffer) { unread(buffer, 0, buffer.size()); }

  /// @brief Pushes back a portion of the buffer into the stream.
  /// @param buffer the buffer containing data to push back.
  /// @param offset the start offset in the buffer from which data is pushed back.
  /// @param len the number of bytes to push back.
  void unread(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
    if (len > buffer_pos_) {
      throw std::overflow_error("Pushback buffer overflow");
    }
    for (size_t i = 0; i < len; ++i) {
      pushback_buffer_[--buffer_pos_] = buffer[offset + len - i - 1];
    }
  }

  /// @brief Pushes back a single byte into the stream.
  /// @param b the byte to push back.
  void unread(const std::byte b) {
    if (buffer_pos_ == 0) {
      throw std::overflow_error("Pushback buffer overflow");
    }
    pushback_buffer_[--buffer_pos_] = b;
  }

 private:
  std::vector<std::byte> pushback_buffer_;
  size_t buffer_pos_{0};
};
}  // namespace fox
