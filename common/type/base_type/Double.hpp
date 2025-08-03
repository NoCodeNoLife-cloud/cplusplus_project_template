#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Double final : public Object {
 public:
  static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
  static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
  static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
  static constexpr double MIN_VALUE = std::numeric_limits<double>::min();
  explicit Double(double value = 0.0);
  ~Double() override;
  Double(const Double& other);
  Double(Double&& other) noexcept;

  /// @brief Copy assignment operator
  Double& operator=(const Double& other);

  /// @brief Move assignment operator
  Double& operator=(Double&& other) noexcept;

  /// @brief Conversion operator to double
  explicit operator double() const;

  /// @brief Returns the hash code of the double value
  /// @return The hash code as a size_t
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts the double value to a string representation
  /// @return The string representation of the double value
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Returns the double value
  /// @return The stored double value
  [[nodiscard]] auto doubleValue() const -> double;

  /// @brief Parses a string to create a Double object
  /// @param str The string to parse
  /// @return A Double object representing the parsed value
  static auto parseDouble(const std::string& str) -> Double;

  /// @brief Three-way comparison operator
  /// @param other The other Double to compare with
  /// @return The comparison result as a std::partial_ordering
  auto operator<=>(const Double& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other Double to compare with
  /// @return True if the values are equal, false otherwise
  auto operator==(const Double& other) const -> bool;

  /// @brief Addition operator
  /// @param other The other Double to add
  /// @return A new Double representing the sum
  auto operator+(const Double& other) const -> Double;

  /// @brief Subtraction operator
  /// @param other The other Double to subtract
  /// @return A new Double representing the difference
  auto operator-(const Double& other) const -> Double;

  /// @brief Multiplication operator
  /// @param other The other Double to multiply
  /// @return A new Double representing the product
  auto operator*(const Double& other) const -> Double;

  /// @brief Division operator
  /// @param other The other Double to divide by
  /// @return A new Double representing the quotient
  auto operator/(const Double& other) const -> Double;

 private:
  friend std::formatter<Double>;
  double value_{0.0};
};
}  // namespace common

template <>
struct std::formatter<common::Double> : common::GenericFormatter<common::Double, &common::Double::value_> {};
