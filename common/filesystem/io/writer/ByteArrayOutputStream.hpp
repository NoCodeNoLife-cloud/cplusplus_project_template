#pragma once
#include "AbstractOutputStream.hpp"

namespace fox {
/// @brief A ByteArrayOutputStream is an output stream that writes data into a byte array.
/// The buffer automatically grows as data is written to it.
class ByteArrayOutputStream final : public AbstractOutputStream {
 public:
  ByteArrayOutputStream();
  explicit ByteArrayOutputStream(size_t size);

  /// @brief Writes a single byte to the stream.
  /// @param b The byte to write.
  auto write(std::byte b) -> void override;

  /// @brief Writes a sequence of bytes to the stream from the specified buffer.
  /// @param buffer The buffer containing bytes to write.
  /// @param offset The start offset in the buffer.
  /// @param len The number of bytes to write.
  auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;

  /// @brief Writes the complete contents of this byte array output stream to the specified output stream.
  /// @param out The output stream to which to write the data.
  auto writeTo(AbstractOutputStream& out) const -> void;

  /// @brief Resets the count field of this byte array output stream to zero.
  auto reset() -> void;

  /// @brief Creates a newly allocated byte array.
  /// @return The current contents of this output stream, as a byte array.
  [[nodiscard]] auto toByteArray() const -> std::vector<std::byte>;

  /// @brief Returns the current size of the buffer.
  /// @return The value of the count field, which is the number of valid bytes in the buffer.
  [[nodiscard]] auto size() const -> size_t;

  /// @brief Converts the buffer's contents into a string by decoding the bytes using the platform's default charset.
  /// @return A string representation of the buffer's contents.
  [[nodiscard]] auto toString() const -> std::string;

  /// @brief Closes this output stream and releases any system resources associated with this stream.
  auto close() -> void override;

  /// @brief Flushes this output stream and forces any buffered output bytes to be written out.
  auto flush() -> void override;

 protected:
  std::vector<std::byte> buf_;
  size_t count_{0};
};
}  // namespace fox
