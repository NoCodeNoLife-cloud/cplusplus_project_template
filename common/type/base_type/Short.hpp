#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Short final : public Object {
 public:
  static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
  static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
  explicit Short(int16_t value);
  ~Short() override;
  Short(const Short& other);
  Short(Short&& other) noexcept;

  /// @brief Copy assignment operator
  Short& operator=(const Short& other);

  /// @brief Move assignment operator
  Short& operator=(Short&& other) noexcept;

  /// @brief Conversion operator to int16_t
  explicit operator int16_t() const;

  /// @brief Returns the hash code of this Short
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts this Short to a string representation
  /// @return String representation of this Short
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Gets the underlying int16_t value
  /// @return The int16_t value
  [[nodiscard]] auto shortValue() const -> int16_t;

  /// @brief Parses a string to create a Short instance
  /// @param str The string to parse
  /// @return A new Short instance
  static auto parseShort(const std::string& str) -> Short;

  /// @brief Three-way comparison operator
  /// @param other The other Short to compare with
  /// @return The comparison result
  auto operator<=>(const Short& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other Short to compare with
  /// @return True if equal, false otherwise
  auto operator==(const Short& other) const -> bool;

  /// @brief Addition operator
  /// @param other The other Short to add
  /// @return A new Short representing the sum
  auto operator+(const Short& other) const -> Short;

  /// @brief Subtraction operator
  /// @param other The other Short to subtract
  /// @return A new Short representing the difference
  auto operator-(const Short& other) const -> Short;

  /// @brief Multiplication operator
  /// @param other The other Short to multiply
  /// @return A new Short representing the product
  auto operator*(const Short& other) const -> Short;

  /// @brief Division operator
  /// @param other The other Short to divide by
  /// @return A new Short representing the quotient
  auto operator/(const Short& other) const -> Short;

  /// @brief Modulo operator
  /// @param other The other Short to modulo by
  /// @return A new Short representing the remainder
  auto operator%(const Short& other) const -> Short;

 private:
  friend std::formatter<Short>;
  int16_t value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Short> : common::GenericFormatter<common::Short, &common::Short::value_> {};
