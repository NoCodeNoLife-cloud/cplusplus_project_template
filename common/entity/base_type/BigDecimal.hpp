#pragma once
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <stdexcept>

namespace common::entity::base_type
{
    class BigDecimal
    {
    public:
        explicit BigDecimal(const std::string& str);
        explicit BigDecimal(double num);
        auto operator+(const BigDecimal& other) const -> BigDecimal;
        auto operator-(const BigDecimal& other) const -> BigDecimal;
        auto operator*(const BigDecimal& other) const -> BigDecimal;
        auto operator/(const BigDecimal& other) const -> BigDecimal;
        auto operator==(const BigDecimal& other) const -> bool;
        auto operator!=(const BigDecimal& other) const -> bool;
        auto operator<(const BigDecimal& other) const -> bool;
        auto operator>(const BigDecimal& other) const -> bool;
        [[nodiscard]] auto toString() const -> std::string;
    private:
        boost::multiprecision::cpp_dec_float_100 value_;
    };

    inline BigDecimal::BigDecimal(const std::string& str): value_(str) {}

    inline BigDecimal::BigDecimal(const double num): value_(num) {}

    inline auto BigDecimal::operator+(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ + other.value_).convert_to<std::string>())};
    }

    inline auto BigDecimal::operator-(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ - other.value_).convert_to<std::string>())};
    }

    inline auto BigDecimal::operator*(const BigDecimal& other) const -> BigDecimal
    {
        return {BigDecimal((value_ * other.value_).convert_to<std::string>())};
    }

    inline auto BigDecimal::operator/(const BigDecimal& other) const -> BigDecimal
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return {BigDecimal((value_ / other.value_).convert_to<std::string>())};
    }

    inline auto BigDecimal::operator==(const BigDecimal& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto BigDecimal::operator!=(const BigDecimal& other) const -> bool
    {
        return value_ != other.value_;
    }

    inline auto BigDecimal::operator<(const BigDecimal& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto BigDecimal::operator>(const BigDecimal& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto BigDecimal::toString() const -> std::string
    {
        return value_.convert_to<std::string>();
    }
}
