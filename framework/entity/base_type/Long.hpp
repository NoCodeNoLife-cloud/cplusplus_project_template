#pragma once
#include <format>
#include <iostream>
#include <string>

#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type
{

class Long final : public Object, public iface::IComparable<Long>
{
  public:
    static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
    static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();

    explicit Long(int64_t value);

    ~Long() override;

    explicit operator int64_t() const;

    [[nodiscard]] auto toString() const -> std::string override;

    [[nodiscard]] auto longValue() const -> int64_t;

    [[nodiscard]] auto equals(const Long &other) const -> bool override;

    [[nodiscard]] auto compareTo(const Long &other) const -> int32_t override;

    static auto parseLong(const std::string &str) -> Long;

    auto operator==(const Long &other) const -> bool;

    auto operator!=(const Long &other) const -> bool;

    auto operator<(const Long &other) const -> bool;

    auto operator>(const Long &other) const -> bool;

    auto operator<=(const Long &other) const -> bool;

    auto operator>=(const Long &other) const -> bool;

    auto operator+(const Long &other) const -> Long;

    auto operator-(const Long &other) const -> Long;

    auto operator*(const Long &other) const -> Long;

    auto operator/(const Long &other) const -> Long;

    auto operator%(const Long &other) const -> Long;

  private:
    int64_t value_{0};
    friend std::formatter<Long>;
};

} // namespace framework::entity::base_type

template <> struct std::formatter<framework::entity::base_type::Long>
{
    constexpr static auto parse(format_parse_context &ctx) -> format_parse_context::const_iterator
    {
        const auto begin = ctx.begin();
        if (const auto end = ctx.end(); begin != end && *begin != '}')
        {
            throw std::format_error("invalid format");
        }
        return begin;
    }

    static auto format(const framework::entity::base_type::Long &content, format_context &ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream &os, const framework::entity::base_type::Long &content) -> std::ostream &
{
    return os << std::format("{}", content);
}
