#include <gtest/gtest.h>

#include "type/base_type/BigInteger.hpp"

namespace gtest_case
{
    TEST(BigIntegerTest, DivisionByZeroThrowsException)
    {
        const common::BigInteger a("10");
        const common::BigInteger b("0");
        EXPECT_THROW({ a / b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, ModuloByZeroThrowsException)
    {
        const common::BigInteger a("5");
        const common::BigInteger b("0");
        EXPECT_THROW({ a % b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, EqualityOperatorTrue)
    {
        const common::BigInteger a("123");
        const common::BigInteger b("123");
        EXPECT_TRUE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, EqualityOperatorFalse)
    {
        const common::BigInteger a("123");
        const common::BigInteger b("456");
        EXPECT_FALSE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorTrue)
    {
        const common::BigInteger a("789");
        const common::BigInteger b("987");
        EXPECT_TRUE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorFalse)
    {
        const common::BigInteger a("555");
        const common::BigInteger b("555");
        EXPECT_FALSE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, LessThanOperatorTrue)
    {
        const common::BigInteger a("100");
        const common::BigInteger b("200");
        EXPECT_TRUE(a < b);
    }

    TEST(BigIntegerTest, LessThanOperatorFalse)
    {
        const common::BigInteger a("500");
        const common::BigInteger b("300");
        EXPECT_FALSE(a < b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual)
    {
        const common::BigInteger a("42");
        const common::BigInteger b("42");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess)
    {
        const common::BigInteger a("-5");
        const common::BigInteger b("5");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorTrue)
    {
        const common::BigInteger a("999");
        const common::BigInteger b("123");
        EXPECT_TRUE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorFalse)
    {
        const common::BigInteger a("123");
        const common::BigInteger b("999");
        EXPECT_FALSE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual)
    {
        const common::BigInteger a("0");
        const common::BigInteger b("0");
        EXPECT_TRUE(a >= b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater)
    {
        const common::BigInteger a("100");
        const common::BigInteger b("-100");
        EXPECT_TRUE(a >= b);
    }
}
