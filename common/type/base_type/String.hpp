#pragma once
#include "Object.hpp"

namespace common {
class String final : public Object {
 public:
  String();
  ~String() override;
  explicit String(const char* str);
  explicit String(std::string str);
  String(const String& other);
  String(String&& other) noexcept;
  String& operator=(const String& other);
  String& operator=(String&& other) noexcept;

  /// @brief Converts the String to std::string
  explicit operator std::string() const;

  /// @brief Returns a hash code for this string
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Returns a string representation of the object
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Returns the character at the specified index
  /// @param index The index of the character to return
  [[nodiscard]] auto charAt(int32_t index) const -> char;

  /// @brief Returns the length of this string
  [[nodiscard]] auto length() const -> size_t;

  /// @brief Returns a new string that is a substring of this string
  /// @param beginIndex The beginning index, inclusive
  /// @param endIndex The ending index, exclusive
  [[nodiscard]] auto substring(int32_t beginIndex, int32_t endIndex) const -> String;

  /// @brief Concatenates the specified string to the end of this string
  /// @param str The string to concatenate
  [[nodiscard]] auto concat(const String& str) const -> String;

  /// @brief Compares two strings lexicographically, ignoring case differences
  /// @param anotherString The string to compare to
  [[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const -> int32_t;

  /// @brief Tests if this string has no characters
  [[nodiscard]] auto isEmpty() const -> bool;

  /// @brief Tests if this string contains the specified substring
  /// @param str The substring to search for
  [[nodiscard]] auto contains(const String& str) const -> bool;

  /// @brief Returns a new string resulting from replacing all occurrences of oldChar with newChar
  /// @param oldChar The old character
  /// @param newChar The new character
  [[nodiscard]] auto replace(char oldChar, char newChar) const -> String;

  /// @brief Converts all characters in this string to lower case
  [[nodiscard]] auto toLowerCase() const -> String;

  /// @brief Converts all characters in this string to upper case
  [[nodiscard]] auto toUpperCase() const -> String;

  /// @brief Returns a copy of the string with leading and trailing whitespace omitted
  [[nodiscard]] auto trim() const -> String;

  /// @brief Returns the underlying std::string
  [[nodiscard]] auto toStdString() const -> std::string;

  /// @brief Returns the character (Unicode code point) at the specified index
  /// @param index The index to the char values
  [[nodiscard]] auto codePointAt(int32_t index) const -> int32_t;

  /// @brief Returns the character (Unicode code point) before the specified index
  /// @param index The index following the code point that should be returned
  [[nodiscard]] auto codePointBefore(int32_t index) const -> int32_t;

  /// @brief Returns the number of Unicode code points in the specified text range
  /// @param beginIndex The index to the first char of the text range
  /// @param endIndex The index after the last char of the text range
  [[nodiscard]] auto codePointCount(int32_t beginIndex, int32_t endIndex) const -> int32_t;

  /// @brief Returns the index within this string of the first occurrence of the specified character
  /// @param ch The character to search for
  [[nodiscard]] auto indexOf(char ch) const -> int32_t;

  /// @brief Returns the index within this string of the first occurrence of the specified character, starting the search at fromIndex
  /// @param ch The character to search for
  /// @param fromIndex The index to start the search from
  [[nodiscard]] auto indexOf(char ch, int32_t fromIndex) const -> int32_t;

  /// @brief Returns the index within this string of the first occurrence of the specified substring
  /// @param str The substring to search for
  [[nodiscard]] auto indexOf(const String& str) const -> int32_t;

  /// @brief Returns the index within this string of the first occurrence of the specified substring, starting at the specified index
  /// @param str The substring to search for
  /// @param fromIndex The index to start the search from
  [[nodiscard]] auto indexOf(const String& str, int32_t fromIndex) const -> int32_t;

  /// @brief Returns the index within this string of the last occurrence of the specified character
  /// @param ch The character to search for
  [[nodiscard]] auto lastIndexOf(char ch) const -> int32_t;

  /// @brief Returns the index within this string of the last occurrence of the specified character, searching backward starting at fromIndex
  /// @param ch The character to search for
  /// @param fromIndex The index to start the backward search from
  [[nodiscard]] auto lastIndexOf(char ch, int32_t fromIndex) const -> int32_t;

  /// @brief Returns the index within this string of the rightmost occurrence of the specified substring
  /// @param str The substring to search for
  [[nodiscard]] auto lastIndexOf(const String& str) const -> int32_t;

  /// @brief Returns the index within this string of the last occurrence of the specified substring, searching backward starting at fromIndex
  /// @param str The substring to search for
  /// @param fromIndex The index to start the backward search from
  [[nodiscard]] auto lastIndexOf(const String& str, int32_t fromIndex) const -> int32_t;

  /// @brief Tests if this string matches the given regular expression
  /// @param regex The regular expression to match against
  [[nodiscard]] auto matches(const std::string& regex) const -> bool;

  /// @brief Replaces each substring of this string that matches the given regular expression with the given replacement
  /// @param regex The regular expression to match against
  /// @param replacement The string to be substituted for each match
  [[nodiscard]] auto replaceAll(const std::string& regex, const std::string& replacement) const -> String;

  /// @brief Replaces the first substring of this string that matches the given regular expression with the given replacement
  /// @param regex The regular expression to match against
  /// @param replacement The string to be substituted for the first match
  [[nodiscard]] auto replaceFirst(const std::string& regex, const std::string& replacement) const -> String;

  /// @brief Splits this string around matches of the given regular expression
  /// @param regex The regular expression to split around
  [[nodiscard]] auto split(const std::string& regex) const -> std::vector<String>;

  /// @brief Splits this string around matches of the given regular expression with a limit
  /// @param regex The regular expression to split around
  /// @param limit The result threshold
  [[nodiscard]] auto split(const std::string& regex, int32_t limit) const -> std::vector<String>;

  /// @brief Returns the string representation of the boolean argument
  /// @param b A boolean
  static auto valueOf(bool b) -> String;

  /// @brief Returns the string representation of the char argument
  /// @param c A character
  static auto valueOf(char c) -> String;

  /// @brief Returns the string representation of the char array argument
  /// @param data A character array
  static auto valueOf(const char* data) -> String;

  /// @brief Returns the string representation of the int argument
  /// @param i An integer
  static auto valueOf(int32_t i) -> String;

  /// @brief Returns the string representation of the long argument
  /// @param l A long
  static auto valueOf(int64_t l) -> String;

  /// @brief Returns the string representation of the float argument
  /// @param f A float
  static auto valueOf(float f) -> String;

  /// @brief Returns the string representation of the double argument
  /// @param d A double
  static auto valueOf(double d) -> String;

  /// @brief Returns the string representation of the String argument
  /// @param str A string
  static auto valueOf(const String& str) -> String;

  /// @brief Tests if two string regions are equal
  /// @param tOffset The starting offset of the subregion in this string
  /// @param other The string argument
  /// @param oOffset The starting offset of the subregion in the string argument
  /// @param len The number of characters to compare
  [[nodiscard]] auto regionMatches(int32_t tOffset, const String& other, int32_t oOffset, int32_t len) const -> bool;

  /// @brief Tests if two string regions are equal, optionally ignoring case
  /// @param ignoreCase If true, ignore case when comparing characters
  /// @param tOffset The starting offset of the subregion in this string
  /// @param other The string argument
  /// @param oOffset The starting offset of the subregion in the string argument
  /// @param len The number of characters to compare
  [[nodiscard]] auto regionMatches(bool ignoreCase, int32_t tOffset, const String& other, int32_t oOffset, int32_t len) const -> bool;

  /// @brief Compares two strings lexicographically
  /// @param other The string to compare to
  auto operator<=>(const String& other) const -> std::partial_ordering;

  /// @brief Compares this string to the specified object
  /// @param other The string to compare to
  auto operator==(const String& other) const -> bool;

  /// @brief Concatenates this string with the specified string
  /// @param str The string to concatenate
  auto operator+(const String& str) const -> String;

 private:
  friend std::formatter<String>;
  std::string value_{};
};
}  // namespace common

template <>
struct std::formatter<common::String> : common::GenericFormatter<common::String, &common::String::value_> {};
