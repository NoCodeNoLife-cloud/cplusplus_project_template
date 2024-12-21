#pragma once
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Boolean final : public Object, public iface::IComparable<Boolean>
    {
    public:
        static const Boolean TRUE;
        static const Boolean FALSE;
        explicit Boolean(bool value);
        ~Boolean() override;
        explicit operator bool() const;
        [[nodiscard]] auto toString() const -> std::string override;
        [[nodiscard]] auto boolValue() const -> bool;
        [[nodiscard]] auto compareTo(const Boolean& other) const -> int override;
        static auto parseBoolean(const std::string& str) -> Boolean;
        [[nodiscard]] auto booleanValue() const -> bool;
        [[nodiscard]] auto equals(const Boolean& other) const -> bool override;
        auto operator==(const Boolean& other) const -> bool;
        auto operator!=(const Boolean& other) const -> bool;
    private:
        bool value_{false};
        friend std::formatter<Boolean>;
    };

    inline Boolean::Boolean(const bool value): value_(value) {}

    inline Boolean::~Boolean() = default;

    inline Boolean::operator bool() const
    {
        return value_;
    }

    inline std::string Boolean::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Boolean::boolValue() const -> bool
    {
        return value_;
    }

    inline auto Boolean::compareTo(const Boolean& other) const -> int
    {
        return value_ - other.value_;
    }

    inline auto Boolean::parseBoolean(const std::string& str) -> Boolean
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

    inline auto Boolean::booleanValue() const -> bool
    {
        return value_;
    }

    inline auto Boolean::equals(const Boolean& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Boolean::operator==(const Boolean& other) const -> bool
    {
        return equals(other);
    }

    inline auto Boolean::operator!=(const Boolean& other) const -> bool
    {
        return !equals(other);
    }

    inline const Boolean TRUE{true};
    inline const Boolean FALSE{false};
}

template <> struct std::formatter<common::entity::base_type::Boolean>
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

    static auto format(const common::entity::base_type::Boolean& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Boolean& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
