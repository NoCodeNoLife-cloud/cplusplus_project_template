#pragma once
#include "FilterInputStream.hpp"

namespace common::io {
/// \brief A class that reads bytes from a stream with pushback ability.
/// \details It reads bytes from a stream with pushback ability. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pushback buffer size can be specified in the constructor.
class PushbackInputStream final : public FilterInputStream {
public:
  PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, size_t bufferSize): FilterInputStream(std::move(inputStream)), pushbackBuffer_(bufferSize), bufferPos_(bufferSize) {}

  ~PushbackInputStream() override = default;

  /// \brief Returns the number of bytes that can be read from this input stream without blocking.
  /// \details The available method for class PushbackInputStream returns the number of bytes that can be read from this input stream without blocking.
  /// \return The number of bytes that can be read from this input stream without blocking.
  auto available() -> size_t override {
    return pushbackBuffer_.size() - bufferPos_ + inputStream_->available();
  }

  /// \brief Reads a byte from this input stream.
  /// \details This function reads a single byte from the input stream.
  /// If there are bytes in the pushback buffer, it returns the next byte from the buffer.
  /// Otherwise, it reads a byte from the underlying input stream.
  /// \return The byte read from the input stream.
  auto read() -> std::byte override {
    if (bufferPos_ < pushbackBuffer_.size()) {
      return pushbackBuffer_[bufferPos_++];
    }
    return inputStream_->read();
  }

  /// \brief Reads bytes from this input stream into the specified buffer.
  /// \details Attempts to read up to buffer.size() bytes into the provided buffer vector.
  /// \param buffer The buffer into which the data is read.
  /// \return The total number of bytes read into the buffer, or -1 if the end of the stream has been reached.
  auto read(std::vector<std::byte>& buffer) -> size_t override {
    return read(buffer, 0, buffer.size());
  }

  /// \brief Reads bytes from this input stream into the specified buffer.
  /// \details Attempts to read up to len bytes into the provided buffer vector, starting at the offset.
  /// \param buffer The buffer into which the data is read.
  /// \param offset The starting position in the buffer.
  /// \param len The maximum number of bytes to read.
  /// \return The total number of bytes read into the buffer, or -1 if the end of the stream has been reached.
  auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t override {
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    size_t bytesRead = 0;
    while (bytesRead < len && bufferPos_ < pushbackBuffer_.size()) {
      buffer[offset + bytesRead++] = pushbackBuffer_[bufferPos_++];
    }
    if (bytesRead < len) {
      bytesRead += inputStream_->read(buffer, offset + bytesRead, len - bytesRead);
    }
    return bytesRead;
  }

  /// \brief Pushes back a buffer of bytes onto this stream.
  /// \details The buffer is pushed back onto this stream, and the next read will return the first byte of the buffer.
  /// \param buffer The buffer to push back.
  void unread(const std::vector<std::byte>& buffer) {
    unread(buffer, 0, buffer.size());
  }

  /// \brief Pushes back a buffer of bytes onto this stream.
  /// \details The buffer is pushed back onto this stream, and the next read will return the first byte of the buffer.
  /// \param buffer The buffer to push back.
  /// \param offset The starting offset in the buffer.
  /// \param len The number of bytes to push back.
  void unread(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
    if (len > bufferPos_) {
      throw std::overflow_error("Pushback buffer overflow");
    }
    for (size_t i = 0; i < len; ++i) {
      pushbackBuffer_[--bufferPos_] = buffer[offset + len - i - 1];
    }
  }

  /// \brief Pushes back a single byte onto this stream.
  /// \details The byte is pushed back onto this stream, and the next read will return the byte.
  /// \param b The byte to push back.
  void unread(const std::byte b) {
    if (bufferPos_ == 0) {
      throw std::overflow_error("Pushback buffer overflow");
    }
    pushbackBuffer_[--bufferPos_] = b;
  }

private:
  std::vector<std::byte> pushbackBuffer_;
  size_t bufferPos_{0};
};
}
