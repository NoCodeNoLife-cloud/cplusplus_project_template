#pragma once
#include "AbstractInputStream.hpp"

namespace common::io {
/// \brief A class that reads bytes from a stream with filtering.
/// \details It reads bytes from a stream with filtering. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
class FilterInputStream : public AbstractInputStream {
public:
  explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream): inputStream_(std::move(inputStream)) {}

  ~FilterInputStream() override = default;

  /// \brief Returns the number of bytes that can be read without blocking.
  /// \return The number of available bytes.
  auto available() -> size_t override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    return inputStream_->available();
  }

  /// \brief Marks the current position in the stream.
  /// \param readLimit The maximum bytes to read before the mark becomes invalid.
  auto mark(const int readLimit) -> void override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    inputStream_->mark(readLimit);
  }

  /// \brief Checks if marking is supported by the stream.
  /// \return `true` if marking is supported; otherwise, `false`.
  [[nodiscard]] auto markSupported() const -> bool override {
    if (!inputStream_) {
      return false;
    }
    return inputStream_->markSupported();
  }

  /// \brief Reads the next byte from the stream.
  /// \return The next byte as an `int`, or `-1` if end of stream is reached.
  auto read() -> std::byte override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    return inputStream_->read();
  }

  /// \brief Reads bytes into the provided buffer.
  /// \param buffer The buffer to fill with bytes.
  /// \return The number of bytes read.
  size_t read(std::vector<std::byte>& buffer) override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    return inputStream_->read(buffer);
  }

  /// \brief Reads bytes into the provided buffer starting at the given offset.
  /// \param buffer The buffer to fill with bytes.
  /// \param offset The start position in the buffer to write to.
  /// \param len The maximum number of bytes to read.
  /// \return The number of bytes read.
  size_t read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    return inputStream_->read(buffer, offset, len);
  }

  /// \brief Resets the stream to the most recent mark.
  void reset() override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    inputStream_->reset();
  }

  /// \brief Skips over the specified number of bytes in the stream.
  /// \param n The number of bytes to skip.
  /// \return The actual number of bytes skipped.
  size_t skip(const size_t n) override {
    if (!inputStream_) {
      throw std::runtime_error("Input stream is not available");
    }
    return inputStream_->skip(n);
  }

  /// \brief Closes the input stream and releases any system resources associated with the stream.
  /// \details Closes the underlying input stream and releases any system resources associated with it.
  auto close() -> void override {
    inputStream_->close();
  }

protected:
  std::unique_ptr<AbstractInputStream> inputStream_;
};
}
