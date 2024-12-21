#pragma once
#include <format>
#include <iostream>
#include <string>
#include <entity/base_type/Object.hpp>
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Byte final : public Object, public iface::IfaceComparable<Byte>
    {
    public:
        static constexpr int8_t MIN_VALUE = std::numeric_limits<int8_t>::min();
        static constexpr int8_t MAX_VALUE = std::numeric_limits<int8_t>::max();

        explicit Byte(const int8_t value = 0): value_(value)
        {
        }

        ~Byte() override = default;

        explicit operator signed char() const
        {
            return value_;
        }

        [[nodiscard]] auto equals(const Byte& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Byte& other) const -> int override
        {
            return (value_ > other.value_) - (value_ < other.value_);
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        static auto parseByte(const std::string& str) -> Byte
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

        [[nodiscard]] auto byteValue() const -> int8_t
        {
            return value_;
        }

        auto operator==(const Byte& other) const -> bool
        {
            return equals(other);
        }

        auto operator!=(const Byte& other) const -> bool
        {
            return !equals(other);
        }

        auto operator<(const Byte& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Byte& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Byte& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Byte& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto operator+(const Byte& other) const -> Byte
        {
            const int result = this->value_ + other.value_;
            if (result < MIN_VALUE || result > MAX_VALUE)
            {
                throw std::overflow_error("Byte overflow in addition");
            }
            return Byte(static_cast<int8_t>(result));
        }

        auto operator-(const Byte& other) const -> Byte
        {
            const int result = this->value_ - other.value_;
            if (result < MIN_VALUE || result > MAX_VALUE)
            {
                throw std::overflow_error("Byte overflow in subtraction");
            }
            return Byte(static_cast<int8_t>(result));
        }

    private:
        int8_t value_{0};
        friend std::formatter<Byte>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Byte>
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

    static auto format(const common::entity::base_type::Byte& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Byte& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
