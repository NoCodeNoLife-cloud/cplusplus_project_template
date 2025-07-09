#include <type/base_type/BigInteger.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(BigIntegerTest, DivisionByZeroThrowsException)
    {
        const coco::BigInteger a("10");
        const coco::BigInteger b("0");
        EXPECT_THROW({ a / b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, ModuloByZeroThrowsException)
    {
        const coco::BigInteger a("5");
        const coco::BigInteger b("0");
        EXPECT_THROW({ a % b; }, std::invalid_argument);
    }

    TEST(BigIntegerTest, EqualityOperatorTrue)
    {
        const coco::BigInteger a("123");
        const coco::BigInteger b("123");
        EXPECT_TRUE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, EqualityOperatorFalse)
    {
        const coco::BigInteger a("123");
        const coco::BigInteger b("456");
        EXPECT_FALSE(std::is_eq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorTrue)
    {
        const coco::BigInteger a("789");
        const coco::BigInteger b("987");
        EXPECT_TRUE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, InequalityOperatorFalse)
    {
        const coco::BigInteger a("555");
        const coco::BigInteger b("555");
        EXPECT_FALSE(std::is_neq(a <=> b));
    }

    TEST(BigIntegerTest, LessThanOperatorTrue)
    {
        const coco::BigInteger a("100");
        const coco::BigInteger b("200");
        EXPECT_TRUE(a < b);
    }

    TEST(BigIntegerTest, LessThanOperatorFalse)
    {
        const coco::BigInteger a("500");
        const coco::BigInteger b("300");
        EXPECT_FALSE(a < b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual)
    {
        const coco::BigInteger a("42");
        const coco::BigInteger b("42");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess)
    {
        const coco::BigInteger a("-5");
        const coco::BigInteger b("5");
        EXPECT_TRUE(a <= b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorTrue)
    {
        const coco::BigInteger a("999");
        const coco::BigInteger b("123");
        EXPECT_TRUE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOperatorFalse)
    {
        const coco::BigInteger a("123");
        const coco::BigInteger b("999");
        EXPECT_FALSE(a > b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual)
    {
        const coco::BigInteger a("0");
        const coco::BigInteger b("0");
        EXPECT_TRUE(a >= b);
    }

    TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater)
    {
        const coco::BigInteger a("100");
        const coco::BigInteger b("-100");
        EXPECT_TRUE(a >= b);
    }
}
