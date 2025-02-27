#pragma once
#include <format>
#include <iostream>
#include <string>
#include <entity/base_type/Object.hpp>
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Byte final : public Object, public iface::IComparable<Byte>
    {
    public:
        static constexpr int8_t MIN_VALUE = std::numeric_limits<int8_t>::min();
        static constexpr int8_t MAX_VALUE = std::numeric_limits<int8_t>::max();
        explicit Byte(int8_t value = 0);
        ~Byte() override;
        explicit operator signed char() const;
        [[nodiscard]] auto equals(const Byte& other) const -> bool override;
        [[nodiscard]] auto compareTo(const Byte& other) const -> int override;
        [[nodiscard]] auto toString() const -> std::string override;
        static auto parseByte(const std::string& str) -> Byte;
        [[nodiscard]] auto byteValue() const -> int8_t;
        auto operator==(const Byte& other) const -> bool;
        auto operator!=(const Byte& other) const -> bool;
        auto operator<(const Byte& other) const -> bool;
        auto operator>(const Byte& other) const -> bool;
        auto operator<=(const Byte& other) const -> bool;
        auto operator>=(const Byte& other) const -> bool;
        auto operator+(const Byte& other) const -> Byte;
        auto operator-(const Byte& other) const -> Byte;
    private:
        int8_t value_{0};
        friend std::formatter<Byte>;
    };

    inline Byte::Byte(const int8_t value): value_(value) {}

    inline Byte::~Byte() = default;

    inline Byte::operator signed char() const
    {
        return value_;
    }

    inline auto Byte::equals(const Byte& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Byte::compareTo(const Byte& other) const -> int
    {
        return (value_ > other.value_) - (value_ < other.value_);
    }

    inline std::string Byte::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Byte::parseByte(const std::string& str) -> Byte
    {
        try
        {
            const int result = std::stoi(str);
            if (result < MIN_VALUE || result > MAX_VALUE)
            {
                throw std::out_of_range("Value out of range for Byte");
            }
            return Byte(static_cast<int8_t>(result));
        }
        catch (const std::invalid_argument&)
        {
            throw std::invalid_argument("Invalid input string for Byte conversion");
        } catch (const std::out_of_range&)
        {
            throw std::out_of_range("Value out of range for Byte");
        }
    }

    inline auto Byte::byteValue() const -> int8_t
    {
        return value_;
    }

    inline auto Byte::operator==(const Byte& other) const -> bool
    {
        return equals(other);
    }

    inline auto Byte::operator!=(const Byte& other) const -> bool
    {
        return !equals(other);
    }

    inline auto Byte::operator<(const Byte& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto Byte::operator>(const Byte& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto Byte::operator<=(const Byte& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto Byte::operator>=(const Byte& other) const -> bool
    {
        return value_ >= other.value_;
    }

    inline auto Byte::operator+(const Byte& other) const -> Byte
    {
        const int result = this->value_ + other.value_;
        if (result < MIN_VALUE || result > MAX_VALUE)
        {
            throw std::overflow_error("Byte overflow in addition");
        }
        return Byte(static_cast<int8_t>(result));
    }

    inline auto Byte::operator-(const Byte& other) const -> Byte
    {
        const int result = this->value_ - other.value_;
        if (result < MIN_VALUE || result > MAX_VALUE)
        {
            throw std::overflow_error("Byte overflow in subtraction");
        }
        return Byte(static_cast<int8_t>(result));
    }
}

template <> struct std::formatter<common::entity::base_type::Byte>
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

    static auto format(const common::entity::base_type::Byte& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Byte& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
