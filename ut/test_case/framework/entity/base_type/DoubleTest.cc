#include <stdexcept>
#include <string>
#include <gtest/gtest.h>

#include "type/base_type/Double.hpp"

namespace gtest_case
{
    TEST(DoubleTest, ConstructorTest)
    {
        const coco::Double d1(2.5);
        EXPECT_EQ(d1.doubleValue(), 2.5);
        const coco::Double d2(coco::Double::POSITIVE_INFINITY);
        EXPECT_EQ(d2.doubleValue(), std::numeric_limits<double>::infinity());
        const coco::Double d3(coco::Double::NEGATIVE_INFINITY);
        EXPECT_EQ(d3.doubleValue(), -std::numeric_limits<double>::infinity());
        const coco::Double d4(coco::Double::NaN);
        EXPECT_TRUE(std::isnan(d4.doubleValue()));
    }

    TEST(DoubleTest, CopyConstructorTest)
    {
        const coco::Double d1(3.14);
        const coco::Double d2(d1);
        EXPECT_EQ(d2.doubleValue(), 3.14);
    }

    TEST(DoubleTest, MoveConstructorTest)
    {
        coco::Double d1(42.0);
        const coco::Double d2(std::move(d1));
        EXPECT_EQ(d2.doubleValue(), 42.0);
    }

    TEST(DoubleTest, AssignmentOperatorTest)
    {
        coco::Double d1(1.0);
        coco::Double d2(2.0);
        d2 = d1;
        EXPECT_EQ(d2.doubleValue(), 1.0);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        d1 = d1;
        EXPECT_EQ(d1.doubleValue(), 1.0);
    }

    TEST(DoubleTest, ComparisonOperatorsTest)
    {
        const coco::Double d1(5.0);
        const coco::Double d2(5.0);
        const coco::Double d3(6.0);
        EXPECT_TRUE(d1 == d2);
        EXPECT_FALSE(d1 == d3);
        EXPECT_TRUE(d1 < d3);
        EXPECT_FALSE(d3 < d1);
        const coco::Double d4(coco::Double::NaN);
        EXPECT_FALSE(d4 == d4);
        EXPECT_FALSE(d4 < d4);
    }

    TEST(DoubleTest, ArithmeticOperatorsTest)
    {
        const coco::Double d1(4.0);
        const coco::Double d2(2.0);
        EXPECT_EQ((d1 + d2).doubleValue(), 6.0);
        EXPECT_EQ((d1 - d2).doubleValue(), 2.0);
        EXPECT_EQ((d1 * d2).doubleValue(), 8.0);
        EXPECT_EQ((d1 / d2).doubleValue(), 2.0);
        const coco::Double zero(0.0);
        EXPECT_THROW(d1 / zero, std::overflow_error);
        const coco::Double nan(coco::Double::NaN);
        EXPECT_TRUE(std::isnan((d1 + nan).doubleValue()));
    }

    TEST(DoubleTest, ParseDoubleTest)
    {
        EXPECT_EQ(coco::Double::parseDouble("123").doubleValue(), 123.0);
        EXPECT_EQ(coco::Double::parseDouble("123.45").doubleValue(), 123.45);
        EXPECT_EQ(coco::Double::parseDouble("-123").doubleValue(), -123.0);
        EXPECT_EQ(coco::Double::parseDouble("inf").doubleValue(), std::numeric_limits<double>::infinity());
        EXPECT_EQ(coco::Double::parseDouble("-inf").doubleValue(), -std::numeric_limits<double>::infinity());
        EXPECT_TRUE(std::isnan(coco::Double::parseDouble("nan").doubleValue()));
        EXPECT_THROW(coco::Double::parseDouble("abc"), std::invalid_argument);
        EXPECT_THROW(coco::Double::parseDouble("123abc"), std::invalid_argument);
        EXPECT_THROW(coco::Double::parseDouble("1e10000"), std::out_of_range);
    }

    TEST(DoubleTest, ToStringTest)
    {
        const coco::Double d1(3.14);
        EXPECT_EQ(d1.toString(), "class coco::Double{3.14}");
        const coco::Double d2(coco::Double::POSITIVE_INFINITY);
        EXPECT_EQ(d2.toString(), "class coco::Double{inf}");
        const coco::Double d3(coco::Double::NaN);
        EXPECT_EQ(d3.toString(), "class coco::Double{nan}");
    }

    TEST(DoubleTest, HashCodeTest)
    {
        const coco::Double d1(1.0);
        const coco::Double d2(1.0);
        const coco::Double d3(2.0);
        EXPECT_EQ(d1.hashCode(), d2.hashCode());
        EXPECT_NE(d1.hashCode(), d3.hashCode());
    }
}
