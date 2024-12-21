#pragma once
#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

namespace common::entity::base_type
{
    class BigInteger
    {
    public:
        BigInteger() : value_(0)
        {
        }

        explicit BigInteger(const std::string& str) : value_(str)
        {
        }

        explicit BigInteger(const long long num) : value_(num)
        {
        }

        auto operator+(const BigInteger& other) const -> BigInteger
        {
            return BigInteger((value_ + other.value_).convert_to<std::string>());
        }

        auto operator-(const BigInteger& other) const -> BigInteger
        {
            return BigInteger((value_ - other.value_).convert_to<std::string>());
        }

        auto operator*(const BigInteger& other) const -> BigInteger
        {
            return BigInteger((value_ * other.value_).convert_to<std::string>());
        }

        auto operator/(const BigInteger& other) const -> BigInteger
        {
            if (other.value_ == 0)
            {
                throw std::invalid_argument("Division by zero");
            }
            return BigInteger((value_ / other.value_).convert_to<std::string>());
        }

        auto operator%(const BigInteger& other) const -> BigInteger
        {
            if (other.value_ == 0)
            {
                throw std::invalid_argument("Modulo by zero");
            }
            return BigInteger((value_ % other.value_).convert_to<std::string>());
        }

        auto operator==(const BigInteger& other) const -> bool
        {
            return value_ == other.value_;
        }

        auto operator!=(const BigInteger& other) const -> bool
        {
            return value_ != other.value_;
        }

        auto operator<(const BigInteger& other) const -> bool
        {
            return value_ < other.value_;
        }

        auto operator<=(const BigInteger& other) const -> bool
        {
            return value_ <= other.value_;
        }

        auto operator>(const BigInteger& other) const -> bool
        {
            return value_ > other.value_;
        }

        auto operator>=(const BigInteger& other) const -> bool
        {
            return value_ >= other.value_;
        }

        auto toString() const -> std::string
        {
            return value_.str();
        }

        static auto fromString(const std::string& str) -> BigInteger
        {
            return BigInteger(str);
        }

        static auto fromInt(const long long num) -> BigInteger
        {
            return BigInteger(num);
        }

    private:
        boost::multiprecision::cpp_int value_;
    };
}
