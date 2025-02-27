#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Character final : public Object, public iface::IComparable<Character>
    {
    public:
        explicit Character(char value);
        ~Character() override;
        explicit operator char() const;
        [[nodiscard]] auto toString() const -> std::string override;
        [[nodiscard]] auto equals(const Character& other) const -> bool override;
        [[nodiscard]] auto compareTo(const Character& other) const -> int override;
        static auto isLetter(char c) -> bool;
        static auto isDigit(char c) -> bool;
        static auto isLetterOrDigit(char c) -> bool;
        static auto isUpperCase(char c) -> bool;
        static auto isLowerCase(char c) -> bool;
        static auto toUpperCase(char c) -> int;
        static auto toLowerCase(char c) -> int;
        [[nodiscard]] auto characterValue() const -> char;
        auto operator==(const Character& other) const -> bool;
        auto operator!=(const Character& other) const -> bool;
        auto operator<(const Character& other) const -> bool;
        auto operator>(const Character& other) const -> bool;
        auto operator<=(const Character& other) const -> bool;
        auto operator>=(const Character& other) const -> bool;
    private:
        char value_{0};
        friend std::formatter<Character>;
    };

    inline Character::Character(const char value): value_(value) {}

    inline Character::~Character() = default;

    inline Character::operator char() const
    {
        return value_;
    }

    inline std::string Character::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Character::equals(const Character& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Character::compareTo(const Character& other) const -> int
    {
        return value_ - other.value_;
    }

    inline auto Character::isLetter(const char c) -> bool
    {
        return std::isalpha(c);
    }

    inline auto Character::isDigit(const char c) -> bool
    {
        return std::isdigit(c);
    }

    inline auto Character::isLetterOrDigit(const char c) -> bool
    {
        return std::isalnum(c);
    }

    inline auto Character::isUpperCase(const char c) -> bool
    {
        return std::isupper(c);
    }

    inline auto Character::isLowerCase(const char c) -> bool
    {
        return std::islower(c);
    }

    inline auto Character::toUpperCase(const char c) -> int
    {
        return std::toupper(c);
    }

    inline auto Character::toLowerCase(const char c) -> int
    {
        return std::tolower(c);
    }

    inline auto Character::characterValue() const -> char
    {
        return value_;
    }

    inline auto Character::operator==(const Character& other) const -> bool
    {
        return equals(other);
    }

    inline auto Character::operator!=(const Character& other) const -> bool
    {
        return !equals(other);
    }

    inline auto Character::operator<(const Character& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto Character::operator>(const Character& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto Character::operator<=(const Character& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto Character::operator>=(const Character& other) const -> bool
    {
        return value_ >= other.value_;
    }
}

template <> struct std::formatter<common::entity::base_type::Character>
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

    static auto format(const common::entity::base_type::Character& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Character& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
