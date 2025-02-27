#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Long final : public Object, public iface::IComparable<Long>
    {
    public:
        static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
        static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();
        explicit Long(int64_t value);
        ~Long() override;
        explicit operator long() const;
        [[nodiscard]] auto toString() const -> std::string override;
        [[nodiscard]] auto longValue() const -> int64_t;
        [[nodiscard]] auto equals(const Long& other) const -> bool override;
        [[nodiscard]] auto compareTo(const Long& other) const -> int override;
        static auto parseLong(const std::string& str) -> Long;
        auto operator==(const Long& other) const -> bool;
        auto operator!=(const Long& other) const -> bool;
        auto operator<(const Long& other) const -> bool;
        auto operator>(const Long& other) const -> bool;
        auto operator<=(const Long& other) const -> bool;
        auto operator>=(const Long& other) const -> bool;
        auto operator+(const Long& other) const -> Long;
        auto operator-(const Long& other) const -> Long;
        auto operator*(const Long& other) const -> Long;
        auto operator/(const Long& other) const -> Long;
        auto operator%(const Long& other) const -> Long;
    private:
        int64_t value_{0};
        friend std::formatter<Long>;
    };

    inline Long::Long(const int64_t value): value_(value) {}

    inline Long::~Long() = default;

    inline Long::operator long() const
    {
        return static_cast<long>(value_);
    }

    inline std::string Long::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Long::longValue() const -> int64_t
    {
        return value_;
    }

    inline auto Long::equals(const Long& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Long::compareTo(const Long& other) const -> int
    {
        return (value_ > other.value_) - (value_ < other.value_);
    }

    inline auto Long::parseLong(const std::string& str) -> Long
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

    inline auto Long::operator==(const Long& other) const -> bool
    {
        return equals(other);
    }

    inline auto Long::operator!=(const Long& other) const -> bool
    {
        return !equals(other);
    }

    inline auto Long::operator<(const Long& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto Long::operator>(const Long& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto Long::operator<=(const Long& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto Long::operator>=(const Long& other) const -> bool
    {
        return value_ >= other.value_;
    }

    inline auto Long::operator+(const Long& other) const -> Long
    {
        return Long(this->value_ + other.value_);
    }

    inline auto Long::operator-(const Long& other) const -> Long
    {
        return Long(this->value_ - other.value_);
    }

    inline auto Long::operator*(const Long& other) const -> Long
    {
        return Long(this->value_ * other.value_);
    }

    inline auto Long::operator/(const Long& other) const -> Long
    {
        if (other.value_ == 0)
        {
            throw std::overflow_error("Division by zero");
        }
        return Long(this->value_ / other.value_);
    }

    inline auto Long::operator%(const Long& other) const -> Long
    {
        if (other.value_ == 0)
        {
            throw std::overflow_error("Modulo by zero");
        }
        return Long(this->value_ % other.value_);
    }
}

template <> struct std::formatter<common::entity::base_type::Long>
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

    static auto format(const common::entity::base_type::Long& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Long& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
