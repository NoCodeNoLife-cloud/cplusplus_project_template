#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Boolean final : public Object {
 public:
  explicit Boolean(bool value = false);
  ~Boolean() override;
  Boolean(const Boolean& other);
  Boolean(Boolean&& other) noexcept;

  /// @brief Converts the Boolean object to a primitive bool value.
  explicit operator bool() const;

  /// @brief Copy assignment operator.
  /// @param other The Boolean object to copy from.
  /// @return A reference to this Boolean object.
  Boolean& operator=(const Boolean& other);

  /// @brief Move assignment operator.
  /// @param other The Boolean object to move from.
  /// @return A reference to this Boolean object.
  Boolean& operator=(Boolean&& other) noexcept;

  /// @brief Computes the hash code of the Boolean object.
  /// @return The hash code as a size_t.
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts the Boolean object to a string representation.
  /// @return The string representation of the Boolean object.
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Gets the underlying bool value.
  /// @return The underlying bool value.
  [[nodiscard]] auto boolValue() const -> bool;

  /// @brief Parses a string to create a Boolean object.
  /// @param str The string to parse.
  /// @return A Boolean object representing the parsed value.
  static auto parseBoolean(const std::string& str) -> Boolean;

  /// @brief Gets the underlying boolean value.
  /// @return The underlying boolean value.
  [[nodiscard]] auto booleanValue() const -> bool;

  /// @brief Compares this Boolean object with another for ordering.
  /// @param other The other Boolean object to compare with.
  /// @return A std::partial_ordering result of the comparison.
  auto operator<=>(const Boolean& other) const -> std::partial_ordering;

  /// @brief Checks equality between this Boolean object and another.
  /// @param other The other Boolean object to compare with.
  /// @return True if both objects represent the same value, false otherwise.
  auto operator==(const Boolean& other) const -> bool;

 private:
  friend std::formatter<Boolean>;
  bool value_{false};
};

const Boolean True{true};
const Boolean False{false};
}  // namespace common

template <>
struct std::formatter<common::Boolean> : common::GenericFormatter<common::Boolean, &common::Boolean::value_> {};
