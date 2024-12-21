#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <string>

namespace framework::entity::base_type
{

class BigInteger
{
  public:
    BigInteger();

    explicit BigInteger(const std::string &str);

    explicit BigInteger(int64_t num);

    auto operator+(const BigInteger &other) const -> BigInteger;

    auto operator-(const BigInteger &other) const -> BigInteger;

    auto operator*(const BigInteger &other) const -> BigInteger;

    auto operator/(const BigInteger &other) const -> BigInteger;

    auto operator%(const BigInteger &other) const -> BigInteger;

    auto operator==(const BigInteger &other) const -> bool;

    auto operator!=(const BigInteger &other) const -> bool;

    auto operator<(const BigInteger &other) const -> bool;

    auto operator<=(const BigInteger &other) const -> bool;

    auto operator>(const BigInteger &other) const -> bool;

    auto operator>=(const BigInteger &other) const -> bool;

    [[nodiscard]] auto toString() const -> std::string;

    static auto fromString(const std::string &str) -> BigInteger;

    static auto fromInt(int64_t num) -> BigInteger;

  private:
    boost::multiprecision::cpp_int value_;
};

} // namespace framework::entity::base_type
