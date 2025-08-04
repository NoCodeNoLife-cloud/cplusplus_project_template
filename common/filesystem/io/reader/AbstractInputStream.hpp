#pragma once
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"

namespace common {
/// @brief Abstract base class for all input streams.
class AbstractInputStream abstract : public ICloseable {
 public:
  ~AbstractInputStream() override;

  /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking.
  [[nodiscard]] virtual auto available() -> size_t = 0;

  /// @brief Marks the current position in this input stream.
  virtual auto mark(int32_t readLimit) -> void;

  /// @brief Tells whether this stream supports the mark() operation.
  [[nodiscard]] virtual auto markSupported() const -> bool;

  /// @brief Reads the next byte of data from the input stream.
  virtual auto read() -> std::byte = 0;

  /// @brief Reads up to len bytes of data from the input stream into an array of bytes.
  virtual auto read(std::vector<std::byte>& buffer) -> size_t;

  /// @brief Reads up to len bytes of data from the input stream into an array of bytes.
  /// @param buffer The buffer into which the data is read.
  /// @param offset The start offset in the destination array buffer.
  /// @param len The maximum number of bytes to read.
  /// @return The total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
  virtual auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t;

  /// @brief Repositions this stream to the position at the time the mark() method was last called on this input stream.
  virtual auto reset() -> void;

  /// @brief Skips over and discards n bytes of data from this input stream.
  virtual auto skip(size_t n) -> size_t;
};
}  // namespace common
