#pragma once
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
  ~AbstractReader() override = default;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff), or -1 if the end of the stream has been reached
  auto read() -> int32_t override {
    std::vector<char> buffer(1);
    if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1) {
      return -1;
    }
    return buffer[0];
  }

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer.
  /// @param off Offset at which to start storing characters.
  /// @param len Maximum number of characters to read.
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer.
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf) -> size_t { return read(cBuf, 0, static_cast<int32_t>(cBuf.size())); }

  /// @brief Tests if this stream is ready to be read.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise
  [[nodiscard]] virtual auto markSupported() const -> bool { return false; }

  /// @brief Marks the present position in the stream.
  /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
  virtual auto mark(size_t readAheadLimit) -> void = 0;

  /// @brief Resets the stream to the most recent mark.
  virtual auto reset() -> void = 0;

  /// @brief Tests if the stream is ready to be read.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise
  [[nodiscard]] virtual auto ready() const -> bool { return true; }

  /// @brief Skips characters.
  /// @param n Number of characters to skip.
  /// @return The number of characters actually skipped
  virtual auto skip(const size_t n) -> size_t {
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
};
}  // namespace fox
