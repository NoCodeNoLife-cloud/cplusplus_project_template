#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Double final : public Object, public iface::IfaceComparable<Double>
    {
    public:
        static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
        static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
        static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
        static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
        static constexpr double MIN_VALUE = std::numeric_limits<double>::min();

        explicit Double(const double value) : value_(value)
        {
        }

        ~Double() override = default;

        explicit operator double() const
        {
            return value_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto equals(const Double& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Double& other) const -> int override
        {
            return (value_ > other.value_) - (value_ < other.value_);
        }

        [[nodiscard]] auto doubleValue() const -> double
        {
            return value_;
        }

        static auto parseDouble(const std::string& str) -> Double
        {
            try
            {
                const double result = std::stod(str);
                return Double(result);
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid input string for Double conversion");
            } catch (const std::out_of_range&)
            {
                throw std::out_of_range("Value out of range for Double");
            }
        }

        auto operator==(const Double& other) const -> bool
        {
            return value_ == other.value_;
        }

        auto operator!=(const Double& other) const -> bool
        {
            return value_ != other.value_;
        }

        auto operator<(const Double& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Double& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Double& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Double& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto operator+(const Double& other) const -> Double
        {
            return Double(this->value_ + other.value_);
        }

        auto operator-(const Double& other) const -> Double
        {
            return Double(this->value_ - other.value_);
        }

        auto operator*(const Double& other) const -> Double
        {
            return Double(this->value_ * other.value_);
        }

        auto operator/(const Double& other) const -> Double
        {
            if (other.value_ == 0.0)
            {
                throw std::overflow_error("Division by zero");
            }
            return Double(this->value_ / other.value_);
        }

    private:
        friend std::formatter<Double>;
        double value_{0.0};
    };
}

template <>
struct std::formatter<common::entity::base_type::Double>
{
    constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator
    {
        const auto begin = ctx.begin();
        if (const auto end = ctx.end(); begin != end && *begin != '}')
        {
            throw std::format_error("invalid format");
        }
        return begin;
    }

    static auto format(const common::entity::base_type::Double& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Double& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
