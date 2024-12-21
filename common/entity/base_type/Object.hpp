#pragma once
#include <format>
#include <iostream>

namespace common::entity::base_type
{
    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        [[nodiscard]] auto clone() const -> std::unique_ptr<Object>
        {
            return std::make_unique<Object>(Object(*this));
        }

        [[nodiscard]] auto getClass() const -> const std::type_info&
        {
            return typeid(*this);
        }

        [[nodiscard]] auto equals(const Object& other) const -> bool
        {
            if (typeid(*this) != typeid(other))
            {
                return false;
            }
            return this == &other;
        }

        [[nodiscard]] auto hashCode() const -> size_t
        {
            return std::hash<const void*>{}(this);
        }

        [[nodiscard]] virtual auto toString() const -> std::string
        {
            return std::format("{}", *this);
        }

    private:
        friend std::formatter<Object>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Object>
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

    static auto format(const common::entity::base_type::Object& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "Object{{}}", "");
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Object& object) -> std::ostream&
{
    return os << std::format("{}", object);
}
