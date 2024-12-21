#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type {
/// \brief A Double object represents an immutable double precision floating point value.
/// \details In addition to implementing the methods inherited from its parent class,
/// it also overrides the methods defined in the Comparable interface.
class Double final : public Object, public iface::IfaceComparable<Double> {
public:
  static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
  static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
  static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
  static constexpr double MIN_VALUE = std::numeric_limits<double>::min();

  explicit Double(const double value) : value_(value) {}

  ~Double() override = default;

  /// \brief Cast the object to a double.
  /// \return The underlying double value.
  /// \details This function simply returns the underlying double value.
  explicit operator double() const {
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
  /// it compares the underlying double values directly. Otherwise, it returns
  /// false.
  [[nodiscard]] auto equals(const Double& other) const -> bool override {
    return value_ == other.value_;
  }

  /// \brief Compare this Double object with another.
  /// \param other The Double object to compare with.
  /// \return An integer less than, equal to, or greater than zero if this object
  /// is considered to be respectively less than, equal to, or greater than the specified object.
  /// \details This function compares the underlying double values directly.
  [[nodiscard]] auto compareTo(const Double& other) const -> int override {
    return (value_ > other.value_) - (value_ < other.value_);
  }

  /// \brief Returns the underlying double value.
  /// \return The underlying double value.
  /// \details This function simply returns the underlying double value.
  [[nodiscard]] auto doubleValue() const -> double {
    return value_;
  }

  /// \brief Parse a double value from a string.
  /// \param str The string to parse.
  /// \return A Double object representing the parsed value.
  /// \throws std::invalid_argument If the string is not a valid double.
  /// \throws std::out_of_range If the parsed value is out of range for a double.
  static auto parseDouble(const std::string& str) -> Double {
    try {
      const double result = std::stod(str);
      return Double(result);
    }
    catch (const std::invalid_argument&) {
      throw std::invalid_argument("Invalid input string for Double conversion");
    } catch (const std::out_of_range&) {
      throw std::out_of_range("Value out of range for Double");
    }
  }

  /// \brief Check if this Double object is equal to another Double object.
  /// \param other The Double object to compare with.
  /// \return True if the Double objects are equal, false otherwise.
  /// \details This function checks if the underlying double values are equal
  /// by utilizing the Equals method.
  auto operator==(const Double& other) const -> bool {
    return value_ == other.value_;
  }

  /// \brief Check if this Double object is not equal to another Double object.
  /// \param other The Double object to compare with.
  /// \return True if the Double objects are not equal, false otherwise.
  /// \details This function checks if the underlying double values are not equal
  /// by utilizing the Equals method.
  auto operator!=(const Double& other) const -> bool {
    return value_ != other.value_;
  }

  /// \brief Check if this Double object is less than another Double object.
  /// \param other The Double object to compare with.
  /// \return True if this object is less than the other object, false otherwise.
  /// \details This function checks if the underlying double values are less than
  /// by utilizing the CompareTo method.
  auto operator<(const Double& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Check if this Double object is greater than another Double object.
  /// \param other The Double object to compare with.
  /// \return True if this object is greater than the other object, false otherwise.
  /// \details This function checks if the underlying double value is greater than
  /// the value of the other Double object.
  auto operator>(const Double& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Check if this Double object is less than or equal to another Double object.
  /// \param other The Double object to compare with.
  /// \return True if this object is less than or equal to the other object, false otherwise.
  /// \details This function checks if the underlying double values are less than or equal to
  /// by utilizing the CompareTo method.
  auto operator<=(const Double& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Check if this Double object is greater than or equal to another Double object.
  /// \param other The Double object to compare with.
  /// \return True if this object is greater than or equal to the other object, false otherwise.
  /// \details This function checks if the underlying double values are greater than or equal to
  /// the value of the other Double object.
  auto operator>=(const Double& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Adds two Double objects.
  /// \param other The Double object to add.
  /// \return A Double object with the result of the addition.
  /// \details This function adds the underlying double values of the two Double objects.
  auto operator+(const Double& other) const -> Double {
    return Double(this->value_ + other.value_);
  }

  /// \brief Subtracts two Double objects.
  /// \param other The Double object to subtract.
  /// \return A Double object with the result of the subtraction.
  /// \details This function subtracts the underlying double values of the two Double objects.
  auto operator-(const Double& other) const -> Double {
    return Double(this->value_ - other.value_);
  }

  /// \brief Multiplies two Double objects.
  /// \param other The Double object to multiply with.
  /// \return A Double object with the result of the multiplication.
  /// \details This function multiplies the underlying double values of the two Double objects.
  auto operator*(const Double& other) const -> Double {
    return Double(this->value_ * other.value_);
  }

  /// \brief Divides two Double objects.
  /// \param other The Double object to divide with.
  /// \return A Double object with the result of the division.
  /// \details This function divides the underlying double values of the two Double objects.
  /// \throws std::overflow_error If the divisor is zero.
  auto operator/(const Double& other) const -> Double {
    if (other.value_ == 0.0) {
      throw std::overflow_error("Division by zero");
    }
    return Double(this->value_ / other.value_);
  }

private:
  friend std::formatter<Double>;
  double value_{0.0};
};
}

template <>
struct std::formatter<common::entity::base_type::Double> {
  /// \brief Custom formatter for Double objects.
  /// \details This custom formatter simply calls std::format_to with the underlying double value.
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  /// \brief Format the Double object into a string.
  /// This function formats the Double object using the provided format context.
  /// It generates a string representation of the Double object.
  /// \param content The Double object to format.
  /// \param ctx The format context to use for formatting.
  /// \return An iterator to the end of the inserted sequence.
  static auto format(const common::entity::base_type::Double& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

/// \brief Output stream operator for Double objects.
/// This function inserts the value of the given Double object into the given output stream.
/// \param os The output stream to insert the value into.
/// \param content The Double object to insert.
/// \return The output stream after insertion.
/// This function uses the standard library function `std::format` to format the given Double object into a string.
/// The string is then inserted into the output stream.
inline auto operator<<(std::ostream& os, const common::entity::base_type::Double& content) -> std::ostream& {
  return os << std::format("{}", content);
}
