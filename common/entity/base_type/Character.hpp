#pragma once
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Character final : public Object, public IComparable<Character> {
  public:
    explicit Character(char value);
    ~Character() override;
    explicit operator char() const;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto equals(const Character& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Character& other) const -> int32_t override;
    static auto isLetter(char c) -> bool;
    static auto isDigit(char c) -> bool;
    static auto isLetterOrDigit(char c) -> bool;
    static auto isUpperCase(char c) -> bool;
    static auto isLowerCase(char c) -> bool;
    static auto toUpperCase(char c) -> int32_t;
    static auto toLowerCase(char c) -> int32_t;
    [[nodiscard]] auto characterValue() const -> char;
    auto operator<=>(const Character& other) const -> std::partial_ordering;

  private:
    friend std::formatter<Character>;
    char value_{0};
  };
}

template <>
struct std::formatter<common::Character> : common::GenericFormatter<common::Character, &common::Character::value_> {};
