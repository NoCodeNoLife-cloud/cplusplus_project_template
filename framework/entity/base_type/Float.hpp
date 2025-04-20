#pragma once
#include <format>
#include <iostream>
#include <string>

#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
  class Float final : public Object, public iface::IComparable<Float> {
  public:
    static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
    static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
    static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
    static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
    static constexpr float MIN_VALUE = std::numeric_limits<float>::min();

    explicit Float(float value);

    ~Float() override;

    explicit operator float() const;

    [[nodiscard]] auto toString() const -> std::string override;

    [[nodiscard]] auto equals(const Float& other) const -> bool override;

    [[nodiscard]] auto compareTo(const Float& other) const -> int32_t override;

    [[nodiscard]] auto floatValue() const -> float;

    static auto parseFloat(const std::string& str) -> Float;

    auto operator==(const Float& other) const -> bool;

    auto operator!=(const Float& other) const -> bool;

    auto operator<(const Float& other) const -> bool;

    auto operator>(const Float& other) const -> bool;

    auto operator<=(const Float& other) const -> bool;

    auto operator>=(const Float& other) const -> bool;

    auto operator+(const Float& other) const -> Float;

    auto operator-(const Float& other) const -> Float;

    auto operator*(const Float& other) const -> Float;

    auto operator/(const Float& other) const -> Float;

  private:
    float value_{0.0};
    friend std::formatter<Float>;
  };
} // namespace framework::entity::base_type

template <>
struct std::formatter<framework::entity::base_type::Float> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const framework::entity::base_type::Float& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Float& content) -> std::ostream& {
  return os << std::format("{}", content);
}
