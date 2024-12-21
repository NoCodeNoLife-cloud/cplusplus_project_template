#pragma once
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Boolean final : public Object, public iface::IfaceComparable<Boolean>
    {
    public:
        static const Boolean TRUE;
        static const Boolean FALSE;

        explicit Boolean(const bool value) : value_(value)
        {
        }

        ~Boolean() override = default;

        explicit operator bool() const
        {
            return value_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto boolValue() const -> bool
        {
            return value_;
        }

        [[nodiscard]] auto compareTo(const Boolean& other) const -> int override
        {
            return value_ - other.value_;
        }

        static auto parseBoolean(const std::string& str) -> Boolean
        {
            if (str == "true" || str == "TRUE")
            {
                return Boolean(true);
            }
            if (str == "false" || str == "FALSE")
            {
                return Boolean(false);
            }
            throw std::invalid_argument("Invalid input string for Boolean conversion");
        }

        [[nodiscard]] auto booleanValue() const -> bool
        {
            return value_;
        }

        [[nodiscard]] auto equals(const Boolean& other) const -> bool override
        {
            return value_ == other.value_;
        }

        auto operator==(const Boolean& other) const -> bool
        {
            return equals(other);
        }

        auto operator!=(const Boolean& other) const -> bool
        {
            return !equals(other);
        }

    private:
        bool value_{false};
        friend std::formatter<Boolean>;
    };

    inline const Boolean TRUE{true};
    inline const Boolean FALSE{false};
}

template <>
struct std::formatter<common::entity::base_type::Boolean>
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

    static auto format(const common::entity::base_type::Boolean& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Boolean& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
