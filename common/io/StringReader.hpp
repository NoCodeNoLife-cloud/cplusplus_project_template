#pragma once
#include <ostream>
#include <string>
#include <utility>
#include "AbstractReader.hpp"

namespace common::io {
/// \brief A class that reads characters from a string.
/// \details It is a concrete implementation of the interface::Readable interface.
/// It is used to read characters from a string. The mark and reset methods are supported.
class StringReader final : public AbstractReader {
public:
  explicit StringReader(std::string s) : source_(std::move(s)), position_(0), markPosition_(0), markSet_(false) {}

  ~StringReader() override = default;

  /// \brief Closes the StringReader and releases its resources.
  /// \details Clears the source string, resets the current position, mark position, and mark status.
  /// This effectively renders the reader empty and in a default state.
  auto close() -> void override {
    source_.clear();
    position_ = 0;
    markPosition_ = 0;
    markSet_ = false;
  }

  /// \brief Marks the current position in the stream.
  /// \details This method marks the current position in the stream. The `readAheadLimit` parameter is not used in this
  /// implementation, but must be non-negative.
  /// \param readAheadLimit The limit of bytes that can be read before the mark position becomes invalid.
  /// \throws std::invalid_argument If `readAheadLimit` is negative.
  auto mark(const size_t readAheadLimit) -> void override {
    markPosition_ = readAheadLimit;
    markSet_ = true;
  }

  /// \brief Tests if this reader supports the mark and reset methods.
  /// \details Whether this reader supports the mark and reset methods.
  /// \return true if this reader supports the mark and reset methods, false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override {
    return true;
  }

  /// \brief Reads a single character from the string.
  /// \details This function reads the next character from the source string and advances the position.
  /// If the end of the string has been reached, it returns -1 to indicate EOF.
  /// \return The character read as an integer, or -1 if the end of the string is reached.
  auto read() -> int override {
    if (position_ >= source_.size()) {
      return -1; // EOF
    }
    return source_[position_++];
  }

  /// \brief Reads characters from the string into a buffer.
  /// \details This method attempts to read up to len characters from the source string into the provided buffer vector,
  /// starting at the specified offset. It copies characters from the source string to the buffer. If the offset and
  /// length exceed the size of the buffer, an exception is thrown. The method returns the actual number of characters
  /// read into the buffer.
  /// \param cBuf The buffer into which the data is read.
  /// \param off The starting position in the buffer to write the data.
  /// \param len The maximum number of characters to read into the buffer.
  /// \return The total number of characters read into the buffer.
  /// \throws std::invalid_argument If the offset is out of bounds of the buffer.
  auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override {
    if (off >= cBuf.size()) {
      throw std::invalid_argument("Offset is out of bounds of the buffer");
    }
    const size_t maxRead = std::min(len, source_.size() - position_);
    const size_t actualRead = std::min(maxRead, cBuf.size() - off);
    for (size_t i = 0; i < actualRead; ++i) {
      if (position_ < source_.size()) {
        cBuf[off + i] = source_[position_++];
      }
      else {
        break;
      }
    }
    return actualRead;
  }

  /// \brief Tests if this reader is ready to be read.
  /// \details Whether this reader is ready to be read. A reader is ready if the next read operation
  /// will not block. This reader is always ready because it is backed by a string in memory.
  /// \return true if this reader is ready to be read, false otherwise.
  [[nodiscard]] auto ready() const -> bool override {
    return position_ < source_.size();
  }

  /// \brief Resets the StringReader to the last marked position.
  /// \details If a mark has been set, this method resets the current position to the mark position.
  /// If no mark has been set, it resets the position to the beginning of the string.
  auto reset() -> void override {
    if (!markSet_) {
      position_ = 0;
    }
    else {
      position_ = markPosition_;
    }
  }

  /// \brief Skips over and discards n characters of data from this reader.
  /// \details The skip method may, for a variety of reasons, end before skipping n characters.
  /// \param ns The number of characters to skip.
  /// \return The number of characters actually skipped.
  /// \throws std::invalid_argument If the skip value is negative.
  auto skip(const size_t ns) -> size_t override {
    const size_t charsToSkip = std::min(ns, source_.size() - position_);
    position_ += charsToSkip;
    return static_cast<long>(charsToSkip);
  }

private:
  std::string source_;
  size_t position_;
  size_t markPosition_;
  bool markSet_;
};
}
