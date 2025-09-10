#pragma once
#include <algorithm>
#include <cstddef>
#include <vector>

#include "AbstractOutputStream.hpp"

namespace fox {
/// @brief A ByteArrayOutputStream is an output stream that writes data into a byte array.
/// The buffer automatically grows as data is written to it.
class ByteArrayOutputStream final : public AbstractOutputStream {
 public:
  ByteArrayOutputStream() : buf_(32), count_(0) {}

  explicit ByteArrayOutputStream(const size_t size) : buf_(size), count_(0) {}

  /// @brief Writes a single byte to the stream.
  /// @param b The byte to write.
  auto write(const std::byte b) -> void override {
    if (count_ == buf_.size()) {
      buf_.resize(buf_.size() * 2);
    }
    buf_[count_++] = b;
  }

  /// @brief Writes a sequence of bytes to the stream from the specified buffer.
  /// @param buffer The buffer containing bytes to write.
  /// @param offset The start offset in the buffer.
  /// @param len The number of bytes to write.
  auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void override {
    if (offset + len > buffer.size()) {
      throw std::out_of_range("Buffer offset/length out of range");
    }
    if (count_ + len > buf_.size()) {
      buf_.resize(std::max(buf_.size() * 2, count_ + len));
    }
    std::copy_n(buffer.begin() + static_cast<std::vector<std::byte>::difference_type>(offset), len, buf_.begin() + static_cast<std::vector<std::byte>::difference_type>(count_));
    count_ += len;
  }

  /// @brief Writes the complete contents of this byte array output stream to the specified output stream.
  /// @param out The output stream to which to write the data.
  auto writeTo(AbstractOutputStream& out) const -> void { out.write(buf_, 0, count_); }

  /// @brief Resets the count field of this byte array output stream to zero.
  auto reset() -> void { count_ = 0; }

  /// @brief Creates a newly allocated byte array.
  /// @return The current contents of this output stream, as a byte array.
  [[nodiscard]] auto toByteArray() const -> std::vector<std::byte> { return {buf_.begin(), buf_.begin() + static_cast<std::vector<std::byte>::difference_type>(count_)}; }

  /// @brief Returns the current size of the buffer.
  /// @return The value of the count field, which is the number of valid bytes in the buffer.
  [[nodiscard]] auto size() const -> size_t { return count_; }

  /// @brief Converts the buffer's contents into a string by decoding the bytes using the platform's default charset.
  /// @return A string representation of the buffer's contents.
  [[nodiscard]] auto toString() const -> std::string { return {reinterpret_cast<const char*>(buf_.data()), count_}; }

  /// @brief Closes this output stream and releases any system resources associated with this stream.
  auto close() -> void override {}

  /// @brief Flushes this output stream and forces any buffered output bytes to be written out.
  auto flush() -> void override {
    // No operation for ByteArrayOutputStream.
  }

 protected:
  std::vector<std::byte> buf_;
  size_t count_;
};
}  // namespace fox