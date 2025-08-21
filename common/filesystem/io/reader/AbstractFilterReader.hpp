#pragma once
#include <memory>

#include "AbstractReader.hpp"

namespace common {
/// @brief AbstractFilterReader is an  base class that serves as a filter for other readers.
/// It implements the AbstractReader interface and delegates all operations to an underlying reader.
/// This class follows the decorator pattern, allowing additional functionality to be added to readers
/// by wrapping them with filter implementations.
class AbstractFilterReader final : public AbstractReader {
 public:
  explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader);
  ~AbstractFilterReader() override;

  /// @brief Read a single character.
  /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
  auto read() -> int32_t override;

  /// @brief Read characters into an array.
  /// @param cBuf Destination buffer.
  /// @param off Offset at which to start storing characters.
  /// @param len Maximum number of characters to read.
  /// @return The number of characters read, or -1 if the end of the stream has been reached.
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

  /// @brief Skip characters.
  /// @param n The number of characters to skip.
  /// @return The number of characters actually skipped.
  auto skip(size_t n) -> size_t override;

  /// @brief Tell whether this stream is ready to be read.
  /// @return True if the next read() is guaranteed not to block for input, false otherwise.
  [[nodiscard]] auto ready() const -> bool override;

  /// @brief Tell whether this stream supports the mark() operation.
  /// @return True if this stream type supports the mark() operation, false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override;

  /// @brief Mark the present position in the stream.
  /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
  auto mark(size_t readAheadLimit) -> void override;

  /// @brief Reset the stream to the most recent mark.
  auto reset() -> void override;

  /// @brief Close the stream.
  auto close() -> void override;

 protected:
  std::unique_ptr<AbstractReader> reader_;
};
}  // namespace common
