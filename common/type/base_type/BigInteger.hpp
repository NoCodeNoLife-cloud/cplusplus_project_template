#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <string>

namespace common {
class BigInteger {
 public:
  BigInteger();
  explicit BigInteger(const std::string& str);
  explicit BigInteger(int64_t num);

  /// @brief Addition operator
  /// @param other The BigInteger to add
  /// @return The result of the addition
  auto operator+(const BigInteger& other) const -> BigInteger;

  /// @brief Subtraction operator
  /// @param other The BigInteger to subtract
  /// @return The result of the subtraction
  auto operator-(const BigInteger& other) const -> BigInteger;

  /// @brief Multiplication operator
  /// @param other The BigInteger to multiply
  /// @return The result of the multiplication
  auto operator*(const BigInteger& other) const -> BigInteger;

  /// @brief Division operator
  /// @param other The BigInteger to divide by
  /// @return The result of the division
  auto operator/(const BigInteger& other) const -> BigInteger;

  /// @brief Modulus operator
  /// @param other The BigInteger to modulo by
  /// @return The result of the modulus operation
  auto operator%(const BigInteger& other) const -> BigInteger;

  /// @brief Three-way comparison operator
  /// @param other The BigInteger to compare with
  /// @return The result of the comparison
  auto operator<=>(const BigInteger& other) const -> std::partial_ordering;

  /// @brief Create a BigInteger from a string
  /// @param str The string to convert
  /// @return The resulting BigInteger
  static auto fromString(const std::string& str) -> BigInteger;

  /// @brief Create a BigInteger from an int64_t
  /// @param num The int64_t to convert
  /// @return The resulting BigInteger
  static auto fromInt(int64_t num) -> BigInteger;

 private:
  boost::multiprecision::cpp_int value_;
};
}  // namespace common
