#pragma once
#include <stdexcept>

#include "AbstractReader.hpp"

namespace fox {
/// @brief A reader class that reads from a character array.
/// This class provides methods to read characters from an internal buffer,
/// supporting operations like reading single characters, skipping characters,
/// marking positions in the stream, and resetting to marked positions.
class CharArrayReader final : public AbstractReader {
 public:
  explicit CharArrayReader(const std::vector<char>& buffer);
  CharArrayReader(const std::vector<char>& buffer, size_t offset, size_t length);
  ~CharArrayReader() override;

  /// @brief Reads a single character.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff), or -1 if the end of the stream has been reached
  auto read() -> size_t override;

  /// @brief Reads characters into an array.
  /// @param b The buffer into which the read characters are stored
  /// @param off The offset at which to store the characters
  /// @param len The maximum number of characters to read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  auto read(std::vector<char>& b, size_t off, size_t len) -> size_t override;

  /// @brief Skips characters.
  /// @param n The number of characters to skip
  /// @return The number of characters actually skipped
  auto skip(size_t n) -> size_t override;

  /// @brief Tests if this reader can be read without blocking.
  /// @return True if this reader can be read without blocking, false otherwise
  [[nodiscard]] auto ready() const -> bool override;

  /// @brief Tests if this reader supports the mark() operation.
  /// @return True if this reader supports the mark() operation, false otherwise
  [[nodiscard]] auto markSupported() const -> bool override;

  /// @brief Marks the present position in the stream.
  /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
  auto mark(size_t readAheadLimit) -> void override;

  /// @brief Resets the stream to the most recent mark.
  auto reset() -> void override;

  /// @brief Closes the stream and releases any system resources associated with it.
  auto close() -> void override;

 private:
  std::vector<char> buf_;
  size_t pos_{0};
  size_t marked_pos_{0};
  size_t count_{0};
};

inline CharArrayReader::CharArrayReader(const std::vector<char>& buffer) : buf_(buffer), count_(buffer.size()) {}

inline CharArrayReader::CharArrayReader(const std::vector<char>& buffer, size_t offset, size_t length) {
  if (offset > buffer.size() || offset + length > buffer.size()) {
    throw std::invalid_argument("Invalid offset or length");
  }
  buf_.assign(buffer.begin() + static_cast<std::ptrdiff_t>(offset), buffer.begin() + static_cast<std::ptrdiff_t>(offset + length));
  count_ = length;
}

inline CharArrayReader::~CharArrayReader() = default;

inline size_t CharArrayReader::read() {
  if (pos_ >= count_) return -1;
  return buf_[pos_++];
}

inline auto CharArrayReader::read(std::vector<char>& b, size_t off, size_t len) -> size_t {
  if (pos_ >= count_) return -1;
  if (off >= b.size() || off + len > b.size()) {
    throw std::out_of_range("Invalid offset or length for target buffer");
  }
  const size_t toRead = std::min(len, count_ - pos_);
  std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead, b.begin() + static_cast<std::ptrdiff_t>(off));
  pos_ += toRead;
  return toRead;
}

inline size_t CharArrayReader::skip(size_t n) {
  const size_t skipped = std::min(n, count_ - pos_);
  pos_ += skipped;
  return skipped;
}

inline bool CharArrayReader::ready() const { return pos_ < count_; }

inline bool CharArrayReader::markSupported() const { return true; }

inline auto CharArrayReader::mark(size_t readAheadLimit) -> void { marked_pos_ = readAheadLimit; }

inline auto CharArrayReader::reset() -> void { pos_ = marked_pos_; }

inline auto CharArrayReader::close() -> void {
  buf_.clear();
  pos_ = 0;
  marked_pos_ = 0;
  count_ = 0;
}
}  // namespace fox
