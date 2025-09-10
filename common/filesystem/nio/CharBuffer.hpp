#pragma once
#include <algorithm>
#include <span>
#include <stdexcept>
#include <string>

#include "interface/IBuffer.hpp"

namespace fox {
/// @brief A character buffer that implements the IBuffer interface.
/// @details This class provides functionality for managing a buffer of characters,
///          including operations such as putting and getting characters, compacting
///          the buffer, and retrieving remaining unprocessed characters.
class CharBuffer final : public IBuffer {
 public:
  explicit CharBuffer(size_t cap) {
    position_ = 0;
    limit_ = cap;
    capacity_ = cap;
    buffer_ = std::string(cap, u'\0');
  }

  /// @brief Compacts the buffer by removing processed characters.
  /// @return void
  auto compact() -> void {
    if (position_ > 0) {
      std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_), buffer_.begin());
      limit_ -= position_;
      position_ = 0;
    }
  }

  /// @brief Puts a single character into the buffer.
  /// @param c The character to put into the buffer.
  /// @return void
  auto put(char c) -> void {
    if (position_ >= limit_) {
      throw std::overflow_error("Buffer overflow.");
    }
    buffer_[position_++] = c;
  }

  /// @brief Puts a UTF-16 string into the buffer.
  /// @param src The UTF-16 string to put into the buffer.
  /// @return void
  auto put(const std::u16string& src) -> void {
    if (position_ + src.size() > limit_) {
      throw std::overflow_error("Buffer overflow.");
    }
    std::ranges::copy(src, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
    position_ += src.size();
  }

  /// @brief Gets a single character from the buffer.
  /// @return The character retrieved from the buffer.
  auto get() -> char16_t {
    if (position_ >= limit_) {
      throw std::underflow_error("Buffer underflow.");
    }
    return buffer_[position_++];
  }

  /// @brief Gets the remaining unprocessed characters as a string.
  /// @return The remaining characters in the buffer as a string.
  [[nodiscard]] auto getRemaining() const -> std::string { return {buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)}; }

 private:
  std::string buffer_{};
};
}  // namespace fox