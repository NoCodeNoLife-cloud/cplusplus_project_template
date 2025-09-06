#pragma once
#include <string>

#include "interface/IBuffer.hpp"

namespace fox {
/// @brief A character buffer that implements the IBuffer interface.
/// @details This class provides functionality for managing a buffer of characters,
///          including operations such as putting and getting characters, compacting
///          the buffer, and retrieving remaining unprocessed characters.
class CharBuffer final : public IBuffer {
 public:
  explicit CharBuffer(size_t cap);

  /// @brief Compacts the buffer by removing processed characters.
  /// @return void
  auto compact() -> void;

  /// @brief Puts a single character into the buffer.
  /// @param c The character to put into the buffer.
  /// @return void
  auto put(char c) -> void;

  /// @brief Puts a UTF-16 string into the buffer.
  /// @param src The UTF-16 string to put into the buffer.
  /// @return void
  auto put(const std::u16string& src) -> void;

  /// @brief Gets a single character from the buffer.
  /// @return The character retrieved from the buffer.
  auto get() -> char16_t;

  /// @brief Gets the remaining unprocessed characters as a string.
  /// @return The remaining characters in the buffer as a string.
  [[nodiscard]] auto getRemaining() const -> std::string;

 private:
  std::string buffer_{};
};
}  // namespace fox
