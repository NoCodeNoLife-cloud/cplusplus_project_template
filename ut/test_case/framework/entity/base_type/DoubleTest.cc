#include <stdexcept>
#include <string>
#include <entity/base_type/Double.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(DoubleTest, ConstructorTest) {
    common::Double d1(2.5);
    EXPECT_EQ(d1.doubleValue(), 2.5);
    common::Double d2(common::Double::POSITIVE_INFINITY);
    EXPECT_EQ(d2.doubleValue(), std::numeric_limits<double>::infinity());
    common::Double d3(common::Double::NEGATIVE_INFINITY);
    EXPECT_EQ(d3.doubleValue(), -std::numeric_limits<double>::infinity());
    common::Double d4(common::Double::NaN);
    EXPECT_TRUE(std::isnan(d4.doubleValue()));
  }

  TEST(DoubleTest, CopyConstructorTest) {
    common::Double d1(3.14);
    common::Double d2(d1);
    EXPECT_EQ(d2.doubleValue(), 3.14);
  }

  TEST(DoubleTest, MoveConstructorTest) {
    common::Double d1(42.0);
    common::Double d2(std::move(d1));
    EXPECT_EQ(d2.doubleValue(), 42.0);
  }

  TEST(DoubleTest, AssignmentOperatorTest) {
    common::Double d1(1.0);
    common::Double d2(2.0);
    d2 = d1;
    EXPECT_EQ(d2.doubleValue(), 1.0);
    d1 = d1;
    EXPECT_EQ(d1.doubleValue(), 1.0);
  }

  TEST(DoubleTest, ComparisonOperatorsTest) {
    common::Double d1(5.0);
    common::Double d2(5.0);
    common::Double d3(6.0);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d1 < d3);
    EXPECT_FALSE(d3 < d1);
    common::Double d4(common::Double::NaN);
    EXPECT_FALSE(d4 == d4);
    EXPECT_FALSE(d4 < d4);
  }

  TEST(DoubleTest, ArithmeticOperatorsTest) {
    common::Double d1(4.0);
    common::Double d2(2.0);
    EXPECT_EQ((d1 + d2).doubleValue(), 6.0);
    EXPECT_EQ((d1 - d2).doubleValue(), 2.0);
    EXPECT_EQ((d1 * d2).doubleValue(), 8.0);
    EXPECT_EQ((d1 / d2).doubleValue(), 2.0);
    common::Double zero(0.0);
    EXPECT_THROW(d1 / zero, std::overflow_error);
    common::Double nan(common::Double::NaN);
    EXPECT_TRUE(std::isnan((d1 + nan).doubleValue()));
  }

  TEST(DoubleTest, ParseDoubleTest) {
    EXPECT_EQ(common::Double::parseDouble("123").doubleValue(), 123.0);
    EXPECT_EQ(common::Double::parseDouble("123.45").doubleValue(), 123.45);
    EXPECT_EQ(common::Double::parseDouble("-123").doubleValue(), -123.0);
    EXPECT_EQ(common::Double::parseDouble("inf").doubleValue(), std::numeric_limits<double>::infinity());
    EXPECT_EQ(common::Double::parseDouble("-inf").doubleValue(), -std::numeric_limits<double>::infinity());
    EXPECT_TRUE(std::isnan(common::Double::parseDouble("nan").doubleValue()));
    EXPECT_THROW(common::Double::parseDouble("abc"), std::invalid_argument);
    EXPECT_THROW(common::Double::parseDouble("123abc"), std::invalid_argument);
    EXPECT_THROW(common::Double::parseDouble("1e10000"), std::out_of_range);
  }

  TEST(DoubleTest, ToStringTest) {
    common::Double d1(3.14);
    EXPECT_EQ(d1.toString(), "class common::Double{3.14}");
    common::Double d2(common::Double::POSITIVE_INFINITY);
    EXPECT_EQ(d2.toString(), "class common::Double{inf}");
    common::Double d3(common::Double::NaN);
    EXPECT_EQ(d3.toString(), "class common::Double{nan}");
  }

  TEST(DoubleTest, HashCodeTest) {
    common::Double d1(1.0);
    common::Double d2(1.0);
    common::Double d3(2.0);
    EXPECT_EQ(d1.hashCode(), d2.hashCode());
    EXPECT_NE(d1.hashCode(), d3.hashCode());
  }
}
