#pragma once
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A class representing a boolean value.
/// \details This class is a boolean value in an object form. It is a subclass of
/// the Object class and implements the Comparable interface. It provides a way
/// to perform boolean operations between two Boolean objects.
class Boolean final : public Object, public iface::IfaceComparable<Boolean> {
public:
  static const Boolean TRUE;
  static const Boolean FALSE;

  explicit Boolean(const bool value) : value_(value) {}

  ~Boolean() override = default;

  /// \brief Conversion operator to bool.
  /// \return The underlying boolean value of the Boolean object.
  /// \details This operator allows an Boolean object to be used in a boolean context.
  /// It returns the raw boolean value stored in the Boolean object.
  explicit operator bool() const {
    return value_;
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] auto toString() const -> std::string override {
    return std::format("{}", *this);
  }

  /// \brief Get the boolean value of the object.
  /// \return The boolean value of the object
  [[nodiscard]] auto boolValue() const -> bool {
    return value_;
  }

  /// \brief Compare this Boolean object with another.
  /// \param other The Boolean object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying boolean values directly.
  [[nodiscard]] auto compareTo(const Boolean& other) const -> int override {
    return value_ - other.value_;
  }

  /// \brief Parse a boolean value from a string.
  /// \param str The string to parse.
  /// \return A Boolean object representing the parsed value.
  /// \throws std::invalid_argument If the string is not "true" or "false".
  static auto parseBoolean(const std::string& str) -> Boolean {
    if (str == "true" || str == "TRUE") {
      return Boolean(true);
    }
    if (str == "false" || str == "FALSE") {
      return Boolean(false);
    }
    throw std::invalid_argument("Invalid input string for Boolean conversion");
  }

  /// \brief Get the boolean value of the object.
  /// \return The underlying boolean value of the Boolean object.
  /// \details This function returns the raw boolean value stored in the Boolean object.
  [[nodiscard]] auto booleanValue() const -> bool {
    return value_;
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function checks if the object is equal to another object. The
  /// function first checks if the objects are of the same type, and if so, it
  /// compares the underlying boolean values directly. Otherwise, it returns false.
  [[nodiscard]] auto equals(const Boolean& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function checks if the object is equal to another object by
  /// comparing the underlying boolean values directly.
  auto operator==(const Boolean& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if the Boolean object is not equal to another Boolean object
  /// \param other The other Boolean object
  /// \return True if the Boolean objects are not equal
  /// \details This function compares the underlying boolean values directly.
  auto operator!=(const Boolean& other) const -> bool {
    return !equals(other);
  }

private:
  bool value_{false};
  friend std::formatter<Boolean>;
};

inline const Boolean TRUE{true};
inline const Boolean FALSE{false};
}

template <>
struct std::formatter<common::entity::base_type::Boolean> {
  /// \brief Parse the format specifiers for the Boolean class.
  /// This function parses the format specifiers for the Boolean class.
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

  /// \brief Format the Boolean object into a string.
  /// This function formats the Boolean object using the provided format context.
  /// It generates a string representation of the Boolean object.
  /// \param content The Boolean object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Boolean& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output the Boolean object to the stream.
/// \param os The output stream.
/// \param content The Boolean object to output.
/// \return The output stream.
/// \details This function outputs the Boolean object to the stream. The output
/// is "true" or "false" depending on the value of the Boolean object.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Boolean& content) -> std::ostream& {
  return os << std::format("{}", content);
}
