#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Short final : public Object, public iface::IfaceComparable<Short>
    {
    public:
        static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
        static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();

        explicit Short(const int16_t value) : value_(value)
        {
        }

        ~Short() override = default;

        explicit operator short() const
        {
            return value_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto shortValue() const -> int16_t
        {
            return value_;
        }

        [[nodiscard]] auto equals(const Short& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Short& other) const -> int override
        {
            return value_ - other.value_;
        }

        static auto parseShort(const std::string& str) -> Short
        {
            try
            {
                const auto result = static_cast<int16_t>(std::stoi(str));
                if (result > MAX_VALUE || result < MIN_VALUE)
                {
                    throw std::out_of_range("Value out of range for Short");
                }
                return Short(result);
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid input string for Short conversion");
            } catch (const std::out_of_range&)
            {
                throw std::out_of_range("Value out of range for Short");
            }
        }

        auto operator==(const Short& other) const -> bool
        {
            return equals(other);
        }

        auto operator!=(const Short& other) const -> bool
        {
            return !equals(other);
        }

        auto operator<(const Short& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Short& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Short& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Short& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto operator+(const Short& other) const -> Short
        {
            return Short(static_cast<int16_t>(this->value_ + other.value_));
        }

        auto operator-(const Short& other) const -> Short
        {
            return Short(static_cast<int16_t>(this->value_ - other.value_));
        }

        auto operator*(const Short& other) const -> Short
        {
            return Short(static_cast<int16_t>(this->value_ * other.value_));
        }

        auto operator/(const Short& other) const -> Short
        {
            if (other.value_ == 0)
            {
                throw std::overflow_error("Division by zero");
            }
            return Short(static_cast<int16_t>(this->value_ / other.value_));
        }

        auto operator%(const Short& other) const -> Short
        {
            if (other.value_ == 0)
            {
                throw std::overflow_error("Modulo by zero");
            }
            return Short(static_cast<int16_t>(this->value_ % other.value_));
        }

    private:
        int16_t value_{0};
        friend std::formatter<Short>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Short>
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

    static auto format(const common::entity::base_type::Short& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Short& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
