#pragma once
#include <string>

namespace common {
/// @brief A utility class for formatting and parsing dates based on a pattern.
/// The SimpleDateFormatter class provides methods to format std::tm objects into
/// strings and parse strings back into std::tm objects using a specified pattern.
/// It supports various date and time format specifiers similar to those used in
/// strftime and strptime functions.
class SimpleDateFormatter {
 public:
  explicit SimpleDateFormatter(const std::string& pattern);

  /// @brief Applies a new pattern to the date formatter.
  /// @param newPattern The new pattern to apply.
  auto applyPattern(const std::string& newPattern) -> void;

  /// @brief Retrieves the current pattern used by the date formatter.
  /// @return The current pattern as a string.
  [[nodiscard]] auto toPattern() const -> std::string;

  /// @brief Formats a given date according to the current pattern.
  /// @param date The date to format.
  /// @return The formatted date as a string.
  [[nodiscard]] auto format(const std::tm& date) const -> std::string;

  /// @brief Parses a date string according to the current pattern.
  /// @param dateStr The date string to parse.
  /// @return The parsed date as a std::tm structure.
  [[nodiscard]] auto parse(const std::string& dateStr) const -> std::tm;

  /// @brief Compares this formatter with another for equality.
  /// @param other The other formatter to compare with.
  /// @return True if both formatters are equal, false otherwise.
  [[nodiscard]] auto equals(const SimpleDateFormatter& other) const -> bool;

  /// @brief Computes the hash code for this formatter.
  /// @return The hash code as a size_t.
  [[nodiscard]] auto hashCode() const -> size_t;

 private:
  std::string pattern_;

  /// @brief Validates a given pattern string.
  /// @param pat The pattern to validate.
  static auto validatePattern(const std::string& pat) -> void;
};
}  // namespace common
