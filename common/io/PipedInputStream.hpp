#pragma once
#include <mutex>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io {
class PipedOutputStream;

/// \brief A class that reads bytes from a stream with pipe.
/// \details It reads bytes from a stream with pipe. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pipe size can be specified in the constructor.
class PipedInputStream final : public AbstractInputStream {
public:
  PipedInputStream(): PipedInputStream(PIPE_SIZE) {}

  explicit PipedInputStream(const size_t pipeSize): buffer_(pipeSize) {}

  explicit PipedInputStream(const std::shared_ptr<PipedOutputStream>& src) : PipedInputStream(src, PIPE_SIZE) {}

  PipedInputStream(const std::shared_ptr<PipedOutputStream>& src, const size_t pipeSize): PipedInputStream(pipeSize) {
    connect(src);
  }

  ~PipedInputStream() override {
    close();
  }

  /// \brief Closes this piped input stream and releases any system resources associated with it.
  /// \details Clears the buffer and resets the in and out indices to zero.
  /// \note This method is thread-safe as it locks the mutex before performing operations.
  auto close() -> void override {
    std::lock_guard lock(mutex_);
    buffer_.clear();
    in_ = out_ = 0;
  }

  /// \brief Returns the number of bytes that can be read from this input stream without blocking.
  /// \details Returns the number of bytes that can be read from this input stream without blocking.
  /// \return The number of bytes that can be read from this input stream without blocking.
  auto available() -> size_t override {
    std::lock_guard lock(mutex_);
    return (in_ + buffer_.size() - out_) % buffer_.size();
  }

  /// \brief Reads the next byte of data from this input stream.
  /// \details Reads the next byte of data from this input stream.
  /// \return The next byte of data from this input stream.
  /// \throw std::runtime_error If the end of the stream has been reached.
  /// \note This method is thread-safe as it locks the mutex before performing operations.
  auto read() -> std::byte override {
    std::lock_guard lock(mutex_);
    if (in_ == out_) {
      throw std::runtime_error("PipedInputStream is empty");
    }
    const auto result = buffer_[out_];
    out_ = (out_ + 1) % buffer_.size();
    return result;
  }

  /// \brief Reads up to \a len bytes of data from this input stream into the given array.
  /// \details Reads up to \a len bytes of data from this input stream into the given array starting at \a offset.
  /// \param[out] buffer The destination array.
  /// \param[in] offset The offset in the destination array where to start writing.
  /// \param[in] len The maximum number of bytes to read.
  /// \return The number of bytes read.
  /// \throw std::runtime_error If the end of the stream has been reached.
  /// \note This method is thread-safe as it locks the mutex before performing operations.
  size_t read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) override {
    std::lock_guard lock(mutex_);
    size_t bytesRead{0};
    while (bytesRead < len && out_ != in_) {
      buffer_[offset + bytesRead] = buffer_[out_];
      ++bytesRead;
      out_ = (out_ + 1) % buffer_.size();
    }
    return bytesRead;
  }

  /// \brief Connects the piped input stream to the given piped output stream.
  /// \details Connects the piped input stream to the given piped output stream.
  /// \param[in] src The piped output stream to connect to.
  /// \throw std::runtime_error If the piped input stream is already connected.
  auto connect(std::shared_ptr<PipedOutputStream> src) -> void {
    std::lock_guard lock(mutex_);
    if (src_) {
      throw std::runtime_error("PipedInputStream is already connected");
    }
    src_ = std::move(src);
  }

  /// \brief Receives a single byte of data from the connected piped output stream.
  /// \details Receives a single byte of data from the connected piped output stream.
  /// \param[in] b The byte of data to receive.
  /// \throw std::runtime_error If the piped input stream is not connected.
  /// \throw std::runtime_error If the piped input stream is already full.
  auto receive(const std::byte b) -> void {
    std::lock_guard lock(mutex_);
    if ((in_ + 1) % buffer_.size() == out_) {
      throw std::runtime_error("PipedInputStream is overflow");
    }
    buffer_[in_] = b;
    in_ = (in_ + 1) % buffer_.size();
  }

protected:
  std::vector<std::byte> buffer_{};
  size_t in_{0};
  size_t out_{0};
  static constexpr size_t PIPE_SIZE = 1024;
  std::mutex mutex_;
  std::shared_ptr<PipedOutputStream> src_;
};
}
