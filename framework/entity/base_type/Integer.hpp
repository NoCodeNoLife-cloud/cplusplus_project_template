#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
  class Integer final : public Object, public iface::IComparable<Integer> {
  public:
    static constexpr int32_t MIN_VALUE = std::numeric_limits<int32_t>::min();
    static constexpr int32_t MAX_VALUE = std::numeric_limits<int32_t>::max();
    explicit Integer(int32_t value);
    ~Integer() override;
    explicit operator int32_t() const;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] auto intValue() const -> int32_t;
    static auto parseInt(const std::string& str) -> Integer;
    [[nodiscard]] auto compareTo(const Integer& other) const -> int32_t override;
    [[nodiscard]] bool equals(const Integer& other) const override;
    auto operator==(const Integer& other) const -> bool;
    auto operator!=(const Integer& other) const -> bool;
    auto operator<(const Integer& other) const -> bool;
    auto operator>(const Integer& other) const -> bool;
    auto operator<=(const Integer& other) const -> bool;
    auto operator>=(const Integer& other) const -> bool;
    auto operator+(const Integer& other) const -> Integer;
    auto operator-(const Integer& other) const -> Integer;
    auto operator*(const Integer& other) const -> Integer;
    auto operator/(const Integer& other) const -> Integer;

  private:
    int32_t value_{0};
    friend std::formatter<Integer>;
  };
} // namespace framework::entity::base_type
template <>
struct std::formatter<framework::entity::base_type::Integer> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Integer& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Integer& content) -> std::ostream& {
  return os << std::format("{}", content);
}
