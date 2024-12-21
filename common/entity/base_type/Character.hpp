#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Character final : public Object, public iface::IfaceComparable<Character>
    {
    public:
        explicit Character(const char value) : value_(value)
        {
        }

        ~Character() override = default;

        explicit operator char() const
        {
            return value_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto equals(const Character& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Character& other) const -> int override
        {
            return value_ - other.value_;
        }

        static auto isLetter(const char c) -> bool
        {
            return std::isalpha(c);
        }

        static auto isDigit(const char c) -> bool
        {
            return std::isdigit(c);
        }

        static auto isLetterOrDigit(const char c) -> bool
        {
            return std::isalnum(c);
        }

        static auto isUpperCase(const char c) -> bool
        {
            return std::isupper(c);
        }

        static auto isLowerCase(const char c) -> bool
        {
            return std::islower(c);
        }

        static auto toUpperCase(const char c) -> int
        {
            return std::toupper(c);
        }

        static auto toLowerCase(const char c) -> int
        {
            return std::tolower(c);
        }

        [[nodiscard]] auto characterValue() const -> char
        {
            return value_;
        }

        auto operator==(const Character& other) const -> bool
        {
            return equals(other);
        }

        auto operator!=(const Character& other) const -> bool
        {
            return !equals(other);
        }

        auto operator<(const Character& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Character& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Character& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Character& other) const -> bool
        {
            return value_ >= other.value_;
        }

    private:
        char value_{0};
        friend std::formatter<Character>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Character>
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

    static auto format(const common::entity::base_type::Character& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Character& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
