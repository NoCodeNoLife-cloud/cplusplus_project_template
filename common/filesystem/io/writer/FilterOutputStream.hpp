#pragma once
#include "AbstractOutputStream.hpp"

namespace fox {
/// @brief A filter output stream that wraps another output stream.
/// This class provides a base for output stream filters that modify or enhance
/// the behavior of the underlying output stream.
class FilterOutputStream : public AbstractOutputStream {
 public:
  explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream);
  ~FilterOutputStream() override;

  /// @brief Writes a single byte to the output stream.
  /// @param b The byte to write.
  auto write(std::byte b) -> void override;

  /// @brief Writes all bytes from the given buffer to the output stream.
  /// @param buffer The buffer containing bytes to write.
  auto write(const std::vector<std::byte>& buffer) -> void override;

  /// @brief Writes a specified number of bytes from the buffer starting at the given offset.
  /// @param buffer The buffer containing bytes to write.
  /// @param offset The starting position in the buffer.
  /// @param len The number of bytes to write.
  auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;

  /// @brief Flushes the output stream, ensuring all buffered data is written.
  auto flush() -> void override;

  /// @brief Closes the output stream and releases any associated resources.
  auto close() -> void override;

 protected:
  std::shared_ptr<AbstractOutputStream> output_stream_;
};
}  // namespace fox
