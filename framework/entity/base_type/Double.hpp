#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace framework::entity::base_type {
    class Double final : public Object, public iface::IComparable<Double>
    {
    public:
        static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
        static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
        static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
        static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
        static constexpr double MIN_VALUE = std::numeric_limits<double>::min();

        explicit Double(double value);

        ~Double() override;

        explicit operator double() const;

        [[nodiscard]] auto toString() const -> std::string override;

        [[nodiscard]] auto equals(const Double& other) const -> bool override;

        [[nodiscard]] auto compareTo(const Double& other) const -> int32_t override;

        [[nodiscard]] auto doubleValue() const -> double;

        static auto parseDouble(const std::string& str) -> Double;

        auto operator==(const Double& other) const -> bool;

        auto operator!=(const Double& other) const -> bool;

        auto operator<(const Double& other) const -> bool;

        auto operator>(const Double& other) const -> bool;

        auto operator<=(const Double& other) const -> bool;

        auto operator>=(const Double& other) const -> bool;

        auto operator+(const Double& other) const -> Double;

        auto operator-(const Double& other) const -> Double;

        auto operator*(const Double& other) const -> Double;

        auto operator/(const Double& other) const -> Double;

    private:
        friend std::formatter<Double>;
        double value_{0.0};
    };
} // namespace framework::entity::base_type
template <>
struct std::formatter<framework::entity::base_type::Double>
{
    constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
        const auto begin = ctx.begin();
        if (const auto end = ctx.end(); begin != end && *begin != '}') { throw std::format_error("invalid format"); }
        return begin;
    }

    static auto format(const framework::entity::base_type::Double& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> { return std::format_to(ctx.out(), "{}", content.value_); }
};

inline auto operator<<(std::ostream& os, const framework::entity::base_type::Double& content) -> std::ostream& { return os << std::format("{}", content); }
