#include "BigDecimal.hpp"

#include <stdexcept>

namespace common
{
    BigDecimal::BigDecimal(const std::string& str) : value_(str)
    {
    }

    BigDecimal::BigDecimal(const double num) : value_(num)
    {
    }

    auto BigDecimal::operator+(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ + other.value_).convert_to<std::string>())};
    }

    auto BigDecimal::operator-(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ - other.value_).convert_to<std::string>())};
    }

    auto BigDecimal::operator*(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ * other.value_).convert_to<std::string>())};
    }

    auto BigDecimal::operator/(const BigDecimal& other) const -> BigDecimal
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return {BigDecimal((value_ / other.value_).convert_to<std::string>())};
    }

    auto BigDecimal::operator<=>(const BigDecimal& other) const -> std::partial_ordering
    {
        if (value_ < other.value_)
        {
            return std::strong_ordering::less;
        }
        if (value_ > other.value_)
        {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }
}
