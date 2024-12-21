#pragma once
#include <mutex>
#include <utility>
#include "AbstractReader.hpp"
#include "PipedWriter.hpp"

namespace common::io {
class PipedWriter;

/// \brief A class that reads characters from a stream with pipe.
/// \details It reads characters from a stream with pipe. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pipe size can be specified in the constructor.
class PipedReader final : public AbstractReader {
public:
  PipedReader(): PipedReader(DEFAULT_PIPE_SIZE) {}

  explicit PipedReader(int pipeSize) : buffer_(pipeSize), bufferSize_(pipeSize) {}

  explicit PipedReader(const std::shared_ptr<PipedWriter>& src) : PipedReader(src, DEFAULT_PIPE_SIZE) {}

  PipedReader(std::shared_ptr<PipedWriter> src, const int pipeSize) : src_(std::move(src)), buffer_(pipeSize), bufferSize_(pipeSize) {}

  ~PipedReader() override {
    close();
  }

  /// \brief Closes the PipedReader.
  /// \details This method closes the PipedReader, resetting the associated PipedWriter,
  auto close() -> void override {
    src_.reset();
    buffer_.clear();
    readPos_ = writePos_ = 0;
  }

  /// \brief Reads the next byte of data from this input stream.
  /// \details The value byte is returned as an \c int in the range \c 0 to
  /// \c 255. If no byte is available because the end of the stream has been
  /// reached, the value \c -1 is returned. This method blocks until input data
  /// is available, the end of the stream is detected, or an exception is thrown.
  /// \return the next byte of data, or \c -1 if the end of the stream is reached.
  auto read() -> int override {
    std::lock_guard lock(readMutex_);
    if (!ready()) {
      return -1;
    }
    return buffer_[readPos_++ % bufferSize_];
  }

  /// \brief Reads characters into a portion of an array.
  /// \details This method blocks until some input is available, the end of the
  /// stream is detected, or an exception is thrown.
  /// \param cBuf destination buffer. If the length of the destination buffer is
  /// less than the number of bytes requested to be read, then the returned value
  /// is the number of bytes actually read and the buffer is filled.
  /// \param off the start offset of the data
  /// \param len the maximum number of bytes to read
  /// \return The number of bytes actually read, or -1 if the end of the stream has
  /// been reached
  auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override {
    std::lock_guard lock(readMutex_);
    if (off + len > cBuf.size()) {
      throw std::out_of_range("index out of range");
    }
    size_t bytesRead = 0;
    while (bytesRead < len && ready()) {
      cBuf[off + bytesRead] = buffer_[readPos_++ % bufferSize_];
      ++bytesRead;
    }
    return bytesRead;
  }

  /// \brief Tests if this reader is ready to be read.
  /// \details Whether this reader is ready to be read. A reader is ready if the next read operation
  /// will not block. This reader is ready if there is data available in the pipe.
  /// \return true if this reader is ready to be read, false otherwise.
  [[nodiscard]] auto ready() const -> bool override {
    return readPos_ != writePos_;
  }

  /// \brief Connects the piped reader to the given piped writer.
  /// \details Connects the piped reader to the given piped writer.
  /// \param[in] src The piped writer to connect to.
  /// \throw std::runtime_error If the piped reader is already connected.
  auto connect(std::shared_ptr<PipedWriter> src) -> void {
    if (src_) {
      throw std::runtime_error("already connected");
    }
    src_ = std::move(src);
  }

  /// \brief Marks the current position in the input stream.
  /// \details This method is a no-op for PipedReader as marking is not supported.
  /// The readAheadLimit parameter is ignored.
  /// \param readAheadLimit The limit of bytes that can be read before the mark position becomes invalid.
  auto mark(size_t readAheadLimit) -> void override {
    // no-op
  }

  /// \brief Resets the input stream to the last marked position.
  /// \details This method is a no-op for PipedReader as marking is not supported.
  /// The method does not throw any exception.
  auto reset() -> void override {
    // no-op
  }

  /// \brief Tests if this reader supports the mark and reset methods.
  /// \details Whether this reader supports the mark and reset methods.
  /// \return false if this reader supports the mark and reset methods, true otherwise.
  [[nodiscard]] auto markSupported() const -> bool override {
    return false;
  }

  /// \brief Writes a character to the pipe buffer.
  /// \details Writes a character to the pipe buffer. This method is called by the piped writer.
  /// If the buffer is full, an exception is thrown.
  /// \param[in] c The character to write to the pipe buffer.
  auto writeToBuffer(char c) -> void {
    if (bufferSize_ == 0) {
      throw std::runtime_error("Buffer not initialized or closed.");
    }
    const size_t nextWritePos = (writePos_ + 1) % bufferSize_;
    if (nextWritePos == readPos_) {
      throw std::runtime_error("Pipe buffer overflow: Reader has not consumed data.");
    }
    buffer_[writePos_] = c;
    writePos_ = nextWritePos;
  }

private:
  static constexpr int DEFAULT_PIPE_SIZE = 1024;
  std::shared_ptr<PipedWriter> src_;
  std::vector<char> buffer_;
  size_t bufferSize_{0};
  size_t readPos_{0};
  size_t writePos_{0};
  std::mutex readMutex_;
};
}
