#pragma once
#include <string>
#include <vector>

namespace fox {
/// @brief A utility class for string manipulation operations.
/// This class provides static methods for common string operations such as splitting and concatenating strings.
class StringUtil {
 public:
  /// @brief Splits a string into a vector of strings based on a specified character.
  /// @param target The string to be split.
  /// @param split_char The character used as the delimiter for splitting.
  /// @return A vector of strings resulting from the split operation.
  static auto split(const std::string& target, char split_char) -> std::vector<std::string>;

  /// @brief Concatenates a vector of strings into a single string with a specified character between each element.
  /// @param source The vector of strings to be concatenated.
  /// @param split_char The character to insert between each concatenated string.
  /// @return A single string composed of all elements in the vector separated by the specified character.
  [[nodiscard]] static auto concatenate(const std::vector<std::string>& source, char split_char) -> std::string;
};
}  // namespace fox
