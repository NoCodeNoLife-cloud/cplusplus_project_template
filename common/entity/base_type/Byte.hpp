#pragma once
#include <format>
#include <iostream>
#include <string>
#include <entity/base_type/Object.hpp>
#include <entity/interface/IComparable.hpp>

namespace common {
  class Byte final : public Object, public IComparable<Byte> {
  public:
    static constexpr uint8_t MIN_VALUE = std::numeric_limits<uint8_t>::min();
    static constexpr uint8_t MAX_VALUE = std::numeric_limits<uint8_t>::max();
    explicit Byte(uint8_t value = 0);
    ~Byte() override;
    explicit operator unsigned char() const;
    [[nodiscard]] auto equals(const Byte& other) const -> bool override;
    [[nodiscard]] auto compareTo(const Byte& other) const -> int32_t override;
    [[nodiscard]] auto toString() const -> std::string override;
    static auto parseByte(const std::string& str) -> Byte;
    [[nodiscard]] auto byteValue() const -> uint8_t;
    auto operator<=>(const Byte& other) const -> std::partial_ordering;
    auto operator+(const Byte& other) const -> Byte;
    auto operator-(const Byte& other) const -> Byte;

  private:
    uint8_t value_{0};
    friend std::formatter<Byte>;
  };
}

template <>
struct std::formatter<common::Byte> {
  constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
    const auto begin = ctx.begin();
    if (const auto end = ctx.end(); begin != end && *begin != '}') {
      throw std::format_error("invalid format");
    }
    return begin;
  }

  static auto format(const common::Byte& content, format_context& ctx)
    -> back_insert_iterator<_Fmt_buffer<char>> {
    return std::format_to(ctx.out(), "{}", content.value_);
  }
};

inline auto operator<<(std::ostream& os, const common::Byte& content) -> std::ostream& {
  return os << std::format("{}", content);
}
