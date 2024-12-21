#pragma once
#include "AbstractOutputStream.hpp"
#include "PipedInputStream.hpp"

namespace common::io {
class PipedInputStream;

/// \brief A final class for writing bytes to a pipe.
/// \details The PipedOutputStream class provides methods to write bytes to a pipe.
/// It is a concrete implementation of the AbstractOutputStream interface.
/// The class supports writing single bytes and byte arrays, with the option to specify offsets and lengths.
/// The class also supports flushing and closing the stream, as well as checking if the stream is closed.
/// \remark The class is designed to handle pipe output operations, with options for connecting to a PipedInputStream.
class PipedOutputStream final : public AbstractOutputStream {
public:
  explicit PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk) {
    if (!snk) {
      throw std::invalid_argument("PipedInputStream cannot be null");
    }
    snk_ = snk;
    connected_ = true;
    closed_ = false;
  }

  ~PipedOutputStream() override {
    close();
  }

  /// \brief Closes the piped output stream.
  /// \details If the stream is already closed, this method does nothing.
  /// Otherwise, it flushes the stream and sets the closed flag.
  /// If the stream is connected, it also closes the connected input stream.
  auto close() -> void override {
    if (closed_) {
      return;
    }
    flush();
    connected_ = false;
    closed_ = true;
    if (snk_) {
      snk_->close();
    }
  }

  /// \brief Flushes the piped output stream.
  /// \details This method does not actually flush any data, as the data is directly written to the connected input stream.
  /// The method is provided to satisfy the interface requirements of the OutputStream interface.
  /// If the stream is not connected or if the stream is closed, the method throws an exception.
  auto flush() -> void override {
    if (closed_ || !connected_ || !snk_) {
      throw std::runtime_error("PipedOutputStream is not connected");
    }
    // no-op
  }

  /// \brief Writes a single byte to the piped output stream.
  /// \details If the stream is not connected or if the stream is closed, the method throws an exception.
  /// Otherwise, it writes the byte to the connected input stream.
  auto write(const std::byte b) -> void override {
    if (closed_ || !connected_ || !snk_) {
      throw std::runtime_error("PipedOutputStream is not connected");
    }
    snk_->receive(b);
  }

  /// \brief Writes a portion of a byte array to the piped output stream.
  /// \details If the stream is not connected or if the stream is closed, the method throws an exception.
  /// Otherwise, it writes the specified portion of the byte array to the connected input stream.
  void write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) override {
    if (closed_ || !connected_ || !snk_) {
      throw std::runtime_error("PipedOutputStream is not connected");
    }
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer overflow");
    }
    for (size_t i = 0; i < len; ++i) {
      snk_->receive(buffer[offset + i]);
    }
  }

protected:
  std::shared_ptr<PipedInputStream> snk_;
  bool closed_{true};
  bool connected_{false};
};
}
