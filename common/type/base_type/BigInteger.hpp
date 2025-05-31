#pragma once
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

namespace common
{
    class BigInteger
    {
    public:
        BigInteger();
        explicit BigInteger(const std::string& str);
        explicit BigInteger(int64_t num);
        auto operator+(const BigInteger& other) const -> BigInteger;
        auto operator-(const BigInteger& other) const -> BigInteger;
        auto operator*(const BigInteger& other) const -> BigInteger;
        auto operator/(const BigInteger& other) const -> BigInteger;
        auto operator%(const BigInteger& other) const -> BigInteger;
        auto operator<=>(const BigInteger& other) const -> std::partial_ordering;
        static auto fromString(const std::string& str) -> BigInteger;
        static auto fromInt(int64_t num) -> BigInteger;

    private:
        boost::multiprecision::cpp_int value_;
    };
}
