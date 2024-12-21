#pragma once
#include <stdexcept>
#include "AbstractReader.hpp"

namespace common::io {
/// \brief A final class for reading characters from a character array.
/// \details The CharArrayReader class provides methods to read characters from a character array.
/// It is a concrete implementation of the AbstractReader interface.
/// This class supports marking and resetting, allowing the user to mark a position in the input and reset the stream to that position.
/// It also provides methods to check if the reader is ready to be read, skip characters, and close the reader.
class CharArrayReader final : public AbstractReader {
public:
  explicit CharArrayReader(const std::vector<char>& buffer): buf_(buffer), count_(buffer.size()) {}

  CharArrayReader(const std::vector<char>& buffer, const size_t offset, const size_t length) {
    if (offset > buffer.size() || offset + length > buffer.size()) {
      throw std::invalid_argument("Invalid offset or length");
    }
    buf_.assign(buffer.begin() + static_cast<std::ptrdiff_t>(offset), buffer.begin() + static_cast<std::ptrdiff_t>(offset + length));
    count_ = length;
  }

  ~CharArrayReader() override = default;

  /// \brief Reads a single character from the character array.
  /// \details Reads a single character from the character array.
  /// \return The character read, or -1 if the end of the stream is reached.
  auto read() -> int override {
    if (pos_ >= count_) return -1;
    return buf_[pos_++];
  }

  /// \brief Reads characters from the character array into a buffer.
  /// \details This method attempts to read up to len characters from the character array into the provided buffer vector,
  /// starting at the specified offset. It copies characters from the character array to the buffer. If the offset and
  /// length exceed the size of the buffer, an exception is thrown. The method returns the actual number of characters
  /// read into the buffer.
  /// \param b The buffer into which the data is read.
  /// \param off The starting position in the buffer to write the data.
  /// \param len The maximum number of characters to read into the buffer.
  /// \return The total number of characters read into the buffer.
  /// \throws std::out_of_range If the offset or length exceed the size of the buffer.
  auto read(std::vector<char>& b, const size_t off, const size_t len) -> size_t override {
    if (pos_ >= count_) return -1;
    if (off >= b.size() || off + len > b.size()) {
      throw std::out_of_range("Invalid offset or length for target buffer");
    }
    const size_t toRead = std::min(len, count_ - pos_);
    std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead, b.begin() + static_cast<std::ptrdiff_t>(off));
    pos_ += toRead;
    return toRead;
  }

  /// \brief Skips over and discards n characters of data from this reader.
  /// \details The skip method increases the position by the number of characters skipped, up to n,
  /// or until the end of the stream is reached. If the end of the stream is reached before
  /// n characters are skipped, it returns the actual number of characters skipped.
  /// \param n The number of characters to skip.
  /// \return The number of characters actually skipped.
  auto skip(const size_t n) -> size_t override {
    const size_t skipped = std::min(n, count_ - pos_);
    pos_ += skipped;
    return skipped;
  }

  /// \brief Tests if this reader is ready to be read.
  /// \details Whether this reader is ready to be read. A reader is ready if the next read operation
  /// will not block. This reader is always ready because it is backed by a character array in memory.
  /// \return true if this reader is ready to be read, false otherwise.
  [[nodiscard]] auto ready() const -> bool {
    return pos_ < count_;
  }

  /// \brief Tests if this reader supports the mark and reset methods.
  /// \details Whether this reader supports the mark and reset methods.
  /// \return true if this reader supports the mark and reset methods, false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override {
    return true;
  }

  /// \brief Sets the current marked position in the stream.
  /// \details The mark method sets the current marked position in the stream.
  /// The marked position is the position up to which data can be read from the source buffer.
  /// If an I/O error occurs, the marked position is not changed.
  /// \param readAheadLimit The maximum number of characters that can be read from the source buffer.
  auto mark(const size_t readAheadLimit) -> void override {
    markedPos_ = readAheadLimit;
  }

  /// \brief Resets the reader to the last marked position.
  /// \details The reset method resets the position in the stream to the last marked position
  /// by calling the mark() method. If a mark has not been set, this method does nothing.
  /// \throws std::ios_base::failure If an error occurs while resetting the stream.
  auto reset() -> void override {
    pos_ = markedPos_;
  }

  /// \brief Closes the CharArrayReader and releases its resources.
  /// \details This method clears the buffer and resets the position, marked position, and count_ to zero.
  /// This effectively renders the reader empty and in a default state.
  auto close() -> void override {
    buf_.clear();
    pos_ = 0;
    markedPos_ = 0;
    count_ = 0;
  }

private:
  std::vector<char> buf_;
  size_t pos_{0};
  size_t markedPos_{0};
  size_t count_{0};
};
}
