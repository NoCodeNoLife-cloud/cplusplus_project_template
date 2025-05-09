#include <entity/base_type/Float.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(FloatTest, ConstructorInitializesValueCorrectly) {
    const common::Float instance(3.14f);
    EXPECT_EQ(instance.floatValue(), 3.14f);
  }

  TEST(FloatTest, EqualityOperatorReturnsTrueForSameValues) {
    const common::Float a(4.2f);
    const common::Float b(4.2f);
    EXPECT_TRUE(std::is_eq(a <=> b));
  }

  TEST(FloatTest, EqualityOperatorReturnsFalseForDifferentValues) {
    const common::Float a(4.2f);
    const common::Float b(5.2f);
    EXPECT_FALSE(std::is_eq(a <=> b));
  }

  TEST(FloatTest, InequalityOperatorReturnsTrueForDifferentValues) {
    const common::Float a(3.0f);
    const common::Float b(4.0f);
    EXPECT_TRUE(std::is_neq(a <=> b));
  }

  TEST(FloatTest, InequalityOperatorReturnsFalseForSameValues) {
    const common::Float a(3.0f);
    const common::Float b(3.0f);
    EXPECT_FALSE(std::is_neq(a <=> b));
  }

  TEST(FloatTest, LessThanOperatorWorksWhenTrue) {
    const common::Float a(2.0f);
    const common::Float b(3.0f);
    EXPECT_TRUE(a < b);
  }

  TEST(FloatTest, LessThanOperatorWorksWhenFalse) {
    const common::Float a(4.0f);
    const common::Float b(3.0f);
    EXPECT_FALSE(a < b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenTrue) {
    const common::Float a(5.0f);
    const common::Float b(3.0f);
    EXPECT_TRUE(a > b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenFalse) {
    const common::Float a(2.0f);
    const common::Float b(3.0f);
    EXPECT_FALSE(a > b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenEqual) {
    const common::Float a(3.0f);
    const common::Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenLess) {
    const common::Float a(2.0f);
    const common::Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenEqual) {
    const common::Float a(4.0f);
    const common::Float b(4.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenGreater) {
    const common::Float a(5.0f);
    const common::Float b(3.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, AdditionOperatorWorksCorrectly) {
    const common::Float a(2.0f);
    const common::Float b(3.0f);
    const common::Float result = a + b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, SubtractionOperatorWorksCorrectly) {
    const common::Float a(5.0f);
    const common::Float b(2.0f);
    const common::Float result = a - b;
    EXPECT_EQ(result.floatValue(), 3.0f);
  }

  TEST(FloatTest, MultiplicationOperatorWorksCorrectly) {
    const common::Float a(3.0f);
    const common::Float b(4.0f);
    const common::Float result = a * b;
    EXPECT_EQ(result.floatValue(), 12.0f);
  }

  TEST(FloatTest, DivisionOperatorWorksCorrectly) {
    const common::Float a(10.0f);
    const common::Float b(2.0f);
    const common::Float result = a / b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, DivisionOperatorThrowsWhenDividingByZero) {
    const common::Float a(10.0f);
    const common::Float b(0.0f);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(FloatTest, ParseFloatConvertsValidStringToFloat) {
    const std::string str = "123.45";
    const common::Float result = common::Float::parseFloat(str);
    EXPECT_EQ(result.floatValue(), 123.45f);
  }

  TEST(FloatTest, ParseFloatThrowsInvalidArgumentForInvalidString) {
    const std::string str = "abc";
    EXPECT_THROW(common::Float::parseFloat(str), std::invalid_argument);
  }

  TEST(FloatTest, ParseFloatThrowsOutOfRangeForExceedingString) {
    const std::string str = "1e1000";
    EXPECT_THROW(common::Float::parseFloat(str), std::out_of_range);
  }
}
