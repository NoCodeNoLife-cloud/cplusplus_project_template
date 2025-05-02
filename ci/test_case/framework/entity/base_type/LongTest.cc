#include <limits>
#include <stdexcept>
#include <entity/base_type/Long.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(LongTest, ConstructorInitializesValueCorrectly) {
    const framework::entity::base_type::Long longObj(12345);
    EXPECT_EQ(longObj.longValue(), 12345);
  }

  TEST(LongTest, ExplicitConversionToInt64ReturnsCorrectValue) {
    const framework::entity::base_type::Long longObj(-5678);
    EXPECT_EQ(static_cast<int64_t>(longObj), -5678);
  }

  TEST(LongTest, ToStringReturnsCorrectStringRepresentation) {
    const framework::entity::base_type::Long longObj(87654321);
    EXPECT_EQ(longObj.toString(), "87654321");
  }

  TEST(LongTest, ToStringWithNegativeValueReturnsCorrectString) {
    const framework::entity::base_type::Long longObj(-4444);
    EXPECT_EQ(longObj.toString(), "-4444");
  }

  TEST(LongTest, LongValueReturnsSameAsConstructorArgument) {
    constexpr int64_t value = 999;
    const framework::entity::base_type::Long longObj(value);
    EXPECT_EQ(longObj.longValue(), value);
  }

  TEST(LongTest, EqualsReturnsTrueWhenValuesAreEqual) {
    const framework::entity::base_type::Long a(100);
    const framework::entity::base_type::Long b(100);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(LongTest, EqualsReturnsFalseWhenValuesAreDifferent) {
    const framework::entity::base_type::Long a(100);
    const framework::entity::base_type::Long b(200);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(LongTest, EqualityOperatorComparesValuesCorrectly) {
    const framework::entity::base_type::Long a(50);
    const framework::entity::base_type::Long b(50);
    const framework::entity::base_type::Long c(60);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
  }

  TEST(LongTest, InequalityOperatorComparesValuesCorrectly) {
    const framework::entity::base_type::Long a(50);
    const framework::entity::base_type::Long b(50);
    const framework::entity::base_type::Long c(60);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  }

  TEST(LongTest, LessThanOperatorWorksForSmallerValue) {
    const framework::entity::base_type::Long a(30);
    const framework::entity::base_type::Long b(40);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
  }

  TEST(LongTest, GreaterThanOperatorWorksForLargerValue) {
    const framework::entity::base_type::Long a(50);
    const framework::entity::base_type::Long b(30);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
  }

  TEST(LongTest, LessThanOrEqualOperatorReturnsTrueForEqualValues) {
    const framework::entity::base_type::Long a(70);
    const framework::entity::base_type::Long b(70);
    EXPECT_TRUE(a <= b);
  }

  TEST(LongTest, GreaterThanOrEqualOperatorReturnsTrueForEqualValues) {
    const framework::entity::base_type::Long a(80);
    const framework::entity::base_type::Long b(80);
    EXPECT_TRUE(a >= b);
  }

  TEST(LongTest, CompareToReturnsZeroForEqualValues) {
    const framework::entity::base_type::Long a(123);
    const framework::entity::base_type::Long b(123);
    EXPECT_EQ(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsPositiveWhenLeftIsGreater) {
    const framework::entity::base_type::Long a(200);
    const framework::entity::base_type::Long b(100);
    EXPECT_GT(a.compareTo(b), 0);
  }

  TEST(LongTest, CompareToReturnsNegativeWhenLeftIsLess) {
    const framework::entity::base_type::Long a(50);
    const framework::entity::base_type::Long b(100);
    EXPECT_LT(a.compareTo(b), 0);
  }

  TEST(LongTest, AdditionOperatorAddsValuesCorrectly) {
    const framework::entity::base_type::Long a(10);
    const framework::entity::base_type::Long b(20);
    const framework::entity::base_type::Long result = a + b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, SubtractionOperatorSubtractsValuesCorrectly) {
    const framework::entity::base_type::Long a(50);
    const framework::entity::base_type::Long b(20);
    const framework::entity::base_type::Long result = a - b;
    EXPECT_EQ(result.longValue(), 30);
  }

  TEST(LongTest, MultiplicationOperatorMultipliesValuesCorrectly) {
    const framework::entity::base_type::Long a(7);
    const framework::entity::base_type::Long b(6);
    const framework::entity::base_type::Long result = a * b;
    EXPECT_EQ(result.longValue(), 42);
  }

  TEST(LongTest, DivisionOperatorDividesValuesCorrectly) {
    const framework::entity::base_type::Long a(100);
    const framework::entity::base_type::Long b(25);
    const framework::entity::base_type::Long result = a / b;
    EXPECT_EQ(result.longValue(), 4);
  }

  TEST(LongTest, DivisionByZeroThrowsOverflowError) {
    const framework::entity::base_type::Long a(10);
    const framework::entity::base_type::Long b(0);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(LongTest, ModuloOperatorCalculatesCorrectlyForNonZeroDivisor) {
    const framework::entity::base_type::Long a(10);
    const framework::entity::base_type::Long b(3);
    const framework::entity::base_type::Long result = a % b;
    EXPECT_EQ(result.longValue(), 1);
  }

  TEST(LongTest, ModuloByZeroThrowsOverflowError) {
    const framework::entity::base_type::Long a(10);
    const framework::entity::base_type::Long b(0);
    EXPECT_THROW(a % b, std::overflow_error);
  }

  TEST(LongTest, ParseLongConvertsValidDecimalStringToLong) {
    const std::string str = "123456789";
    const framework::entity::base_type::Long result = framework::entity::base_type::Long::parseLong(str);
    EXPECT_EQ(result.longValue(), 123456789);
  }

  TEST(LongTest, ParseLongConvertsNegativeStringToLong) {
    const std::string str = "-987654321";
    const framework::entity::base_type::Long result = framework::entity::base_type::Long::parseLong(str);
    EXPECT_EQ(result.longValue(), -987654321);
  }

  TEST(LongTest, ParseLongWithInvalidArgumentThrowsInvalidArgument) {
    const std::string str = "abc";
    EXPECT_THROW(framework::entity::base_type::Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithEmptyStringThrowsInvalidArgument) {
    const std::string str;
    EXPECT_THROW(framework::entity::base_type::Long::parseLong(str), std::invalid_argument);
  }

  TEST(LongTest, ParseLongWithOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "9223372036854775808";
    EXPECT_THROW(framework::entity::base_type::Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ParseLongWithNegativeOutOfRangeValueThrowsOutOfRange) {
    const std::string str = "-9223372036854775809";
    EXPECT_THROW(framework::entity::base_type::Long::parseLong(str), std::out_of_range);
  }

  TEST(LongTest, ConstructorWithMaxInt64Value) {
    constexpr int64_t maxValue = std::numeric_limits<int64_t>::max();
    const framework::entity::base_type::Long longObj(maxValue);
    EXPECT_EQ(longObj.longValue(), maxValue);
  }

  TEST(LongTest, ConstructorWithMinInt64Value) {
    constexpr int64_t minValue = std::numeric_limits<int64_t>::min();
    const framework::entity::base_type::Long longObj(minValue);
    EXPECT_EQ(longObj.longValue(), minValue);
  }
} // namespace gtest_case
