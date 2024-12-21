#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A class representing a signed 64-bit integer.
/// \details This class contains a signed 64-bit integer.
/// It is a wrapper class for the built-in type int64_t.
class Long final : public Object, public iface::IfaceComparable<Long> {
public:
  static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
  static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();

  explicit Long(const int64_t value) : value_(value) {}

  ~Long() override = default;

  /// \brief Get the long value of the object.
  /// \return The underlying int64_t value of the Long object.
  /// \details This function returns the raw long value stored in the Long object.
  explicit operator long() const {
    return static_cast<long>(value_);
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] auto toString() const -> std::string override {
    return std::format("{}", *this);
  }

  /// \brief Get the long value of the object.
  /// \return The underlying int64_t value of the Long object.
  /// \details This function returns the raw long value stored in the Long object.
  [[nodiscard]] auto longValue() const -> int64_t {
    return value_;
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function checks if the object is equal to another object. The
  /// function first checks if the objects are of the same type, and if so, it
  /// compares the underlying int64_t values directly. Otherwise, it returns false.
  [[nodiscard]] auto equals(const Long& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Compare this Long object with another.
  /// \param other The Long object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying int64_t values directly.
  [[nodiscard]] auto compareTo(const Long& other) const -> int override {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  /// \brief Parse a long value from a string.
  /// \param str The string to parse.
  /// \return A Long object representing the parsed value.
  /// \throws std::invalid_argument If the string is not a valid long.
  /// \throws std::out_of_range If the parsed value is out of range for the Long object.
  /// \details This function parses the string using `std::stoll`.
  static auto parseLong(const std::string& str) -> Long {
    try {
      const int64_t result = std::stoll(str);
      return Long(result);
    }
    catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Long conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Long");
    }
  }

  /// \brief Check if this Long object is equal to another.
  /// \param other The Long object to compare with.
  /// \return True if the two objects are equal, false otherwise.
  /// \details This function checks if the two objects are equal by comparing their underlying int64_t values directly.
  auto operator==(const Long& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if this Long object is not equal to another.
  /// \param other The Long object to compare with.
  /// \return True if the two objects are not equal, false otherwise.
  /// \details This function checks if the two objects are not equal by comparing their underlying int64_t values
  /// directly.
  auto operator!=(const Long& other) const -> bool {
    return !equals(other);
  }

  /// \brief Check if this Long object is less than another.
  /// \param other The Long object to compare with.
  /// \return True if this object is less than the other object, false otherwise.
  /// \details This function checks if the underlying int64_t values are in order.
  auto operator<(const Long& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Long object is greater than another.
  /// \param other The Long object to compare with.
  /// \return True if this object is greater than the other object, false otherwise.
  /// \details This function checks if the underlying int64_t values are in order.
  auto operator>(const Long& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Long object is less than or equal to another.
  /// \param other The Long object to compare with.
  /// \return True if this object is less than or equal to the other object, false otherwise.
  /// \details This function checks if the underlying int64_t values are in order.
  auto operator<=(const Long& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Long object is greater than or equal to another.
  /// \param other The Long object to compare with.
  /// \return True if this object is greater than or equal to the other object, false otherwise.
  /// \details This function checks if the underlying int64_t values are in order.
  auto operator>=(const Long& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Add another Long object to this Long object.
  /// \param other The Long object to add.
  /// \return A new Long object with the result of the addition.
  /// \details This function adds the underlying int64_t values directly.
  auto operator+(const Long& other) const -> Long {
    return Long(this->value_ + other.value_);
  }

  /// \brief Subtract another Long object from this Long object.
  /// \param other The Long object to subtract.
  /// \return A new Long object with the result of the subtraction.
  /// \details This function subtracts the underlying int64_t values directly.
  auto operator-(const Long& other) const -> Long {
    return Long(this->value_ - other.value_);
  }

  /// \brief Multiply another Long object with this Long object.
  /// \param other The Long object to multiply with.
  /// \return A new Long object with the result of the multiplication.
  /// \details This function multiplies the underlying int64_t values directly.
  auto operator*(const Long& other) const -> Long {
    return Long(this->value_ * other.value_);
  }

  /// \brief Divide this Long object by another Long object.
  /// \param other The Long object to divide by.
  /// \return A new Long object with the result of the division.
  /// \details This function divides the underlying int64_t values directly.
  /// \throws std::overflow_error If the divisor is zero.
  auto operator/(const Long& other) const -> Long {
    if (other.value_ == 0) {
      throw std::overflow_error("Division by zero");
    }
    return Long(this->value_ / other.value_);
  }

  /// \brief Compute the remainder of this Long object divided by another Long object.
  /// \param other The Long object to compute the remainder with.
  /// \return A new Long object with the result of the modulo operation.
  /// \details This function computes the remainder of the underlying int64_t values directly.
  /// \throws std::overflow_error If the divisor is zero.
  auto operator%(const Long& other) const -> Long {
    if (other.value_ == 0) {
      throw std::overflow_error("Modulo by zero");
    }
    return Long(this->value_ % other.value_);
  }

private:
  int64_t value_{0};
  friend std::formatter<Long>;
};
}

template <>
struct std::formatter<common::entity::base_type::Long> {
  /// \brief Custom formatter for Long objects.
  /// \details This custom formatter simply calls std::format_to with the underlying int64_t value.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Format the Long object into a string.
  /// \details This function formats the Long object using the provided format context.
  /// It generates a string representation of the Long object.
  /// \param content The Long object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Long& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output stream operator overload for Long objects.
/// \details This function overloads the output stream operator to print a Long object to the stream.
/// It formats the Long object using the provided format context.
/// \param os The output stream to write to.
/// \param content The Long object to format.
/// \return A reference to the same output stream.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Long& content) -> std::ostream& {
  return os << std::format("{}", content);
}
