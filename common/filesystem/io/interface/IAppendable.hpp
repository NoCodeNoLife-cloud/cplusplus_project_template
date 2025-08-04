#pragma once
#include <string>

namespace common {
/// @brief Interface for appendable objects.
/// @tparam T The type of the object that implements this interface.
template <typename T>
class IAppendable abstract {
 public:
  virtual ~IAppendable() = default;

  /// @brief Append a character to the string.
  /// @param c The character to append.
  /// @return A reference to the string.
  virtual auto append(char c) -> T& = 0;

  /// @brief Append a string to the string.
  /// @param str The string to append.
  /// @return A reference to the string.
  virtual auto append(const std::string& str) -> T& = 0;

  /// @brief Append a substring to the string.
  /// @param str The string to append.
  /// @param start The start index of the substring.
  /// @param end The end index of the substring.
  /// @return A reference to the string.
  virtual auto append(const std::string& str, size_t start, size_t end) -> T& = 0;
};
}  // namespace common
