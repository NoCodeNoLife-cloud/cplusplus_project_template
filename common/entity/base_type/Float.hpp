#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
    class Float final : public Object, public iface::IfaceComparable<Float>
    {
    public:
        static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
        static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
        static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
        static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
        static constexpr float MIN_VALUE = std::numeric_limits<float>::min();

        explicit Float(const float value) : value_(value)
        {
        }

        ~Float() override = default;

        explicit operator float() const
        {
            return value_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto equals(const Float& other) const -> bool override
        {
            return value_ == other.value_;
        }

        [[nodiscard]] auto compareTo(const Float& other) const -> int override
        {
            return (value_ > other.value_) - (value_ < other.value_);
        }

        [[nodiscard]] auto floatValue() const -> float
        {
            return value_;
        }

        static auto parseFloat(const std::string& str) -> Float
        {
            try
            {
                const float result = std::stof(str);
                return Float(result);
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid input string for Float conversion");
            } catch (const std::out_of_range&)
            {
                throw std::out_of_range("Value out of range for Float");
            }
        }

        auto operator==(const Float& other) const -> bool
        {
            return value_ == other.value_;
        }

        auto operator!=(const Float& other) const -> bool
        {
            return value_ != other.value_;
        }

        auto operator<(const Float& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const Float& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator<=(const Float& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>=(const Float& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto operator+(const Float& other) const -> Float
        {
            return Float(this->value_ + other.value_);
        }

        auto operator-(const Float& other) const -> Float
        {
            return Float(this->value_ - other.value_);
        }

        auto operator*(const Float& other) const -> Float
        {
            return Float(this->value_ * other.value_);
        }

        auto operator/(const Float& other) const -> Float
        {
            if (other.value_ == 0.0f)
            {
                throw std::overflow_error("Division by zero");
            }
            return Float(this->value_ / other.value_);
        }

    private:
        float value_{0.0};
        friend std::formatter<Float>;
    };
}

template <>
struct std::formatter<common::entity::base_type::Float>
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

    static auto format(const common::entity::base_type::Float& content,
                       format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Float& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
