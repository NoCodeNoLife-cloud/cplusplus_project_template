#pragma once
#include <fstream>
#include "AbstractReader.hpp"

namespace common::io {
/// \brief A final class that provides buffering for a Reader object.
/// \details This class provides buffering for a Reader object. Buffering can greatly improve performance by reducing the number
/// of calls to the underlying Reader object. The buffering is optional and can be disabled by calling the constructor with
/// a buffer size of 0.
class BufferedReader final : public AbstractReader {
public:
  explicit BufferedReader(std::unique_ptr<AbstractReader> reader, const int size = DEFAULT_BUFFER_SIZE): reader_(std::move(reader)), bufferSize_(size) {
    if (size <= 0) {
      throw std::invalid_argument("Buffer size must be greater than 0");
    }
    buffer_.resize(size);
  }

  ~BufferedReader() override = default;

  /// \brief Closes the BufferedReader and releases its resources.
  /// \details This method closes the reader and releases any system resources associated with it.
  /// Once the stream has been closed, further read(), ready(), mark(), or reset() operations will throw.
  /// Closing a previously closed stream has no effect.
  auto close() -> void override {
    reader_->close();
  }

  /// \brief Marks the current position in the stream.
  /// \details This method marks the current position in the stream.
  /// The `readAheadLimit` parameter is not used in this implementation, but must be non-negative.
  /// \param readAheadLimit The limit of bytes that can be read before the mark position becomes invalid.
  /// \throws std::invalid_argument If `readAheadLimit` is negative.
  auto mark(const size_t readAheadLimit) -> void override {
    if (readAheadLimit <= 0) {
      throw std::invalid_argument("Mark limit must be greater than 0");
    }
    reader_->mark(readAheadLimit);
    markLimit_ = readAheadLimit;
  }

  /// \brief Tests if this BufferedReader supports the mark and reset methods.
  /// \details This method returns true indicating that the BufferedReader supports
  /// the mark and reset methods, allowing the current position in the stream to be saved
  /// and reverted to later.
  /// \return true since this BufferedReader supports the mark and reset methods.
  [[nodiscard]] auto markSupported() const -> bool override {
    return true;
  }

  /// \brief Resets the BufferedReader to the last marked position.
  /// \details This method resets the position in the stream to the last marked position
  /// by calling the mark() method. If a mark has not been set, this method does nothing.
  /// \throws std::ios_base::failure If an error occurs while resetting the stream.
  auto reset() -> void override {
    reader_->reset();
    pos_ = markLimit_;
  }

  /// \brief Reads a single character from the stream.
  /// \details This method reads the next character from the stream and advances the position.
  /// If the end of the stream has been reached, it returns -1 to indicate EOF.
  /// \return The character read as an integer, or -1 if the end of the stream is reached.
  auto read() -> int override {
    if (pos_ >= count_) {
      if (!fillBuffer()) {
        return -1;
      }
    }
    return buffer_[pos_++];
  }

  /// \brief Reads characters from the stream into a buffer.
  /// \details This method reads up to `len` characters from the stream into the buffer
  /// starting at the specified offset `off`. The number of characters actually
  /// read is returned as a long long value. If the end of the stream has been
  /// reached, the method returns -1.
  /// \param cBuf The buffer to fill with characters.
  /// \param off The offset in the buffer at which to start filling.
  /// \param len The number of characters to read.
  /// \return The number of characters read, or -1 if the end of the stream is reached.
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override {
    if (off + len > cBuf.size()) {
      return -1;
    }
    size_t totalBytesRead = 0;
    if (len == 0) {
      return 0;
    }
    while (len > 0) {
      if (pos_ >= count_) {
        if (!fillBuffer()) {
          break;
        }
      }
      size_t bytesAvailable = count_ - pos_;
      const size_t bytesToRead = std::min(bytesAvailable, len);
      std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), bytesToRead, cBuf.begin() + static_cast<std::ptrdiff_t>(off));
      totalBytesRead += bytesToRead;
      off += bytesToRead;
      len -= bytesToRead;
      pos_ += bytesToRead;
    }
    return totalBytesRead;
  }

  /// \brief Reads a line of text from the stream.
  /// \details Reads a line of text from the stream and returns it as a string.
  /// The line is read until the end of line is reached or a maximum number of characters is read.
  /// \return The line of text that was read from the stream.
  auto readLine() -> std::string {
    std::string line;
    while (true) {
      if (pos_ >= count_) {
        if (!fillBuffer()) {
          break;
        }
      }
      const char ch = buffer_[pos_++];
      if (ch == '\n') {
        break;
      }
      if (ch != '\r') {
        line += ch;
      }
    }
    return line;
  }

  /// \brief Tests if this reader is ready to be read.
  /// \details Whether this reader is ready to be read. A reader is ready if the next read operation
  /// will not block. This reader is always ready because it is backed by an underlying reader in memory.
  /// \return true if this reader is ready to be read, false otherwise.
  [[nodiscard]] auto ready() const -> bool {
    return reader_->ready();
  }

  /// \brief Skips over and discards n characters of data from this reader.
  /// \details The skip method may, for a variety of reasons, end before skipping n characters.
  /// \param n The number of characters to skip.
  /// \return The number of characters actually skipped.
  /// \throws std::invalid_argument If the skip value is negative.
  auto skip(const long n) -> long {
    if (n <= 0) {
      throw std::invalid_argument("Skip value must be positive");
    }
    long skipped = 0;
    while (skipped < n) {
      if (pos_ >= count_) {
        if (!fillBuffer()) {
          break;
        }
      }
      const long bytesToSkip = std::min(static_cast<long>(count_ - pos_), n - skipped);
      pos_ += bytesToSkip;
      skipped += bytesToSkip;
    }
    return skipped;
  }

private:
  static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
  std::vector<char> buffer_;
  std::unique_ptr<AbstractReader> reader_;
  size_t bufferSize_{0};
  size_t pos_{0};
  size_t count_{0};
  size_t markLimit_{0};

  /// \brief Fills the buffer with data from the underlying reader.
  /// \details Attempts to fill the buffer by reading from the underlying reader into the buffer.
  /// The buffer is filled starting from the beginning, and the function updates the buffer's count.
  /// \return true if the buffer was successfully filled with data, false otherwise (indicating EOF).
  bool fillBuffer() {
    pos_ = 0;
    count_ = reader_->read(buffer_, 0, bufferSize_);
    return count_ > 0;
  }
};
}
