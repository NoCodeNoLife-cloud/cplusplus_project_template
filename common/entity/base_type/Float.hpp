#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IComparable.hpp"

namespace common::entity::base_type
{
    class Float final : public Object, public iface::IComparable<Float>
    {
    public:
        static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
        static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
        static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
        static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
        static constexpr float MIN_VALUE = std::numeric_limits<float>::min();
        explicit Float(float value);
        ~Float() override;
        explicit operator float() const;
        [[nodiscard]] auto toString() const -> std::string override;
        [[nodiscard]] auto equals(const Float& other) const -> bool override;
        [[nodiscard]] auto compareTo(const Float& other) const -> int override;
        [[nodiscard]] auto floatValue() const -> float;
        static auto parseFloat(const std::string& str) -> Float;
        auto operator==(const Float& other) const -> bool;
        auto operator!=(const Float& other) const -> bool;
        auto operator<(const Float& other) const -> bool;
        auto operator>(const Float& other) const -> bool;
        auto operator<=(const Float& other) const -> bool;
        auto operator>=(const Float& other) const -> bool;
        auto operator+(const Float& other) const -> Float;
        auto operator-(const Float& other) const -> Float;
        auto operator*(const Float& other) const -> Float;
        auto operator/(const Float& other) const -> Float;
    private:
        float value_{0.0};
        friend std::formatter<Float>;
    };

    inline Float::Float(const float value): value_(value) {}

    inline Float::~Float() = default;

    inline Float::operator float() const
    {
        return value_;
    }

    inline std::string Float::toString() const
    {
        return std::format("{}", *this);
    }

    inline auto Float::equals(const Float& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Float::compareTo(const Float& other) const -> int
    {
        return (value_ > other.value_) - (value_ < other.value_);
    }

    inline auto Float::floatValue() const -> float
    {
        return value_;
    }

    inline auto Float::parseFloat(const std::string& str) -> Float
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

    inline auto Float::operator==(const Float& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto Float::operator!=(const Float& other) const -> bool
    {
        return value_ != other.value_;
    }

    inline auto Float::operator<(const Float& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto Float::operator>(const Float& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto Float::operator<=(const Float& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto Float::operator>=(const Float& other) const -> bool
    {
        return value_ >= other.value_;
    }

    inline auto Float::operator+(const Float& other) const -> Float
    {
        return Float(this->value_ + other.value_);
    }

    inline auto Float::operator-(const Float& other) const -> Float
    {
        return Float(this->value_ - other.value_);
    }

    inline auto Float::operator*(const Float& other) const -> Float
    {
        return Float(this->value_ * other.value_);
    }

    inline auto Float::operator/(const Float& other) const -> Float
    {
        if (other.value_ == 0.0f)
        {
            throw std::overflow_error("Division by zero");
        }
        return Float(this->value_ / other.value_);
    }
}

template <> struct std::formatter<common::entity::base_type::Float>
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

    static auto format(const common::entity::base_type::Float& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "{}", content.value_);
    }
};

inline auto operator<<(std::ostream& os, const common::entity::base_type::Float& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
