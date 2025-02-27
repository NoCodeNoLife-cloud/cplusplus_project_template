#pragma once
#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

namespace common::entity::base_type
{
    class BigInteger
    {
    public:
        BigInteger();
        explicit BigInteger(const std::string& str);
        explicit BigInteger(long long num);
        auto operator+(const BigInteger& other) const -> BigInteger;
        auto operator-(const BigInteger& other) const -> BigInteger;
        auto operator*(const BigInteger& other) const -> BigInteger;
        auto operator/(const BigInteger& other) const -> BigInteger;
        auto operator%(const BigInteger& other) const -> BigInteger;
        auto operator==(const BigInteger& other) const -> bool;
        auto operator!=(const BigInteger& other) const -> bool;
        auto operator<(const BigInteger& other) const -> bool;
        auto operator<=(const BigInteger& other) const -> bool;
        auto operator>(const BigInteger& other) const -> bool;
        auto operator>=(const BigInteger& other) const -> bool;
        [[nodiscard]] auto toString() const -> std::string;
        static auto fromString(const std::string& str) -> BigInteger;
        static auto fromInt(long long num) -> BigInteger;
    private:
        boost::multiprecision::cpp_int value_;
    };

    inline BigInteger::BigInteger(): value_(0) {}

    inline BigInteger::BigInteger(const std::string& str): value_(str) {}

    inline BigInteger::BigInteger(const long long num): value_(num) {}

    inline auto BigInteger::operator+(const BigInteger& other) const -> BigInteger
    {
        return BigInteger((value_ + other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator-(const BigInteger& other) const -> BigInteger
    {
        return BigInteger((value_ - other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator*(const BigInteger& other) const -> BigInteger
    {
        return BigInteger((value_ * other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator/(const BigInteger& other) const -> BigInteger
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        return BigInteger((value_ / other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator%(const BigInteger& other) const -> BigInteger
    {
        if (other.value_ == 0)
        {
            throw std::invalid_argument("Modulo by zero");
        }
        return BigInteger((value_ % other.value_).convert_to<std::string>());
    }

    inline auto BigInteger::operator==(const BigInteger& other) const -> bool
    {
        return value_ == other.value_;
    }

    inline auto BigInteger::operator!=(const BigInteger& other) const -> bool
    {
        return value_ != other.value_;
    }

    inline auto BigInteger::operator<(const BigInteger& other) const -> bool
    {
        return value_ < other.value_;
    }

    inline auto BigInteger::operator<=(const BigInteger& other) const -> bool
    {
        return value_ <= other.value_;
    }

    inline auto BigInteger::operator>(const BigInteger& other) const -> bool
    {
        return value_ > other.value_;
    }

    inline auto BigInteger::operator>=(const BigInteger& other) const -> bool
    {
        return value_ >= other.value_;
    }

    inline auto BigInteger::toString() const -> std::string
    {
        return value_.str();
    }

    inline auto BigInteger::fromString(const std::string& str) -> BigInteger
    {
        return BigInteger(str);
    }

    inline auto BigInteger::fromInt(const long long num) -> BigInteger
    {
        return BigInteger(num);
    }
}
