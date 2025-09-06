#pragma once
#include <memory>

#include "AbstractReader.hpp"

namespace fox {
/// @brief A FilterReader is a subclass of AbstractReader that acts as a wrapper for another AbstractReader.
/// It can be used to extend the functionality of the wrapped reader by overriding methods as needed.
class FilterReader : public AbstractReader {
 public:
  explicit FilterReader(std::shared_ptr<AbstractReader> reader);
  ~FilterReader() override;

  /// @brief Close the stream and release any system resources associated with it.
  auto close() -> void override;

  /// @brief Marks the current position in this input stream.
  /// @param readAheadLimit Limit on the number of bytes that can be read ahead.
  auto mark(size_t readAheadLimit) -> void override;

  /// @brief Tests if this input stream supports the mark and reset methods.
  /// @return true if this stream type supports the mark and reset methods; false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override;

  /// @brief Reads the next character from this input stream.
  /// @return The next character from this input stream, or -1 if the end of the stream has been reached.
  auto read() -> int32_t override;

  /// @brief Reads characters into an array of characters.
  /// @param cBuf The buffer into which characters are to be read.
  /// @param off The offset at which to begin storing characters.
  /// @param len The maximum number of characters to read.
  /// @return The number of characters read, or -1 if the end of the stream has been reached.
  auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

  /// @brief Reads characters into an array of characters.
  /// @param cBuf The buffer into which characters are to be read.
  /// @return The number of characters read, or -1 if the end of the stream has been reached.
  auto read(std::vector<char>& cBuf) -> size_t override;

  /// @brief Tests if this input stream is ready to be read.
  /// @return true if the next read() is guaranteed not to block for input; false otherwise.
  [[nodiscard]] auto ready() const -> bool override;

  /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
  auto reset() -> void override;

  /// @brief Skips over and discards n bytes of data from this input stream.
  auto skip(size_t n) -> size_t override;

 protected:
  std::shared_ptr<AbstractReader> in_;
};
}  // namespace fox
