#pragma once
#include <format>
#include <iostream>
#include <string>
#include <entity/base_type/Object.hpp>
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
  class Byte final : public Object, public iface::IComparable<Byte> {
  public:
    static constexpr int8_t MIN_VALUE = std::numeric_limits<int8_t>::min();
    static constexpr int8_t MAX_VALUE = std::numeric_limits<int8_t>::max();
    explicit Byte(int8_t value = 0);
    ~Byte() override;
    explicit operator signed char() const;
    [[nodiscard]] auto equals(const Byte& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Byte& other) const -> int32_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    static auto parseByte(const std::string& str) -> Byte;
    [[nodiscard]] auto byteValue() const -> int8_t;
    auto operator==(const Byte& other) const -> bool;
    auto operator!=(const Byte& other) const -> bool;
    auto operator<(const Byte& other) const -> bool;
    auto operator>(const Byte& other) const -> bool;
    auto operator<=(const Byte& other) const -> bool;
    auto operator>=(const Byte& other) const -> bool;
    auto operator+(const Byte& other) const -> Byte;
    auto operator-(const Byte& other) const -> Byte;

  private:
    int8_t value_{0};
    friend std::formatter<Byte>;
  };
} // namespace framework::entity::base_type
template <>
struct std::formatter<framework::entity::base_type::Byte> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Byte& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Byte& content) -> std::ostream& {
  return os << std::format("{}", content);
}
