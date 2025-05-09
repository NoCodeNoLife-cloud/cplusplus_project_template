#include <stdexcept>
#include <string>
#include <entity/base_type/Double.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(DoubleTest, ConstructorInitializesValueCorrectly) {
    constexpr double value = 42.0;
    const common::Double d(value);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), value);
  }

  TEST(DoubleTest, ConversionOperatorReturnsStoredValue) {
    const common::Double d(3.14);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), 3.14);
  }

  TEST(DoubleTest, EqualsReturnsTrueForEqualValues) {
    const common::Double a(5.0);
    const common::Double b(5.0);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(DoubleTest, EqualsReturnsFalseForDifferentValues) {
    const common::Double a(5.0);
    const common::Double b(6.0);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(DoubleTest, CompareToReturnsZeroWhenEqual) {
    const common::Double a(5.0);
    EXPECT_EQ(a.compareTo(a), 0);
  }

  TEST(DoubleTest, CompareToReturnsPositiveWhenGreater) {
    const common::Double a(6.0);
    const common::Double b(5.0);
    EXPECT_EQ(a.compareTo(b), 1);
  }

  TEST(DoubleTest, CompareToReturnsNegativeWhenLess) {
    const common::Double a(5.0);
    const common::Double b(6.0);
    EXPECT_EQ(a.compareTo(b), -1);
  }

  TEST(DoubleTest, ParseDoubleConvertsValidString) {
    const std::string str = "123.45";
    const common::Double d = common::Double::parseDouble(str);
    EXPECT_DOUBLE_EQ(static_cast<double>(d), 123.45);
  }

  TEST(DoubleTest, ParseDoubleThrowsInvalidArgumentForInvalidInput) {
    const std::string invalid = "abc";
    EXPECT_THROW(common::Double::parseDouble(invalid), std::invalid_argument);
  }

  TEST(DoubleTest, ParseDoubleThrowsOutOfRangeForLargeValue) {
    const std::string huge = "1e999999999";
    EXPECT_THROW(common::Double::parseDouble(huge), std::out_of_range);
  }

  TEST(DoubleTest, EqualityOperatorComparesValuesCorrectly) {
    const common::Double a(5.0);
    const common::Double b(5.0);
    const common::Double c(6.0);
    EXPECT_TRUE(std::is_eq(a <=> b));
    EXPECT_FALSE(std::is_eq(a <=> c));
  }

  TEST(DoubleTest, InequalityOperatorWorks) {
    const common::Double a(5.0);
    const common::Double b(6.0);
    EXPECT_TRUE(std::is_neq(a <=> b));
    EXPECT_FALSE(std::is_neq(a <=> a));
  }

  TEST(DoubleTest, LessThanOperator) {
    const common::Double a(3.0);
    const common::Double b(5.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
  }

  TEST(DoubleTest, GreaterThanOperator) {
    const common::Double a(5.0);
    const common::Double b(3.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
  }

  TEST(DoubleTest, LessThanOrEqualOperator) {
    const common::Double a(3.0);
    const common::Double b(3.0);
    const common::Double c(5.0);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
  }

  TEST(DoubleTest, GreaterThanOrEqualOperator) {
    const common::Double a(5.0);
    const common::Double b(5.0);
    const common::Double c(3.0);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
  }

  TEST(DoubleTest, AdditionOperator) {
    const common::Double a(3.0);
    const common::Double b(4.0);
    const common::Double result = a + b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 7.0);
  }

  TEST(DoubleTest, SubtractionOperator) {
    const common::Double a(5.0);
    const common::Double b(3.0);
    const common::Double result = a - b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 2.0);
  }

  TEST(DoubleTest, MultiplicationOperator) {
    const common::Double a(2.5);
    const common::Double b(4.0);
    const common::Double result = a * b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 10.0);
  }

  TEST(DoubleTest, DivisionOperatorWithNonZeroDivisor) {
    const common::Double a(10.0);
    const common::Double b(2.0);
    const common::Double result = a / b;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 5.0);
  }

  TEST(DoubleTest, DivisionByZeroThrowsOverflowError) {
    const common::Double a(5.0);
    const common::Double b(0.0);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(DoubleTest, ArithmeticOperationsWithNegativeNumbers) {
    const common::Double a(-3.0);
    const common::Double b(2.0);
    const common::Double addResult = a + b;
    const common::Double mulResult = a * b;
    EXPECT_DOUBLE_EQ(static_cast<double>(addResult), -1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(mulResult), -6.0);
  }
}
