#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <string>

namespace common {
/// @brief A class for high-precision decimal arithmetic
/// @details This class uses boost::multiprecision::cpp_dec_float_100 for underlying storage
///          to provide high precision decimal operations.
class BigDecimal {
 public:
  explicit BigDecimal(const std::string& str);
  explicit BigDecimal(double num);

  /// @brief Addition operator
  /// @param other The BigDecimal to add
  /// @return The sum of this BigDecimal and other
  auto operator+(const BigDecimal& other) const -> BigDecimal;

  /// @brief Subtraction operator
  /// @param other The BigDecimal to subtract
  /// @return The difference of this BigDecimal and other
  auto operator-(const BigDecimal& other) const -> BigDecimal;

  /// @brief Multiplication operator
  /// @param other The BigDecimal to multiply
  /// @return The product of this BigDecimal and other
  auto operator*(const BigDecimal& other) const -> BigDecimal;

  /// @brief Division operator
  /// @param other The BigDecimal to divide by
  /// @return The quotient of this BigDecimal and other
  auto operator/(const BigDecimal& other) const -> BigDecimal;

  /// @brief Three-way comparison operator
  /// @param other The BigDecimal to compare with
  /// @return std::partial_ordering result of the comparison
  auto operator<=>(const BigDecimal& other) const -> std::partial_ordering;

 private:
  boost::multiprecision::cpp_dec_float_100 value_;
};
}  // namespace common
