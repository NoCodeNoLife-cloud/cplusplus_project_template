#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A wrapper class for primitive type int.
/// \details This class provides a way to treat int as a generic object.
/// It is used to represent an immutable signed 32-bit integer.
class Integer final : public Object, public iface::IfaceComparable<Integer> {
public:
  static constexpr int MIN_VALUE = std::numeric_limits<int>::min();
  static constexpr int MAX_VALUE = std::numeric_limits<int>::max();

  explicit Integer(const int value) : value_(value) {}

  ~Integer() override = default;

  /// \brief Convert the Integer object to a raw int value.
  /// \return The underlying int value of the Integer object.
  /// \details This operator allows the Integer object to be implicitly converted to an int type.
  explicit operator int() const {
    return value_;
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] std::string toString() const override {
    return std::format("{}", *this);
  }

  /// \brief Get the int value of the object.
  /// \return The underlying int value of the Integer object.
  /// \details This function returns the raw int value stored in the Integer object.
  [[nodiscard]] auto intValue() const -> int {
    return value_;
  }

  /// \brief Parse an integer value from a string.
  /// \param str The string to parse.
  /// \return An Integer object representing the parsed value.
  /// \throws std::invalid_argument If the string is not a valid integer.
  /// \throws std::out_of_range If the parsed value is out of range for the Integer object.
  static auto parseInt(const std::string& str) -> Integer {
    try {
      size_t idx;
      const int result = std::stoi(str, &idx);
      if (idx != str.size()) {
        throw std::invalid_argument("Invalid input string");
      }
      return Integer(result);
    }
    catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range");
    }
  }

  /// \brief Compare this Integer object with another.
  /// \param other The Integer object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying int values directly.
  [[nodiscard]] auto compareTo(const Integer& other) const -> int override {
    return value_ - other.value_;
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function checks if the object is equal to another object. The
  /// function first checks if the objects are of the same type, and if so, it
  /// compares the underlying int values directly. Otherwise, it returns false.
  [[nodiscard]] bool equals(const Integer& other) const override {
    return value_ == other.value_;
  }

  /// \brief Check if this Integer object is equal to another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if the objects are equal, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator==(const Integer& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if this Integer object is not equal to another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if the objects are not equal, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator!=(const Integer& other) const -> bool {
    return !equals(other);
  }

  /// \brief Check if this Integer object is less than another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if this Integer object is less than the other Integer object, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator<(const Integer& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Integer object is greater than another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if this Integer object is greater than the other Integer object, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator>(const Integer& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Integer object is less than or equal to another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if this Integer object is less than or equal to the other Integer object, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator<=(const Integer& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Integer object is greater than or equal to another Integer object.
  /// \param other The other Integer object to compare with.
  /// \return True if this Integer object is greater than or equal to the other Integer object, false otherwise.
  /// \details This function compares the underlying int values directly.
  auto operator>=(const Integer& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Add two Integer objects.
  /// \param other The other Integer object.
  /// \return A new Integer object representing the sum of this object and the other.
  auto operator+(const Integer& other) const -> Integer {
    return Integer(this->value_ + other.value_);
  }

  /// \brief Subtract an Integer object from this object.
  /// \param other The other Integer object.
  /// \return A new Integer object representing the difference between this object and the other.
  auto operator-(const Integer& other) const -> Integer {
    return Integer(this->value_ - other.value_);
  }

  /// \brief Multiply this object by another Integer object.
  /// \param other The other Integer object.
  /// \return A new Integer object representing the product of this object and the other.
  auto operator*(const Integer& other) const -> Integer {
    return Integer(this->value_ * other.value_);
  }

  /// \brief Divide this object by another Integer object.
  /// \param other The other Integer object.
  /// \return A new Integer object representing the quotient of this object divided by the other.
  /// \throws std::invalid_argument If division by zero is attempted.
  auto operator/(const Integer& other) const -> Integer {
    if (other.value_ == 0) {
      throw std::invalid_argument("Division by zero is not allowed.");
    }
    return Integer(this->value_ / other.value_);
  }

private:
  int value_{0};
  friend std::formatter<Integer>;
};
}

template <>
struct std::formatter<common::entity::base_type::Integer> {
  /// \brief A custom formatter for Integer objects.
  /// \details This custom formatter simply calls std::format_to with the underlying int value.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Format the Integer object into a string.
  /// \details This function formats the Integer object using the provided format context.
  /// It generates a string representation of the Integer object.
  /// \param content The Integer object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Integer& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output stream operator overload for Integer objects.
/// \param os The output stream to write to.
/// \param content The Integer object to write.
/// \return The output stream after writing the Integer object.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Integer& content) -> std::ostream& {
  return os << std::format("{}", content);
}
