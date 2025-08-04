#pragma once
#include <memory>

#include "AbstractInputStream.hpp"

namespace common {
/// @brief A filter stream is a stream that filters another input stream.
/// This class is the basis for all input streams that filter another input stream.
class FilterInputStream : public AbstractInputStream {
 public:
  explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream);
  ~FilterInputStream() override;

  /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking.
  /// @return the number of bytes that can be read (or skipped over) from this input stream without blocking.
  auto available() -> size_t override;

  /// @brief Marks the current position in this input stream.
  /// @param readLimit the maximum number of bytes that can be read before the mark position becomes invalid.
  auto mark(int32_t readLimit) -> void override;

  /// @brief Tests if this input stream supports the mark and reset methods.
  /// @return true if this input stream supports the mark and reset methods; false otherwise.
  [[nodiscard]] auto markSupported() const -> bool override;

  /// @brief Reads the next byte of data from this input stream.
  /// @return the next byte of data, or -1 if the end of the stream is reached.
  auto read() -> std::byte override;

  /// @brief Reads up to len bytes of data from this input stream into an array of bytes.
  /// @param buffer the buffer into which the data is read.
  auto read(std::vector<std::byte>& buffer) -> size_t override;

  /// @brief Reads up to len bytes of data from this input stream into an array of bytes.
  /// @param buffer the buffer into which the data is read.
  /// @param offset the start offset in the destination array buffer.
  /// @param len the maximum number of bytes to read.
  /// @return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
  auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;

  /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
  auto reset() -> void override;

  /// @brief Skips over and discards n bytes of data from this input stream.
  /// @param n the number of bytes to be skipped.
  auto skip(size_t n) -> size_t override;

  /// @brief Closes this input stream and releases any system resources associated with the stream.
  auto close() -> void override;

 protected:
  std::unique_ptr<AbstractInputStream> input_stream_;
};
}  // namespace common
