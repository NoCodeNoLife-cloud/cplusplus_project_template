#include <limits>
#include <stdexcept>
#include <entity/base_type/Long.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(LongTest, ConstructorInitializesValueCorrectly) {
    const common::Long longObj(12345);
    EXPECT_EQ(longObj.longValue(), 12345);
  }

  TEST(LongTest, ExplicitConversionToInt64ReturnsCorrectValue) {
    const common::Long longObj(-5678);
    EXPECT_EQ(static_cast<int64_t>(longObj), -5678);
  }

  TEST(LongTest, ToStringReturnsCorrectStringRepresentation) {
    const common::Long longObj(87654321);
    EXPECT_EQ(longObj.toString(), "87654321");
  }

  TEST(LongTest, ToStringWithNegativeValueReturnsCorrectString) {
    const common::Long longObj(-4444);
    EXPECT_EQ(longObj.toString(), "-4444");
  }

  TEST(LongTest, LongValueReturnsSameAsConstructorArgument) {
    constexpr int64_t value = 999;
    const common::Long longObj(value);
    EXPECT_EQ(longObj.longValue(), value);
  }

  TEST(LongTest, EqualsReturnsTrueWhenValuesAreEqual) {
    const common::Long a(100);
    const common::Long b(100);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(LongTest, EqualsReturnsFalseWhenValuesAreDifferent) {
    const common::Long a(100);
    const common::Long b(200);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(LongTest, EqualityOperatorComparesValuesCorrectly) {
    const common::Long a(50);
    const common::Long b(50);
    const common::Long c(60);
    EXPECT_TRUE(std::is_eq(a <=> b));
    EXPECT_FALSE(std::is_eq(a <=> c));
  }

  TEST(LongTest, InequalityOperatorComparesValuesCorrectly) {
    const common::Long a(50);
    const common::Long b(50);
    const common::Long c(60);
    EXPECT_FALSE(std::is_neq(a <=> b));
    EXPECT_TRUE(std::is_neq(a <=> c));
  }

  TEST(LongTest, LessThanOperatorWorksForSmallerValue) {
    const common::Long a(30);
    const common::Long b(40);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
  }

  TEST(LongTest, GreaterThanOperatorWorksForLargerValue) {
    const common::Long a(50);
    const common::Long b(30);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
  }

  TEST(LongTest, LessThanOrEqualOperatorReturnsTrueForEqualValues) {
    const common::Long a(70);
    const common::Long b(70);
    EXPECT_TRUE(a <= b);
  }

  TEST(LongTest, GreaterThanOrEqualOperatorReturnsTrueForEqualValues) {
    const common::Long a(80);
    const common::Long b(80);
    EXPECT_TRUE(a >= b);
  }

  TEST(LongTest, CompareToReturnsZeroForEqualValues) {
    const common::Long a(123);
    const common::Long b(123);
    EXPECT_EQ(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsPositiveWhenLeftIsGreater) {
    const common::Long a(200);
    const common::Long b(100);
    EXPECT_GT(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsNegativeWhenLeftIsLess) {
    const common::Long a(50);
    const common::Long b(100);
    EXPECT_LT(a.compareTo(b), 0);
  }

  TEST(LongTest, AdditionOperatorAddsValuesCorrectly) {
    const common::Long a(10);
    const common::Long b(20);
    const common::Long result = a + b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, SubtractionOperatorSubtractsValuesCorrectly) {
    const common::Long a(50);
    const common::Long b(20);
    const common::Long result = a - b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, MultiplicationOperatorMultipliesValuesCorrectly) {
    const common::Long a(7);
    const common::Long b(6);
    const common::Long result = a * b;
    EXPECT_EQ(result.longValue(), 42);
  }

  TEST(LongTest, DivisionOperatorDividesValuesCorrectly) {
    const common::Long a(100);
    const common::Long b(25);
    const common::Long result = a / b;
    EXPECT_EQ(result.longValue(), 4);
  }

  TEST(LongTest, DivisionByZeroThrowsOverflowError) {
    const common::Long a(10);
    const common::Long b(0);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(LongTest, ModuloOperatorCalculatesCorrectlyForNonZeroDivisor) {
    const common::Long a(10);
    const common::Long b(3);
    const common::Long result = a % b;
    EXPECT_EQ(result.longValue(), 1);
  }

  TEST(LongTest, ModuloByZeroThrowsOverflowError) {
    const common::Long a(10);
    const common::Long b(0);
    EXPECT_THROW(a % b, std::overflow_error);
  }

  TEST(LongTest, ParseLongConvertsValidDecimalStringToLong) {
    const std::string str = "123456789";
    const common::Long result = common::Long::parseLong(str);
    EXPECT_EQ(result.longValue(), 123456789);
  }

  TEST(LongTest, ParseLongConvertsNegativeStringToLong) {
    const std::string str = "-987654321";
    const common::Long result = common::Long::parseLong(str);
    EXPECT_EQ(result.longValue(), -987654321);
  }

  TEST(LongTest, ParseLongWithInvalidArgumentThrowsInvalidArgument) {
    const std::string str = "abc";
    EXPECT_THROW(common::Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithEmptyStringThrowsInvalidArgument) {
    const std::string str;
    EXPECT_THROW(common::Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "9223372036854775808";
    EXPECT_THROW(common::Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ParseLongWithNegativeOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "-9223372036854775809";
    EXPECT_THROW(common::Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ConstructorWithMaxInt64Value) {
    constexpr int64_t maxValue = std::numeric_limits<int64_t>::max();
    const common::Long longObj(maxValue);
    EXPECT_EQ(longObj.longValue(), maxValue);
  }

  TEST(LongTest, ConstructorWithMinInt64Value) {
    constexpr int64_t minValue = std::numeric_limits<int64_t>::min();
    const common::Long longObj(minValue);
    EXPECT_EQ(longObj.longValue(), minValue);
  }
}
