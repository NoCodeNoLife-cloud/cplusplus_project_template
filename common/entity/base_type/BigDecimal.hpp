#pragma once
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <stdexcept>

namespace common::entity::base_type
{
    class BigDecimal
    {
    public:
        explicit BigDecimal(const std::string& str) : value_(str)
        {
        }

        explicit BigDecimal(const double num) : value_(num)
        {
        }

        auto operator+(const BigDecimal& other) const -> BigDecimal
        {
            return {BigDecimal((value_ + other.value_).convert_to<std::string>())};
        }

        auto operator-(const BigDecimal& other) const -> BigDecimal
        {
            return {BigDecimal((value_ - other.value_).convert_to<std::string>())};
        }

        auto operator*(const BigDecimal& other) const -> BigDecimal
        {
            return {BigDecimal((value_ * other.value_).convert_to<std::string>())};
        }

        auto operator/(const BigDecimal& other) const -> BigDecimal
        {
            if (other.value_ == 0)
            {
                throw std::invalid_argument("Division by zero is not allowed.");
            }
            return {BigDecimal((value_ / other.value_).convert_to<std::string>())};
        }

        auto operator==(const BigDecimal& other) const -> bool
        {
            return value_ == other.value_;
        }

        auto operator!=(const BigDecimal& other) const -> bool
        {
            return value_ != other.value_;
        }

        auto operator<(const BigDecimal& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator>(const BigDecimal& other) const -> bool
        {
            return value_ > other.value_;
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            return value_.convert_to<std::string>();
        }

    private:
        boost::multiprecision::cpp_dec_float_100 value_;
    };
}
