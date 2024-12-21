#pragma once
#include <memory>
#include "AbstractReader.hpp"

namespace common::io {
class FilterReader : public AbstractReader {
public:
  explicit FilterReader(std::shared_ptr<AbstractReader> reader): in(std::move(reader)) {}

  ~FilterReader() override = default;

  /// \brief Closes the FilterReader and releases its resources.
  /// \details This method closes the underlying input reader and releases any system resources associated with it.
  /// Once the stream has been closed, further read(), ready(), mark(), or reset() operations will throw.
  /// Closing a previously closed stream has no effect.
  auto close() -> void override {
    in->close();
  }

  /// \brief Resets the stream to the last marked position.
  /// \details If the method mark(int) has not been called since the stream was created, or the number of bytes read from the stream since mark(int) was called is larger than the argument to mark(int), then an IOException might be thrown.
  /// \remark This method is optional and might throw an IOException if the stream does not support mark() and reset().
  auto mark(const size_t readAheadLimit) -> void override {
    in->mark(readAheadLimit);
  }

  /// \brief Skips over and discards n bytes of data from this input stream.
  /// \details The skip method may, for a variety of reasons, end up skipping over some smaller number of bytes,
  /// possibly 0. This method may block until some input is available. Note that skip(0) will not cause a no-op, but
  /// will instead cause the stream's position to be advanced by 0 bytes.
  [[nodiscard]] auto markSupported() const -> bool override {
    return in->markSupported();
  }

  /// \brief Tests if this stream is ready to be read.
  /// \details A FilterReader is ready if and only if the underlying input reader is ready.
  auto read() -> int override {
    return in->read();
  }

  /// \brief Reads a portion of the input stream into the given array.
  /// \details This method blocks until some input is available.
  /// \param cBuf the destination buffer
  /// \param off the offset in the buffer to write to
  /// \param len the maximum number of bytes to read
  /// \return the number of characters read, or -1 if the end of the stream is reached.
  auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override {
    if (off + len > cBuf.size()) {
      throw std::out_of_range("Buffer overflow detected.");
    }
    return in->read(cBuf, off, len);
  }

  /// \brief Reads characters into an array.
  /// \details This method reads up to len bytes of data from this stream into an array of bytes.
  /// \param cBuf the destination buffer
  /// \return the number of characters read, or -1 if the end of the stream is reached.
  auto read(std::vector<char>& cBuf) -> size_t override {
    return in->read(cBuf);
  }

  /// \brief Reads characters into an array.
  /// \details This method reads up to len bytes of data from this stream into an array of bytes.
  /// \return the number of characters read, or -1 if the end of the stream is reached.
  [[nodiscard]] auto ready() const -> bool override {
    return in->ready();
  }

  /// \brief Resets the stream to the last marked position.
  /// \details If the mark method has not been called, or if the read limit has been exceeded, an IOException might be thrown.
  auto reset() -> void override {
    in->reset();
  }

  /// \brief Skips over and discards n bytes of data from this input stream.
  /// \details The skip method may, for a variety of reasons, end up skipping over some smaller number of bytes,
  /// possibly 0. This method may block until some input is available. Note that skip(0) will not cause a no-op, but
  /// will instead cause the stream's position to be advanced by 0 bytes.
  /// \param n the number of bytes to be skipped
  /// \return the actual number of bytes skipped
  auto skip(const size_t n) -> size_t override {
    return in->skip(n);
  }

protected:
  std::shared_ptr<AbstractReader> in;
};
}
