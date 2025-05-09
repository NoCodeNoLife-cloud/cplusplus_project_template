#pragma once
#include <entity/base_type/Object.hpp>

namespace common {
  class Character final : public Object {
  public:
    explicit Character(char value);
    ~Character() override;
    [[nodiscard]] auto toString() const -> std::string override;
    explicit operator char() const;
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
    char value_{0};
  };
}
