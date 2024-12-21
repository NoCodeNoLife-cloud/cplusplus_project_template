#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io {
/// \brief A concrete class that filters an output stream.
/// \details The `FilterOutputStream` class provides a base implementation for filtering
/// operations on an underlying output stream. Subclasses can extend this to provide
/// specific filtering behaviors.
class FilterOutputStream : public AbstractOutputStream {
public:
  explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream): outputStream_(std::move(outputStream)) {}

  ~FilterOutputStream() override = default;

  /// \brief Writes a single byte to the stream.
  /// \param b The byte to write.
  /// \throw std::runtime_error If the underlying stream is unavailable.
  auto write(const std::byte b) -> void override {
    if (!outputStream_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputStream_->write(b);
  }

  /// \brief Writes the entire buffer to the stream.
  /// \param buffer The buffer containing the data to write.
  /// \throw std::runtime_error If the underlying stream is unavailable.
  auto write(const std::vector<std::byte>& buffer) -> void override {
    if (!outputStream_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputStream_->write(buffer);
  }

  /// \brief Writes a portion of the buffer to the stream.
  /// \param buffer The buffer containing the data to write.
  /// \param offset The offset in the buffer at which to start writing.
  /// \param len The number of bytes to write.
  /// \throw std::runtime_error If the underlying stream is unavailable or the buffer is invalid.
  auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void override {
    if (!outputStream_) {
      throw std::runtime_error("Output stream is not available");
    }
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    outputStream_->write(buffer, offset, len);
  }

  /// \brief Flushes the stream, forcing any buffered output bytes to be written.
  /// \throw std::runtime_error If the underlying stream is unavailable.
  auto flush() -> void override {
    if (!outputStream_) {
      throw std::runtime_error("Output stream is not available");
    }
    outputStream_->flush();
  }

  /// \brief Closes the stream and releases any system resources associated with it.
  /// \throw std::runtime_error If the underlying stream is unavailable.
  auto close() -> void override {
    if (!outputStream_) {
      throw std::runtime_error("Output stream is not available");
    }
    flush();
    outputStream_->close();
  }

protected:
  std::shared_ptr<AbstractOutputStream> outputStream_;
};
}
