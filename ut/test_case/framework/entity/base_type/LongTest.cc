#include <limits>
#include <stdexcept>
#include <type/base_type/Long.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(LongTest, ConstructorInitializesValue)
    {
        const coco::Long l1;
        EXPECT_EQ(static_cast<int64_t>(l1), 0);
        const coco::Long l2(1234567890123456789LL);
        EXPECT_EQ(l2.longValue(), 1234567890123456789LL);
    }

    TEST(LongTest, ConversionOperatorsReturnCorrectValue)
    {
        const coco::Long l(0x7FFFFFFFFFFFFFFFLL);
        EXPECT_EQ(static_cast<int64_t>(l), 0x7FFFFFFFFFFFFFFFLL);
        EXPECT_EQ(l.longValue(), 0x7FFFFFFFFFFFFFFFLL);
    }

    TEST(LongTest, ArithmeticOperations)
    {
        const coco::Long a(100), b(200);
        EXPECT_EQ(static_cast<int64_t>(a + b), 300);
        EXPECT_EQ(static_cast<int64_t>(b - a), 100);
        EXPECT_EQ(static_cast<int64_t>(a * b), 20000);
        EXPECT_EQ(static_cast<int64_t>(b / a), 2);
        EXPECT_EQ(static_cast<int64_t>(b % a), 0);
    }

    TEST(LongTest, ParseValidStrings)
    {
        EXPECT_EQ(coco::Long::parseLong("12345").longValue(), 12345LL);
        EXPECT_EQ(coco::Long::parseLong("-9876543210").longValue(), -9876543210LL);
        EXPECT_EQ(coco::Long::parseLong("26").longValue(), 26LL);
    }

    TEST(LongTest, ParseInvalidStringsThrow)
    {
        EXPECT_THROW(coco::Long::parseLong("123abc"), std::invalid_argument);
        EXPECT_THROW(coco::Long::parseLong(""), std::invalid_argument);
    }

    TEST(LongTest, ComparisonOperators)
    {
        const coco::Long a(100), b(200), c(100);
        EXPECT_TRUE(a == c);
        EXPECT_TRUE(a != b);
        EXPECT_TRUE(a < b);
        EXPECT_TRUE(b > a);
    }

    TEST(LongTest, DivisionByZeroThrows)
    {
        coco::Long a(100);
        coco::Long zero(0);
        EXPECT_THROW(a / zero, std::overflow_error);
        EXPECT_THROW(a % zero, std::overflow_error);
    }

    TEST(LongTest, HashCodeConsistency)
    {
        const coco::Long a(123456789LL);
        const coco::Long b(123456789LL);
        EXPECT_EQ(a.hashCode(), b.hashCode());
    }

    TEST(LongTest, ToStringConversion)
    {
        const coco::Long l(1234567890123456789LL);
        EXPECT_EQ(l.toString(), "class coco::Long{1234567890123456789}");
    }
}
