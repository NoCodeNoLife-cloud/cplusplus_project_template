#pragma once
#include "Object.hpp"

namespace common {
class Character final : public Object {
 public:
  explicit Character(char value);
  ~Character() override;
  Character(const Character& other);
  Character(Character&& other) noexcept;

  /// @brief Copy assignment operator
  Character& operator=(const Character& other);

  /// @brief Move assignment operator
  Character& operator=(Character&& other) noexcept;

  /// @brief Explicit conversion to char
  explicit operator char() const;

  /// @brief Returns the hash code of this character
  /// @return The hash code
  [[nodiscard]] auto hashCode() const -> size_t override;

  /// @brief Converts this character to a string representation
  /// @return String representation of the character
  [[nodiscard]] auto toString() const -> std::string override;

  /// @brief Checks if a character is a letter
  /// @param c The character to check
  /// @return True if the character is a letter, false otherwise
  static auto isLetter(char c) -> bool;

  /// @brief Checks if a character is a digit
  /// @param c The character to check
  /// @return True if the character is a digit, false otherwise
  static auto isDigit(char c) -> bool;

  /// @brief Checks if a character is a letter or digit
  /// @param c The character to check
  /// @return True if the character is a letter or digit, false otherwise
  static auto isLetterOrDigit(char c) -> bool;

  /// @brief Checks if a character is uppercase
  /// @param c The character to check
  /// @return True if the character is uppercase, false otherwise
  static auto isUpperCase(char c) -> bool;

  /// @brief Checks if a character is lowercase
  /// @param c The character to check
  /// @return True if the character is lowercase, false otherwise
  static auto isLowerCase(char c) -> bool;

  /// @brief Converts a character to uppercase
  /// @param c The character to convert
  /// @return The uppercase version of the character
  static auto toUpperCase(char c) -> int32_t;

  /// @brief Converts a character to lowercase
  /// @param c The character to convert
  /// @return The lowercase version of the character
  static auto toLowerCase(char c) -> int32_t;

  /// @brief Gets the character value
  /// @return The character value
  [[nodiscard]] auto characterValue() const -> char;

  /// @brief Three-way comparison operator
  /// @param other The other character to compare with
  /// @return The comparison result
  auto operator<=>(const Character& other) const -> std::partial_ordering;

  /// @brief Equality comparison operator
  /// @param other The other character to compare with
  /// @return True if equal, false otherwise
  auto operator==(const Character& other) const -> bool;

 private:
  friend std::formatter<Character>;
  char value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Character> : common::GenericFormatter<common::Character, &common::Character::value_> {};
