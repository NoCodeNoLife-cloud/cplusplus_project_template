#include <gtest/gtest.h>

#include "type/base_type/BigInteger.hpp"

namespace gtest_case
{
    TEST(BigIntegerTest, DivisionByZeroThrowsException)
    {
        const fox::BigInteger a("10");
        const fox::BigInteger b("0");
        EXPECT_THROW({ a / b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, ModuloByZeroThrowsException)
    {
        const fox::BigInteger a("5");
        const fox::BigInteger b("0");
        EXPECT_THROW({ a % b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, EqualityOperatorTrue)
    {
        const fox::BigInteger a("123");
        const fox::BigInteger b("123");
        EXPECT_TRUE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, EqualityOperatorFalse)
    {
        const fox::BigInteger a("123");
        const fox::BigInteger b("456");
        EXPECT_FALSE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorTrue)
    {
        const fox::BigInteger a("789");
        const fox::BigInteger b("987");
        EXPECT_TRUE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorFalse)
    {
        const fox::BigInteger a("555");
        const fox::BigInteger b("555");
        EXPECT_FALSE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, LessThanOperatorTrue)
    {
        const fox::BigInteger a("100");
        const fox::BigInteger b("200");
        EXPECT_TRUE(a < b);
    }

    TEST(BigIntegerTest, LessThanOperatorFalse)
    {
        const fox::BigInteger a("500");
        const fox::BigInteger b("300");
        EXPECT_FALSE(a < b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual)
    {
        const fox::BigInteger a("42");
        const fox::BigInteger b("42");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess)
    {
        const fox::BigInteger a("-5");
        const fox::BigInteger b("5");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorTrue)
    {
        const fox::BigInteger a("999");
        const fox::BigInteger b("123");
        EXPECT_TRUE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorFalse)
    {
        const fox::BigInteger a("123");
        const fox::BigInteger b("999");
        EXPECT_FALSE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual)
    {
        const fox::BigInteger a("0");
        const fox::BigInteger b("0");
        EXPECT_TRUE(a >= b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater)
    {
        const fox::BigInteger a("100");
        const fox::BigInteger b("-100");
        EXPECT_TRUE(a >= b);
    }
} // namespace gtest_case
