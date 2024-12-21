#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Long final : public Object, public iface::IfaceComparable<Long>
    {
    public:
        static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
        static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();

        explicit Long(const int64_t value) : value_(value)
        {
        }

        ~Long() override = default;

        explicit operator long() const
        {
            return static_cast<long>(value_);
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto longValue() const -> int64_t
        {
            return value_;
        }

        [[nodiscard]] auto equals(const Long& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Long& other) const -> int override
        {
            return (value_ > other.value_) - (value_ < other.value_);
        }

        static auto parseLong(const std::string& str) -> Long
        {
            try
            {
                const int64_t result = std::stoll(str);
                return Long(result);
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid input string for Long conversion");
            } catch (const std::out_of_range&)
            {
                throw std::out_of_range("Value out of range for Long");
            }
        }

        auto operator==(const Long& other) const -> bool
        {
            return equals(other);
        }

        auto operator!=(const Long& other) const -> bool
        {
            return !equals(other);
        }

        auto operator<(const Long& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Long& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Long& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Long& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto operator+(const Long& other) const -> Long
        {
            return Long(this->value_ + other.value_);
        }

        auto operator-(const Long& other) const -> Long
        {
            return Long(this->value_ - other.value_);
        }

        auto operator*(const Long& other) const -> Long
        {
            return Long(this->value_ * other.value_);
        }

        auto operator/(const Long& other) const -> Long
        {
            if (other.value_ == 0)
            {
                throw std::overflow_error("Division by zero");
            }
            return Long(this->value_ / other.value_);
        }

        auto operator%(const Long& other) const -> Long
        {
            if (other.value_ == 0)
            {
                throw std::overflow_error("Modulo by zero");
            }
            return Long(this->value_ % other.value_);
        }

    private:
        int64_t value_{0};
        friend std::formatter<Long>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Long>
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

    static auto format(const common::entity::base_type::Long& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Long& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
