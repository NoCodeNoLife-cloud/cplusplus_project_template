#pragma once
#include <ostream>
#include <string>

#include "AbstractReader.hpp"

namespace fox {
/// @brief A StringReader class that reads data from a string.
/// @details This class implements the AbstractReader interface to provide functionality
///          for reading characters from a string. It supports marking and resetting
///          to a previous position in the string.
class StringReader final : public AbstractReader {
 public:
  explicit StringReader(std::string s) : source_(std::move(s)), position_(0), mark_position_(0), mark_set_(false) {}
  ~StringReader() override = default;

  /// @brief Closes the StringReader and releases any associated resources.
  auto close() -> void override {
    source_.clear();
    position_ = 0;
    mark_position_ = 0;
    mark_set_ = false;
  }

  /// @brief Marks the current position in the stream.
  /// @param readAheadLimit the maximum number of characters that can be read from the stream before the mark position becomes invalid.
  auto mark(const size_t readAheadLimit) -> void override {
    mark_position_ = readAheadLimit;
    mark_set_ = true;
  }

  /// @brief Tests if this input stream supports the mark and reset methods.
  /// @return true if this stream type supports the mark and reset methods; false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override { return true; }

  /// @brief Reads a single character from the string.
  /// @return The character read, or -1 if the end of the string has been reached.
  [[nodiscard]] auto read() -> int32_t override {
    if (position_ >= source_.size()) {
      return -1;  // EOF
    }
    return source_[position_++];
  }

  /// @brief Reads up to len characters from the string into the buffer cBuf starting at offset off.
  /// @param cBuf The buffer into which the data is read.
  /// @param off The start offset in the buffer at which the data is written.
  /// @param len The maximum number of characters to read.
  /// @return The total number of characters read into the buffer, or 0 if there is no more data because the end of the string has been reached.
  [[nodiscard]] auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override {
    if (off >= cBuf.size()) {
      throw std::invalid_argument("Offset is out of bounds of the buffer");
    }
    const size_t maxRead = std::min(len, source_.size() - position_);
    const size_t actualRead = std::min(maxRead, cBuf.size() - off);
    for (size_t i = 0; i < actualRead; ++i) {
      if (position_ < source_.size()) {
        cBuf[off + i] = source_[position_++];
      } else {
        break;
      }
    }
    return actualRead;
  }

  /// @brief Tests if this input stream is ready to be read.
  /// @return true if the next read() is guaranteed not to block for input, false otherwise.
  [[nodiscard]] auto ready() const -> bool override { return position_ < source_.size(); }

  /// @brief Resets the stream to the most recent mark position.
  auto reset() -> void override {
    if (!mark_set_) {
      position_ = 0;
    } else {
      position_ = mark_position_;
    }
  }

  /// @brief Skips over and discards n characters from the input stream.
  /// @param ns The number of characters to skip.
  /// @return The actual number of characters skipped.
  auto skip(const size_t ns) -> size_t override {
    const size_t charsToSkip = std::min(ns, source_.size() - position_);
    position_ += charsToSkip;
    return static_cast<int64_t>(charsToSkip);
  }

 private:
  std::string source_;
  size_t position_;
  size_t mark_position_;
  bool mark_set_;
};
}  // namespace fox
