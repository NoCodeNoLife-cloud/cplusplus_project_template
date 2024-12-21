#pragma once
#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

namespace common::entity::base_type {
/// \brief A class representing a BigInteger.
/// \details A BigInteger is an arbitrary-precision signed integer.
/// This class provides a way to represent an integer with any number of digits.
/// It provides methods for performing arithmetic operations on BigInteger objects.
class BigInteger {
public:
  BigInteger() : value_(0) {}
  explicit BigInteger(const std::string& str) : value_(str) {}
  explicit BigInteger(const long long num) : value_(num) {}
  /// \brief Adds two BigInteger objects.
  /// \details This method adds the value of the parameter to the value of the
  /// current object and returns the result as a new BigInteger object.
  auto operator+(const BigInteger& other) const -> BigInteger {
    return BigInteger((value_ + other.value_).convert_to<std::string>());
  }

  /// \brief Subtracts one BigInteger object from another.
  /// \details This method subtracts the value of the parameter from the value of the
  /// current object and returns the result as a new BigInteger object.
  auto operator-(const BigInteger& other) const -> BigInteger {
    return BigInteger((value_ - other.value_).convert_to<std::string>());
  }

  /// \brief Multiplies two BigInteger objects.
  /// \details This method multiplies the value of the parameter with the value of the
  /// current object and returns the result as a new BigInteger object.
  auto operator*(const BigInteger& other) const -> BigInteger {
    return BigInteger((value_ * other.value_).convert_to<std::string>());
  }

  /// \brief Divides one BigInteger object by another.
  /// \details This method performs division of the current BigInteger object by the parameter BigInteger object.
  /// It checks for division by zero and throws an invalid_argument exception if the denominator is zero.
  /// \param[in] other The BigInteger object to divide the current object by.
  /// \return A new BigInteger object representing the quotient of the division.
  /// \throws std::invalid_argument if the other BigInteger object is zero.
  auto operator/(const BigInteger& other) const -> BigInteger {
    if (other.value_ == 0) {
      throw std::invalid_argument("Division by zero");
    }
    return BigInteger((value_ / other.value_).convert_to<std::string>());
  }

  /// \brief Computes the remainder of the division of two BigInteger objects.
  /// \details This method calculates the remainder when the current BigInteger is divided by the parameter BigInteger.
  /// It checks for division by zero and throws an invalid_argument exception if the divisor is zero.
  /// \param[in] other The BigInteger object to divide the current object by for modulo operation.
  /// \return A new BigInteger object representing the remainder of the division.
  /// \throws std::invalid_argument if the other BigInteger object is zero.
  auto operator%(const BigInteger& other) const -> BigInteger {
    if (other.value_ == 0) {
      throw std::invalid_argument("Modulo by zero");
    }
    return BigInteger((value_ % other.value_).convert_to<std::string>());
  }

  /// \brief Checks if two BigInteger objects are equal.
  /// \details This method compares two BigInteger objects for equality.
  /// It returns true if the two objects have the same value, and false otherwise.
  /// \param[in] other The BigInteger object to compare to the current object.
  /// \return true if the two objects are equal, false otherwise.
  auto operator==(const BigInteger& other) const -> bool {
    return value_ == other.value_;
  }

  /// \brief Checks if two BigInteger objects are not equal.
  /// \details This method compares two BigInteger objects for inequality.
  /// It returns true if the two objects have different values, and false otherwise.
  /// \param[in] other The BigInteger object to compare to the current object.
  /// \return true if the two objects are not equal, false otherwise.
  auto operator!=(const BigInteger& other) const -> bool {
    return value_ != other.value_;
  }

  /// \brief Compares if the current BigInteger is less than another.
  /// \details This method checks if the value of the current BigInteger object
  /// is strictly less than the value of the parameter BigInteger object.
  /// \param[in] other The BigInteger object to compare with the current object.
  /// \return true if the current object is less than the other object, false otherwise.
  auto operator<(const BigInteger& other) const -> bool {
    return value_ < other.value_;
  }

  /// \brief Compares if the current BigInteger is less than or equal to another.
  /// \details This method checks if the value of the current BigInteger object
  /// is less than or equal to the value of the parameter BigInteger object.
  /// \param[in] other The BigInteger object to compare with the current object.
  /// \return true if the current object is less than or equal to the other object, false otherwise.
  auto operator<=(const BigInteger& other) const -> bool {
    return value_ <= other.value_;
  }

  /// \brief Compares if the current BigInteger is greater than another.
  /// \details This method checks if the value of the current BigInteger object
  /// is strictly greater than the value of the parameter BigInteger object.
  /// \param[in] other The BigInteger object to compare with the current object.
  /// \return true if the current object is greater than the other object, false otherwise.
  auto operator>(const BigInteger& other) const -> bool {
    return value_ > other.value_;
  }

  /// \brief Compares if the current BigInteger is greater than or equal to another.
  /// \details This method checks if the value of the current BigInteger object
  /// is greater than or equal to the value of the parameter BigInteger object.
  /// \param[in] other The BigInteger object to compare with the current object.
  /// \return true if the current object is greater than or equal to the other object, false otherwise.
  auto operator>=(const BigInteger& other) const -> bool {
    return value_ >= other.value_;
  }

  /// \brief Converts the BigInteger object to a string.
  /// \details This method returns a string representation of the BigInteger object.
  /// The string is in the base 10 number system.
  /// \return A string representation of the BigInteger object.
  auto toString() const -> std::string {
    return value_.str();
  }

  /// \brief Creates a BigInteger object from a string representation.
  /// \details This static method parses a string and creates a corresponding BigInteger object.
  /// The string should represent a valid integer in base 10.
  /// \param str The string to be converted to a BigInteger object.
  /// \return A BigInteger object representing the integer value of the string.
  static auto fromString(const std::string& str) -> BigInteger {
    return BigInteger(str);
  }

  /// \brief Creates a BigInteger object from an integer.
  /// \details This static method creates a BigInteger object from the given integer.
  /// \param num The integer to be converted to a BigInteger object.
  /// \return A BigInteger object representing the given integer value.
  static auto fromInt(const long long num) -> BigInteger {
    return BigInteger(num);
  }

private:
  boost::multiprecision::cpp_int value_;
};
}
