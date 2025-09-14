#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IReadable.hpp"

namespace fox {

/// @brief Abstract base class for reading character streams.
/// This class provides a standard interface for reading character data from various sources.
/// It implements the ICloseable and IReadable interfaces and provides standard implementations
/// for some common reading operations.
class AbstractReader : public ICloseable, public IReadable {
 public:
  /// @brief Virtual destructor for proper cleanup of derived classes
  ~AbstractReader() override;

  /// @brief Read a single character.
  /// This method reads the next character from the input stream.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
  ///         or -1 if the end of the stream has been reached
  auto read() -> size_t override;

  /// @brief Read characters into an array.
  /// This method reads up to 'len' characters from the input stream into the buffer 'cBuf'
  /// starting at the specified offset.
  /// @param cBuf Destination buffer to store the characters read
  /// @param off Offset at which to start storing characters
  /// @param len Maximum number of characters to read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;

  /// @brief Read characters into an array.
  /// This method reads characters from the input stream into the entire buffer 'cBuf'.
  /// @param cBuf Destination buffer to store the characters read
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf) -> size_t;

  /// @brief Tests if this stream supports the mark and reset methods.
  /// @return True if this stream supports the mark and reset methods, false otherwise
  [[nodiscard]] virtual auto markSupported() const -> bool;

  /// @brief Marks the present position in the stream.
  /// This method marks the current position in the input stream, allowing a subsequent
  /// call to reset to return to this position.
  /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark
  virtual auto mark(size_t readAheadLimit) -> void = 0;

  /// @brief Resets the stream to the most recent mark.
  /// This method repositions the stream to the position at the time the mark method was last called.
  virtual auto reset() -> void = 0;

  /// @brief Tests if the stream is ready to be read.
  /// This method checks whether the next read operation will block for input.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise
  [[nodiscard]] virtual auto ready() const -> bool;

  /// @brief Skips characters.
  /// This method skips over and discards n characters from the input stream.
  /// @param n Number of characters to skip
  /// @return The number of characters actually skipped
  virtual auto skip(const size_t n) -> size_t;
};

inline AbstractReader::~AbstractReader() = default;

inline auto AbstractReader::read() -> size_t {
  std::vector<char> buffer(1);
  if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1) {
    return -1;
  }
  return buffer[0];
}

inline auto AbstractReader::read(std::vector<char>& cBuf) -> size_t { return read(cBuf, 0, static_cast<int32_t>(cBuf.size())); }

inline auto AbstractReader::markSupported() const -> bool { return false; }

inline auto AbstractReader::ready() const -> bool { return true; }

inline auto AbstractReader::skip(const size_t n) -> size_t {
  size_t skipped = 0;
  while (skipped < n) {
    std::vector<char> buffer(1024);
    const size_t toRead = std::min(n - skipped, buffer.size());
    const size_t readCount = read(buffer, 0, static_cast<int32_t>(toRead));
    if (readCount == -1) break;
    skipped += readCount;
  }
  return skipped;
}
}  // namespace fox
