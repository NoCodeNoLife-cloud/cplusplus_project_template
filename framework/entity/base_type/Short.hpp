#pragma once
#include <format>
#include <iostream>
#include <string>

#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
  class Short final : public Object, public iface::IComparable<Short> {
  public:
    static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
    static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();

    explicit Short(int16_t value);

    ~Short() override;

    explicit operator short() const;

    [[nodiscard]] auto toString() const -> std::string override;

    [[nodiscard]] auto shortValue() const -> int16_t;

    [[nodiscard]] auto equals(const Short& other) const -> bool override;

    [[nodiscard]] auto compareTo(const Short& other) const -> int32_t override;

    static auto parseShort(const std::string& str) -> Short;

    auto operator==(const Short& other) const -> bool;

    auto operator!=(const Short& other) const -> bool;

    auto operator<(const Short& other) const -> bool;

    auto operator>(const Short& other) const -> bool;

    auto operator<=(const Short& other) const -> bool;

    auto operator>=(const Short& other) const -> bool;

    auto operator+(const Short& other) const -> Short;

    auto operator-(const Short& other) const -> Short;

    auto operator*(const Short& other) const -> Short;

    auto operator/(const Short& other) const -> Short;

    auto operator%(const Short& other) const -> Short;

  private:
    int16_t value_{0};
    friend std::formatter<Short>;
  };
} // namespace framework::entity::base_type

template <>
struct std::formatter<framework::entity::base_type::Short> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Short& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Short& content) -> std::ostream& {
  return os << std::format("{}", content);
}
