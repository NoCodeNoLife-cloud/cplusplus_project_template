#pragma once
#include <format>
#include <iostream>
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace framework::entity::base_type {
  class Character final : public Object, public iface::IComparable<Character> {
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
    auto operator==(const Character& other) const -> bool;
    auto operator!=(const Character& other) const -> bool;
    auto operator<(const Character& other) const -> bool;
    auto operator>(const Character& other) const -> bool;
    auto operator<=(const Character& other) const -> bool;
    auto operator>=(const Character& other) const -> bool;

  private:
    char value_{0};
    friend std::formatter<Character>;
  };
}

template <>
struct std::formatter<framework::entity::base_type::Character> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Character& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Character& content) -> std::ostream& {
  return os << std::format("{}", content);
}
