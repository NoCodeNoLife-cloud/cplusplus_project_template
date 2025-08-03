#pragma once
#include <string>
#include <type/base_type/Object.hpp>

namespace common {
class Byte final : public Object {
 public:
  static constexpr uint8_t MIN_VALUE = std::numeric_limits<uint8_t>::min();
  static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
  explicit Byte(uint8_t value = 0);
  ~Byte() override;
  Byte(const Byte& other);
  Byte(Byte&& other) noexcept;

  /// @brief Copy assignment operator
  Byte& operator=(const Byte& other);

  /// @brief Move assignment operator
  Byte& operator=(Byte&& other) noexcept;

  /// @brief Explicit conversion operator to uint8_t
  explicit operator uint8_t() const;

  /// @brief Returns the hash code of the byte
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts the byte to a string representation
  /// @return String representation of the byte
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Parses a string to create a Byte object
  /// @param str The string to parse
  /// @return A Byte object created from the string
  static auto parseByte(const std::string& str) -> Byte;

  /// @brief Gets the underlying byte value
  /// @return The underlying uint8_t value
  [[nodiscard]] auto byteValue() const -> uint8_t;

  /// @brief Spaceship operator for comparing two Byte objects
  /// @param other The other Byte to compare with
  /// @return The comparison result
  auto operator<=>(const Byte& other) const -> std::partial_ordering;

  /// @brief Equality operator for comparing two Byte objects
  /// @param other The other Byte to compare with
  /// @return True if equal, false otherwise
  auto operator==(const Byte& other) const -> bool;

  /// @brief Addition operator for two Byte objects
  /// @param other The other Byte to add
  /// @return A new Byte representing the sum
  auto operator+(const Byte& other) const -> Byte;

  /// @brief Subtraction operator for two Byte objects
  /// @param other The other Byte to subtract
  /// @return A new Byte representing the difference
  auto operator-(const Byte& other) const -> Byte;

 private:
  friend std::formatter<Byte>;
  uint8_t value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Byte> : common::GenericFormatter<common::Byte, &common::Byte::value_> {};
