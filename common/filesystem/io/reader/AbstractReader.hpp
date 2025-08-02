#pragma once
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IReadable.hpp"

namespace common {
class AbstractReader abstract : public ICloseable, public IReadable {
 public:
  ~AbstractReader() override;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff), or -1 if the end of the stream has been reached
  auto read() -> int32_t override;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer.
  /// @param off Offset at which to start storing characters.
  /// @param len Maximum number of characters to read.
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer.
  /// @return The number of characters read, or -1 if the end of the stream has been reached
  virtual auto read(std::vector<char>& cBuf) -> size_t;

  /// @brief Tests if this stream is ready to be read.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise
  [[nodiscard]] virtual auto markSupported() const -> bool;

  /// @brief Marks the present position in the stream.
  /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
  virtual auto mark(size_t readAheadLimit) -> void = 0;

  /// @brief Resets the stream to the most recent mark.
  virtual auto reset() -> void = 0;

  /// @brief Tests if the stream is ready to be read.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise
  [[nodiscard]] virtual auto ready() const -> bool;

  /// @brief Skips characters.
  /// @param n Number of characters to skip.
  /// @return The number of characters actually skipped
  virtual auto skip(size_t n) -> size_t;
};
}  // namespace common
