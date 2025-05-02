#include <stdexcept>
#include <string>
#include <entity/base_type/Double.hpp>
#include <gtest/gtest.h>
using framework::entity::base_type::Double;

namespace gtest_case {
  TEST(DoubleTest, ConstructorInitializesValueCorrectly) {
    constexpr double value = 42.0;
    const Double d(value);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), value);
  }

  TEST(DoubleTest, ConversionOperatorReturnsStoredValue) {
    Double d(3.14);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), 3.14);
  }

  TEST(DoubleTest, ToStringReturnsCorrectFormat) {
    const Double d(3.14);
    EXPECT_EQ(d.toString(), "3.14");
    const Double zero(0.0);
    EXPECT_EQ(zero.toString(), "0");
    const Double negative(-42.5);
    EXPECT_EQ(negative.toString(), "-42.5");
  }

  TEST(DoubleTest, EqualsReturnsTrueForEqualValues) {
    const Double a(5.0);
    const Double b(5.0);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(DoubleTest, EqualsReturnsFalseForDifferentValues) {
    const Double a(5.0);
    const Double b(6.0);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(DoubleTest, CompareToReturnsZeroWhenEqual) {
    const Double a(5.0);
    EXPECT_EQ(a.compareTo(a), 0);
  }

  TEST(DoubleTest, CompareToReturnsPositiveWhenGreater) {
    const Double a(6.0);
    const Double b(5.0);
    EXPECT_EQ(a.compareTo(b), 1);
  }

  TEST(DoubleTest, CompareToReturnsNegativeWhenLess) {
    const Double a(5.0);
    const Double b(6.0);
    EXPECT_EQ(a.compareTo(b), -1);
  }

  TEST(DoubleTest, ParseDoubleConvertsValidString) {
    const std::string str = "123.45";
    const Double d = Double::parseDouble(str);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), 123.45);
  }

  TEST(DoubleTest, ParseDoubleThrowsInvalidArgumentForInvalidInput) {
    const std::string invalid = "abc";
    EXPECT_THROW(Double::parseDouble(invalid), std::invalid_argument);
  }

  TEST(DoubleTest, ParseDoubleThrowsOutOfRangeForLargeValue) {
    const std::string huge = "1e999999999";
    EXPECT_THROW(Double::parseDouble(huge), std::out_of_range);
  }

  TEST(DoubleTest, EqualityOperatorComparesValuesCorrectly) {
    const Double a(5.0);
    const Double b(5.0);
    const Double c(6.0);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
  }

  TEST(DoubleTest, InequalityOperatorWorks) {
    const Double a(5.0);
    const Double b(6.0);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a);
  }

  TEST(DoubleTest, LessThanOperator) {
    const Double a(3.0);
    const Double b(5.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
  }

  TEST(DoubleTest, GreaterThanOperator) {
    const Double a(5.0);
    const Double b(3.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
  }

  TEST(DoubleTest, LessThanOrEqualOperator) {
    const Double a(3.0);
    const Double b(3.0);
    const Double c(5.0);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
  }

  TEST(DoubleTest, GreaterThanOrEqualOperator) {
    const Double a(5.0);
    const Double b(5.0);
    const Double c(3.0);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
  }

  TEST(DoubleTest, AdditionOperator) {
    const Double a(3.0);
    const Double b(4.0);
    const Double result = a + b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 7.0);
  }

  TEST(DoubleTest, SubtractionOperator) {
    const Double a(5.0);
    const Double b(3.0);
    const Double result = a - b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 2.0);
  }

  TEST(DoubleTest, MultiplicationOperator) {
    const Double a(2.5);
    const Double b(4.0);
    const Double result = a * b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 10.0);
  }

  TEST(DoubleTest, DivisionOperatorWithNonZeroDivisor) {
    const Double a(10.0);
    const Double b(2.0);
    const Double result = a / b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 5.0);
  }

  TEST(DoubleTest, DivisionByZeroThrowsOverflowError) {
    const Double a(5.0);
    const Double b(0.0);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(DoubleTest, ArithmeticOperationsWithNegativeNumbers) {
    const Double a(-3.0);
    const Double b(2.0);
    const Double addResult = a + b;
    const Double mulResult = a * b;
    EXPECT_DOUBLE_EQ(static_cast<double>(addResult), -1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(mulResult), -6.0);
  }
} // namespace gtest_case
