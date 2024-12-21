#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief Class Short is a type of Object that represents a signed short value.
/// \details Class Short is a type of Object that represents a signed short value.
/// It is a final class that cannot be inherited from.
class Short final : public Object, public iface::IfaceComparable<Short> {
public:
  static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
  static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();

  explicit Short(const int16_t value) : value_(value) {}

  ~Short() override = default;

  /// \brief Convert the Short object to a short.
  /// \return The underlying short value of the Short object.
  /// \details This function simply returns the value_ member variable.
  explicit operator short() const {
    return value_;
  }

  /// \brief Returns a string representation of the object.
  /// \return A string representing the object's type name.
  /// \details This function uses `typeid` to retrieve the name of the object's type.
  [[nodiscard]] auto toString() const -> std::string override {
    return std::format("{}", *this);
  }

  /// \brief Get the short value of the object.
  /// \return The underlying int16_t value of the Short object.
  /// \details This function returns the raw short value stored in the Short object.
  [[nodiscard]] auto shortValue() const -> int16_t {
    return value_;
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function compares the underlying short values.
  /// If the other object is not of type Short, it returns false.
  [[nodiscard]] auto equals(const Short& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Compare this Short object with another.
  /// \param other The Short object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying short values directly.
  [[nodiscard]] auto compareTo(const Short& other) const -> int override {
    return value_ - other.value_;
  }

  /// \brief Parse a short value from a string.
  /// \param str The string to parse.
  /// \return A Short object representing the parsed value.
  /// \throws std::invalid_argument If the string is not a valid short.
  /// \throws std::out_of_range If the parsed value is out of range for a short.
  /// \details This function parses the string using `std::stoi`.
  static auto parseShort(const std::string& str) -> Short {
    try {
      const auto result = static_cast<int16_t>(std::stoi(str));
      if (result > MAX_VALUE || result < MIN_VALUE) {
        throw std::out_of_range("Value out of range for Short");
      }
      return Short(result);
    }
    catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Short conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Short");
    }
  }

  /// \brief Check if the object is equal to another object
  /// \param other The other object
  /// \return True if the objects are equal
  /// \details This function compares the underlying short values.
  /// If the other object is not of type Short, it returns false.
  auto operator==(const Short& other) const -> bool {
    return equals(other);
  }

  /// \brief Check if the object is not equal to another object
  /// \param other The other object
  /// \return True if the objects are not equal
  /// \details This function compares the underlying short values.
  /// If the other object is not of type Short, it returns true.
  auto operator!=(const Short& other) const -> bool {
    return !equals(other);
  }

  /// \brief Check if this Short object is less than another Short object.
  /// \param other The Short object to compare with.
  /// \return True if this Short object is less than the other Short object, false otherwise.
  /// \details This function compares the underlying short values directly.
  auto operator<(const Short& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Short object is greater than another Short object.
  /// \param other The Short object to compare with.
  /// \return True if this Short object is greater than the other Short object, false otherwise.
  /// \details This function compares the underlying short values directly.
  auto operator>(const Short& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Short object is less than or equal to another Short object.
  /// \param other The Short object to compare with.
  /// \return True if this Short object is less than or equal to the other Short object, false otherwise.
  /// \details This function compares the underlying short values directly.
  auto operator<=(const Short& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Short object is greater than or equal to another Short object.
  /// \param other The Short object to compare with.
  /// \return True if this Short object is greater than or equal to the other Short object, false otherwise.
  /// \details This function compares the underlying short values directly.
  auto operator>=(const Short& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Add this Short object to another Short object.
  /// \param other The Short object to add.
  /// \return A new Short object representing the sum of this object and the other.
  /// \details This function adds the underlying short values directly and returns a Short object.
  auto operator+(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ + other.value_));
  }

  /// \brief Subtract another Short object from this Short object.
  /// \param other The Short object to subtract.
  /// \return A new Short object representing the difference between this object and the other.
  /// \details This function subtracts the underlying short values directly and returns a Short object.
  auto operator-(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ - other.value_));
  }

  /// \brief Multiply this Short object by another Short object.
  /// \param other The Short object to multiply.
  /// \return A new Short object representing the product of this object and the other.
  /// \details This function multiplies the underlying short values directly and returns a Short object.
  auto operator*(const Short& other) const -> Short {
    return Short(static_cast<int16_t>(this->value_ * other.value_));
  }

  /// \brief Divide this Short object by another Short object.
  /// \param other The Short object to divide.
  /// \return A new Short object representing the quotient of this object and the other.
  /// \details This function divides the underlying short values directly and returns a Short object.
  /// \throws std::overflow_error If the divisor is zero.
  auto operator/(const Short& other) const -> Short {
    if (other.value_ == 0) {
      throw std::overflow_error("Division by zero");
    }
    return Short(static_cast<int16_t>(this->value_ / other.value_));
  }

  /// \brief Compute the remainder of this Short object divided by another Short object.
  /// \param other The Short object to compute the remainder with.
  /// \return A new Short object with the result of the modulo operation.
  /// \details This function computes the remainder of the underlying short values directly.
  /// \throws std::overflow_error If the divisor is zero.
  auto operator%(const Short& other) const -> Short {
    if (other.value_ == 0) {
      throw std::overflow_error("Modulo by zero");
    }
    return Short(static_cast<int16_t>(this->value_ % other.value_));
  }

private:
  int16_t value_{0};
  friend std::formatter<Short>;
};
}

template <>
struct std::formatter<common::entity::base_type::Short> {
  /// \brief Parse the format specifiers for the Short class.
  /// \param ctx The format parse context.
  /// \return The parsed format specifiers.
  /// \details This function parses the format specifiers for the Short class.
  /// If the format specifier is invalid, it throws a format_error.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief A custom formatter for Short objects.
  /// \details This custom formatter simply calls std::format_to with the underlying int16_t value.
  static auto format(const common::entity::base_type::Short& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output stream operator for Short objects.
/// \param os The output stream to write to.
/// \param content The Short object to write.
/// \return The output stream.
/// \details This function writes the string representation of the Short object to the output stream.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Short& content) -> std::ostream& {
  return os << std::format("{}", content);
}
