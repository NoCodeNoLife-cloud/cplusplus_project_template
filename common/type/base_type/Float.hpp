#pragma once
#include <string>

#include "Object.hpp"

namespace common {
class Float final : public Object {
 public:
  static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
  static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
  static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
  static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
  static constexpr float MIN_VALUE = std::numeric_limits<float>::min();
  explicit Float(float value);
  ~Float() override;
  Float(const Float& other);
  Float(Float&& other) noexcept;

  /// @brief Copy assignment operator
  Float& operator=(const Float& other);

  /// @brief Move assignment operator
  Float& operator=(Float&& other) noexcept;

  /// @brief Conversion operator to float
  explicit operator float() const;

  /// @brief Generates a hash code for this Float
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts this Float to a string representation
  /// @return String representation of this Float
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Returns the float value
  /// @return The underlying float value
  [[nodiscard]] auto floatValue() const -> float;

  /// @brief Parses a string to create a Float object
  /// @param str The string to parse
  /// @return A Float object representing the parsed value
  static auto parseFloat(const std::string& str) -> Float;

  /// @brief Three-way comparison operator
  /// @param other The other Float to compare with
  /// @return The comparison result
  auto operator<=>(const Float& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other Float to compare with
  /// @return True if the two Floats are equal, false otherwise
  auto operator==(const Float& other) const -> bool;

  /// @brief Addition operator
  /// @param other The other Float to add
  /// @return A new Float representing the sum
  auto operator+(const Float& other) const -> Float;

  /// @brief Subtraction operator
  /// @param other The other Float to subtract
  /// @return A new Float representing the difference
  auto operator-(const Float& other) const -> Float;

  /// @brief Multiplication operator
  /// @param other The other Float to multiply
  /// @return A new Float representing the product
  auto operator*(const Float& other) const -> Float;

  /// @brief Division operator
  /// @param other The other Float to divide by
  /// @return A new Float representing the quotient
  auto operator/(const Float& other) const -> Float;

 private:
  friend std::formatter<Float>;
  float value_{0.0};
};
}  // namespace common

template <>
struct std::formatter<common::Float> : common::GenericFormatter<common::Float, &common::Float::value_> {};
