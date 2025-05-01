#pragma once
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
  class Boolean final : public Object, public iface::IComparable<Boolean> {
  public:
    explicit Boolean(bool value);
    ~Boolean() override;
    explicit operator bool() const;
    [[nodiscard]] auto toString() const -> std::string override;
    [[nodiscard]] auto boolValue() const -> bool;
    [[nodiscard]] auto compareTo(const Boolean& other) const -> int32_t override;
    static auto parseBoolean(const std::string& str) -> Boolean;
    [[nodiscard]] auto booleanValue() const -> bool;
    [[nodiscard]] auto equals(const Boolean& other) const -> bool override;
    auto operator==(const Boolean& other) const -> bool;
    auto operator!=(const Boolean& other) const -> bool;

  private:
    bool value_{false};
    friend std::formatter<Boolean>;
  };
  const Boolean True{true};
  const Boolean False{false};
} // namespace framework::entity::base_type
template <>
struct std::formatter<framework::entity::base_type::Boolean> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Boolean& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Boolean& content) -> std::ostream& {
  return os << std::format("{}", content);
}
