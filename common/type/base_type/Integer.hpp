#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Integer final : public Object {
 public:
  static constexpr int32_t MIN_VALUE = std::numeric_limits<int32_t>::min();
  static constexpr int32_t MAX_VALUE = std::numeric_limits<int32_t>::max();
  explicit Integer(int32_t value = 0);
  ~Integer() override;
  Integer(const Integer& other);
  Integer(Integer&& other) noexcept;

  /// @brief Copy assignment operator
  Integer& operator=(const Integer& other);

  /// @brief Move assignment operator
  Integer& operator=(Integer&& other) noexcept;

  /// @brief Conversion operator to int32_t
  explicit operator int32_t() const;

  /// @brief Returns the hash code of this integer
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts this integer to a string representation
  /// @return String representation of this integer
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Returns the int32_t value of this integer
  /// @return The int32_t value
  [[nodiscard]] auto intValue() const -> int32_t;

  /// @brief Parses a string to create an Integer object
  /// @param str The string to parse
  /// @return The parsed Integer object
  static auto parseInt(const std::string& str) -> Integer;

  /// @brief Three-way comparison operator
  /// @param other The other Integer to compare with
  /// @return The comparison result
  auto operator<=>(const Integer& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other Integer to compare with
  /// @return True if equal, false otherwise
  auto operator==(const Integer& other) const -> bool;

  /// @brief Addition operator
  /// @param other The other Integer to add
  /// @return The result of the addition
  auto operator+(const Integer& other) const -> Integer;

  /// @brief Subtraction operator
  /// @param other The other Integer to subtract
  /// @return The result of the subtraction
  auto operator-(const Integer& other) const -> Integer;

  /// @brief Multiplication operator
  /// @param other The other Integer to multiply
  /// @return The result of the multiplication
  auto operator*(const Integer& other) const -> Integer;

  /// @brief Division operator
  /// @param other The other Integer to divide by
  /// @return The result of the division
  auto operator/(const Integer& other) const -> Integer;

 private:
  friend std::formatter<Integer>;
  int32_t value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Integer> : common::GenericFormatter<common::Integer, &common::Integer::value_> {};
