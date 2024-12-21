#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A class representing a Character object.
/// \details This class is a part of the common library and represents a Character object.
/// It provides various methods for manipulating and comparing the Character object.
/// It is a final class and cannot be inherited.
class Character final : public Object, public iface::IfaceComparable<Character> {
public:
  explicit Character(const char value) : value_(value) {}

  ~Character() override = default;

  /// \brief Converts the Character object to a char.
  /// \return The underlying char value of this Character object.
  /// \details This function provides a convenient way to access the underlying
  /// char value of the Character object. It is useful when you need to convert
  /// a Character object to a char for use in a char-specific context.
  explicit operator char() const {
    return value_;
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] auto toString() const -> std::string override {
    return std::format("{}", *this);
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function checks if the object is equal to another object.
  /// The function first checks if the objects are of the same type, and if so,
  /// it compares the underlying char values directly. Otherwise, it returns
  /// false.
  [[nodiscard]] auto equals(const Character& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Compare this Character object with another.
  /// \param other The Character object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the
  /// specified object.
  /// \details This function compares the underlying char values directly.
  [[nodiscard]] auto compareTo(const Character& other) const -> int override {
    return value_ - other.value_;
  }

  /// \brief Check if a character is a letter
  /// \param c The character to check
  /// \return True if the character is a letter, false otherwise
  /// \details This function uses the standard library function `std::isalpha`
  /// to determine if the given character is a letter.
  static auto isLetter(const char c) -> bool {
    return std::isalpha(c);
  }

  /// \brief Check if a character is a digit
  /// \param c The character to check
  /// \return True if the character is a digit, false otherwise
  /// \details This function uses the standard library function `std::isdigit`
  /// to determine if the given character is a digit.
  static auto isDigit(const char c) -> bool {
    return std::isdigit(c);
  }

  /// \brief Check if a character is a letter or a digit
  /// \param c The character to check
  /// \return True if the character is a letter or a digit, false otherwise
  /// \details This function uses the standard library function `std::isalnum`
  /// to determine if the given character is a letter or a digit.
  static auto isLetterOrDigit(const char c) -> bool {
    return std::isalnum(c);
  }

  /// \brief Check if a character is uppercase
  /// \param c The character to check
  /// \return True if the character is uppercase, false otherwise
  /// \details This function uses the standard library function `std::isupper`
  /// to determine if the given character is uppercase.
  static auto isUpperCase(const char c) -> bool {
    return std::isupper(c);
  }

  /// \brief Check if a character is lowercase
  /// \param c The character to check
  /// \return True if the character is lowercase, false otherwise
  /// \details This function uses the standard library function `std::islower`
  /// to determine if the given character is lowercase.
  static auto isLowerCase(const char c) -> bool {
    return std::islower(c);
  }

  /// \brief Convert a character to uppercase
  /// \param c The character to convert
  /// \return The uppercase equivalent of the character
  /// \details This function uses the standard library function `std::toupper`
  /// to convert the given character to its uppercase form.
  static auto toUpperCase(const char c) -> int {
    return std::toupper(c);
  }

  /// \brief Convert a character to lowercase
  /// \param c The character to convert
  /// \return The lowercase equivalent of the character
  /// \details This function uses the standard library function `std::tolower`
  /// to convert the given character to its lowercase form.
  static auto toLowerCase(const char c) -> int {
    return std::tolower(c);
  }

  /// \brief Get the underlying character value
  /// \return The underlying character value
  /// \details This function returns the underlying character value of this
  /// Character object.
  [[nodiscard]] auto characterValue() const -> char {
    return value_;
  }

  /// \brief Check if this Character object is equal to another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if the objects are equal, false otherwise.
  /// \details This function compares the underlying char values directly.
  auto operator==(const Character& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if this Character object is not equal to another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if the objects are not equal, false otherwise.
  /// \details This function compares the underlying char values directly and returns true if they are different.
  auto operator!=(const Character& other) const -> bool {
    return !equals(other);
  }

  /// \brief Check if this Character object is less than another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if this Character object is less than the other Character object, false otherwise.
  /// \details This function compares the underlying char values directly.
  auto operator<(const Character& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Character object is greater than another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if this Character object is greater than the other Character object, false otherwise.
  /// \details This function compares the underlying char values directly.
  auto operator>(const Character& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Character object is less than or equal to another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if this Character object is less than or equal to the other Character object, false otherwise.
  /// \details This function compares the underlying char values directly.
  auto operator<=(const Character& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Character object is greater than or equal to another Character object.
  /// \param other The other Character object to compare with.
  /// \return True if this Character object is greater than or equal to the other Character object, false otherwise.
  /// \details This function compares the underlying char values directly.
  auto operator>=(const Character& other) const -> bool {
    return value_ >= other.value_;
  }

private:
  char value_{0};
  friend std::formatter<Character>;
};
}

template <>
struct std::formatter<common::entity::base_type::Character> {
  /// \brief Parse the format specifiers for the Character class.
  /// This function parses the format specifiers for the Character class.
  /// The format specifiers are as follows:
  /// \param ctx The format parse context.
  /// \return The parsed format specifiers.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Format the Character object into a string.
  /// This function formats the Character object using the provided format context.
  /// It generates a string representation of the Character object.
  /// \param content The Character object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  /// \details This function uses the standard library function `std::format_to`
  /// to format the given Character object into a string.
  static auto format(const common::entity::base_type::Character& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output the Character object to the stream.
/// This function outputs the Character object to the stream.
/// The output is the Unicode character represented by the Character object.
/// \param os The output stream.
/// \param content The Character object to output.
/// \return The output stream.
/// \details This function uses the standard library function `std::format` to format the given Character object into a string.
/// The string is then inserted into the output stream.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Character& content) -> std::ostream& {
  return os << std::format("{}", content);
}
