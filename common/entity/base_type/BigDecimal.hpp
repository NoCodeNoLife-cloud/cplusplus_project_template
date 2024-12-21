#pragma once
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <stdexcept>

namespace common::entity::base_type {
/// \brief A class representing a high-precision decimal number.
/// \details The BigDecimal class is a wrapper around the Boost.Multiprecision library's cpp_dec_float type.
/// It allows for high-precision arithmetic operations on decimal numbers. This class provides methods for
/// addition, subtraction, multiplication, division, and comparison of BigDecimal objects.
class BigDecimal {
public:
  explicit BigDecimal(const std::string& str) : value_(str) {}
  explicit BigDecimal(const double num) : value_(num) {}
  /// \brief Adds two BigDecimal objects.
  /// \details This function adds the value of the `other` object to the value of the current object.
  /// The result is a new BigDecimal object with the sum of the two values.
  /// \param[in] other The BigDecimal object to add to the current object.
  /// \return A new BigDecimal object with the sum of the two values.
  auto operator+(const BigDecimal& other) const -> BigDecimal {
    return {BigDecimal((value_ + other.value_).convert_to<std::string>())};
  }

  /// \brief Subtracts one BigDecimal object from another.
  /// \details This function subtracts the value of the `other` object from the value of the current object.
  /// The result is a new BigDecimal object with the difference of the two values.
  /// \param[in] other The BigDecimal object to subtract from the current object.
  /// \return A new BigDecimal object with the difference of the two values.
  auto operator-(const BigDecimal& other) const -> BigDecimal {
    return {BigDecimal((value_ - other.value_).convert_to<std::string>())};
  }

  /// \brief Multiplies two BigDecimal objects.
  /// \details This function multiplies the value of the `other` object with the value of the current object.
  /// The result is a new BigDecimal object with the product of the two values.
  /// \param[in] other The BigDecimal object to multiply with the current object.
  /// \return A new BigDecimal object with the product of the two values.
  auto operator*(const BigDecimal& other) const -> BigDecimal {
    return {BigDecimal((value_ * other.value_).convert_to<std::string>())};
  }

  /// \brief Divides one BigDecimal object by another.
  /// \details This function divides the value of the current object by the value of the `other` object.
  /// The result is a new BigDecimal object with the result of the division.
  /// \param[in] other The BigDecimal object to divide the current object by.
  /// \return A new BigDecimal object with the result of the division.
  /// \throws std::invalid_argument if the divisor is zero.
  auto operator/(const BigDecimal& other) const -> BigDecimal {
    if (other.value_ == 0) {
      throw std::invalid_argument("Division by zero is not allowed.");
    }
    return {BigDecimal((value_ / other.value_).convert_to<std::string>())};
  }

  /// \brief Checks if two BigDecimal objects are equal.
  /// \details This function checks if the value of the `other` object is equal to the value of the current object.
  /// \param[in] other The BigDecimal object to compare with the current object.
  /// \return True if the two objects are equal, false otherwise.
  auto operator==(const BigDecimal& other) const -> bool {
    return value_ == other.value_;
  }

  /// \brief Checks if two BigDecimal objects are not equal.
  /// \details This function checks if the value of the `other` object is not equal to the value of the current object.
  /// \param[in] other The BigDecimal object to compare with the current object.
  /// \return True if the two objects are not equal, false otherwise.
  auto operator!=(const BigDecimal& other) const -> bool {
    return value_ != other.value_;
  }

  /// \brief Checks if the value of the current object is less than the value of the `other` object.
  /// \details This function compares the value of the current object with the value of the `other` object.
  /// \param[in] other The BigDecimal object to compare with the current object.
  /// \return True if the value of the current object is less than the value of the `other` object, false otherwise.
  auto operator<(const BigDecimal& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Checks if the value of the current object is greater than the value of the `other` object.
  /// \details This function compares the value of the current object with the value of the `other` object.
  /// \param[in] other The BigDecimal object to compare with the current object.
  /// \return True if the value of the current object is greater than the value of the `other` object, false otherwise.
  auto operator>(const BigDecimal& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Converts the BigDecimal object to a string.
  /// \details This function converts the value of the current object to a string.
  /// The string is a decimal representation of the value with up to 100 significant digits.
  /// \return A string representing the value of the current object.
  [[nodiscard]] auto toString() const -> std::string {
    return value_.convert_to<std::string>();
  }

private:
  boost::multiprecision::cpp_dec_float_100 value_;
};
}
