#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Long final : public Object {
 public:
  static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
  static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();
  explicit Long(int64_t value = 0l);
  ~Long() override;
  Long(const Long& other);
  Long(Long&& other) noexcept;

  /// @brief Copy assignment operator
  Long& operator=(const Long& other);

  /// @brief Move assignment operator
  Long& operator=(Long&& other) noexcept;

  /// @brief Conversion operator to int64_t
  explicit operator int64_t() const;

  /// @brief Returns the hash code of this Long
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Returns the string representation of this Long
  /// @return The string representation
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Returns the long value
  /// @return The long value
  [[nodiscard]] auto longValue() const -> int64_t;

  /// @brief Parses a string to create a Long
  /// @param str The string to parse
  /// @return The parsed Long
  static auto parseLong(const std::string& str) -> Long;

  /// @brief Three-way comparison operator
  /// @param other The other Long to compare with
  /// @return The comparison result
  auto operator<=>(const Long& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other Long to compare with
  /// @return True if equal, false otherwise
  auto operator==(const Long& other) const -> bool;

  /// @brief Addition operator
  /// @param other The other Long to add
  /// @return The result of the addition
  auto operator+(const Long& other) const -> Long;

  /// @brief Subtraction operator
  /// @param other The other Long to subtract
  /// @return The result of the subtraction
  auto operator-(const Long& other) const -> Long;

  /// @brief Multiplication operator
  /// @param other The other Long to multiply
  /// @return The result of the multiplication
  auto operator*(const Long& other) const -> Long;

  /// @brief Division operator
  /// @param other The other Long to divide by
  /// @return The result of the division
  auto operator/(const Long& other) const -> Long;

  /// @brief Modulo operator
  /// @param other The other Long to modulo by
  /// @return The result of the modulo
  auto operator%(const Long& other) const -> Long;

 private:
  friend std::formatter<Long>;
  int64_t value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Long> : common::GenericFormatter<common::Long, &common::Long::value_> {};
