#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Integer final : public Object, public iface::IComparable<Integer>
    {
    public:
        static constexpr int MIN_VALUE = std::numeric_limits<int>::min();
        static constexpr int MAX_VALUE = std::numeric_limits<int>::max();
        explicit Integer(int value);
        ~Integer() override;
        explicit operator int() const;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] auto intValue() const -> int;
        static auto parseInt(const std::string& str) -> Integer;
        [[nodiscard]] auto compareTo(const Integer& other) const -> int override;
        [[nodiscard]] bool equals(const Integer& other) const override;
        auto operator==(const Integer& other) const -> bool;
        auto operator!=(const Integer& other) const -> bool;
        auto operator<(const Integer& other) const -> bool;
        auto operator>(const Integer& other) const -> bool;
        auto operator<=(const Integer& other) const -> bool;
        auto operator>=(const Integer& other) const -> bool;
        auto operator+(const Integer& other) const -> Integer;
        auto operator-(const Integer& other) const -> Integer;
        auto operator*(const Integer& other) const -> Integer;
        auto operator/(const Integer& other) const -> Integer;
    private:
        int value_{0};
        friend std::formatter<Integer>;
    };

    inline Integer::Integer(const int value): value_(value) {}

    inline Integer::~Integer() = default;

    inline Integer::operator int() const
    {
        return value_;
    }

    inline std::string Integer::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Integer::intValue() const -> int
    {
        return value_;
    }

    inline auto Integer::parseInt(const std::string& str) -> Integer
    {
        try
        {
            size_t idx;
            const int result = std::stoi(str, &idx);
            if (idx != str.size())
            {
                throw std::invalid_argument("Invalid input string");
            }
            return Integer(result);
        }
        catch (const std::out_of_range&)
        {
            throw std::out_of_range("Value out of range");
        }
    }

    inline auto Integer::compareTo(const Integer& other) const -> int
    {
        return value_ - other.value_;
    }

    inline bool Integer::equals(const Integer& other) const
    {
        return value_ == other.value_;
    }

    inline auto Integer::operator==(const Integer& other) const -> bool
    {
        return equals(other);
    }

    inline auto Integer::operator!=(const Integer& other) const -> bool
    {
        return !equals(other);
    }

    inline auto Integer::operator<(const Integer& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto Integer::operator>(const Integer& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto Integer::operator<=(const Integer& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto Integer::operator>=(const Integer& other) const -> bool
    {
        return value_ >= other.value_;
    }

    inline auto Integer::operator+(const Integer& other) const -> Integer
    {
        return Integer(this->value_ + other.value_);
    }

    inline auto Integer::operator-(const Integer& other) const -> Integer
    {
        return Integer(this->value_ - other.value_);
    }

    inline auto Integer::operator*(const Integer& other) const -> Integer
    {
        return Integer(this->value_ * other.value_);
    }

    inline auto Integer::operator/(const Integer& other) const -> Integer
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return Integer(this->value_ / other.value_);
    }
}

template <> struct std::formatter<common::entity::base_type::Integer>
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

    static auto format(const common::entity::base_type::Integer& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Integer& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
