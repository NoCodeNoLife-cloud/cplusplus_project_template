#include <limits>
#include <stdexcept>
#include <entity/base_type/Long.hpp>
#include <gtest/gtest.h>
using framework::entity::base_type::Long;

namespace gtest_case {
  TEST(LongTest, ConstructorInitializesValueCorrectly) {
    const Long longObj(12345);
    EXPECT_EQ(longObj.longValue(), 12345);
  }

  TEST(LongTest, ExplicitConversionToInt64ReturnsCorrectValue) {
    const Long longObj(-5678);
    EXPECT_EQ(static_cast<int64_t>(longObj), -5678);
  }

  TEST(LongTest, ToStringReturnsCorrectStringRepresentation) {
    const Long longObj(87654321);
    EXPECT_EQ(longObj.toString(), "87654321");
  }

  TEST(LongTest, ToStringWithNegativeValueReturnsCorrectString) {
    const Long longObj(-4444);
    EXPECT_EQ(longObj.toString(), "-4444");
  }

  TEST(LongTest, LongValueReturnsSameAsConstructorArgument) {
    constexpr int64_t value = 999;
    const Long longObj(value);
    EXPECT_EQ(longObj.longValue(), value);
  }

  TEST(LongTest, EqualsReturnsTrueWhenValuesAreEqual) {
    const Long a(100);
    const Long b(100);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(LongTest, EqualsReturnsFalseWhenValuesAreDifferent) {
    const Long a(100);
    const Long b(200);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(LongTest, EqualityOperatorComparesValuesCorrectly) {
    const Long a(50);
    const Long b(50);
    const Long c(60);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
  }

  TEST(LongTest, InequalityOperatorComparesValuesCorrectly) {
    const Long a(50);
    const Long b(50);
    const Long c(60);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  }

  TEST(LongTest, LessThanOperatorWorksForSmallerValue) {
    const Long a(30);
    const Long b(40);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
  }

  TEST(LongTest, GreaterThanOperatorWorksForLargerValue) {
    const Long a(50);
    const Long b(30);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
  }

  TEST(LongTest, LessThanOrEqualOperatorReturnsTrueForEqualValues) {
    const Long a(70);
    const Long b(70);
    EXPECT_TRUE(a <= b);
  }

  TEST(LongTest, GreaterThanOrEqualOperatorReturnsTrueForEqualValues) {
    const Long a(80);
    const Long b(80);
    EXPECT_TRUE(a >= b);
  }

  TEST(LongTest, CompareToReturnsZeroForEqualValues) {
    const Long a(123);
    const Long b(123);
    EXPECT_EQ(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsPositiveWhenLeftIsGreater) {
    const Long a(200);
    const Long b(100);
    EXPECT_GT(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsNegativeWhenLeftIsLess) {
    const Long a(50);
    const Long b(100);
    EXPECT_LT(a.compareTo(b), 0);
  }

  TEST(LongTest, AdditionOperatorAddsValuesCorrectly) {
    const Long a(10);
    const Long b(20);
    const Long result = a + b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, SubtractionOperatorSubtractsValuesCorrectly) {
    const Long a(50);
    const Long b(20);
    const Long result = a - b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, MultiplicationOperatorMultipliesValuesCorrectly) {
    const Long a(7);
    const Long b(6);
    const Long result = a * b;
    EXPECT_EQ(result.longValue(), 42);
  }

  TEST(LongTest, DivisionOperatorDividesValuesCorrectly) {
    const Long a(100);
    const Long b(25);
    const Long result = a / b;
    EXPECT_EQ(result.longValue(), 4);
  }

  TEST(LongTest, DivisionByZeroThrowsOverflowError) {
    const Long a(10);
    const Long b(0);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(LongTest, ModuloOperatorCalculatesCorrectlyForNonZeroDivisor) {
    const Long a(10);
    const Long b(3);
    const Long result = a % b;
    EXPECT_EQ(result.longValue(), 1);
  }

  TEST(LongTest, ModuloByZeroThrowsOverflowError) {
    const Long a(10);
    const Long b(0);
    EXPECT_THROW(a % b, std::overflow_error);
  }

  TEST(LongTest, ParseLongConvertsValidDecimalStringToLong) {
    const std::string str = "123456789";
    const Long result = Long::parseLong(str);
    EXPECT_EQ(result.longValue(), 123456789);
  }

  TEST(LongTest, ParseLongConvertsNegativeStringToLong) {
    const std::string str = "-987654321";
    const Long result = Long::parseLong(str);
    EXPECT_EQ(result.longValue(), -987654321);
  }

  TEST(LongTest, ParseLongWithInvalidArgumentThrowsInvalidArgument) {
    const std::string str = "abc";
    EXPECT_THROW(Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithEmptyStringThrowsInvalidArgument) {
    const std::string str;
    EXPECT_THROW(Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "9223372036854775808";
    EXPECT_THROW(Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ParseLongWithNegativeOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "-9223372036854775809";
    EXPECT_THROW(Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ConstructorWithMaxInt64Value) {
    constexpr int64_t maxValue = std::numeric_limits<int64_t>::max();
    const Long longObj(maxValue);
    EXPECT_EQ(longObj.longValue(), maxValue);
  }

  TEST(LongTest, ConstructorWithMinInt64Value) {
    constexpr int64_t minValue = std::numeric_limits<int64_t>::min();
    const Long longObj(minValue);
    EXPECT_EQ(longObj.longValue(), minValue);
  }
}
