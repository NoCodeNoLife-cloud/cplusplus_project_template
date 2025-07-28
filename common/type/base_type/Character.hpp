#pragma once
#include "Object.hpp"

namespace common {
class Character final : public Object {
 public:
  explicit Character(char value);
  ~Character() override;
  Character(const Character& other);
  Character(Character&& other) noexcept;
  Character& operator=(const Character& other);
  Character& operator=(Character&& other) noexcept;
  explicit operator char() const;
  [[nodiscard]] auto hashCode() const -> size_t override;
  [[nodiscard]] auto toString() const -> std::string override;
  static auto isLetter(char c) -> bool;
  static auto isDigit(char c) -> bool;
  static auto isLetterOrDigit(char c) -> bool;
  static auto isUpperCase(char c) -> bool;
  static auto isLowerCase(char c) -> bool;
  static auto toUpperCase(char c) -> int32_t;
  static auto toLowerCase(char c) -> int32_t;
  [[nodiscard]] auto characterValue() const -> char;
  auto operator<=>(const Character& other) const -> std::partial_ordering;
  auto operator==(const Character& other) const -> bool;

 private:
  friend std::formatter<Character>;
  char value_{0};
};
}  // namespace common

template <>
struct std::formatter<common::Character>
    : common::GenericFormatter<common::Character, &common::Character::value_> {
};
