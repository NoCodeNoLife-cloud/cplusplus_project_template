#include <entity/base_type/Float.hpp>
#include <gtest/gtest.h>
using framework::Float;

namespace gtest_case {
  TEST(FloatTest, ConstructorInitializesValueCorrectly) {
    const Float instance(3.14f);
    EXPECT_EQ(instance.floatValue(), 3.14f);
  }

  TEST(FloatTest, ToStringReturnsCorrectString) {
    const Float instance(5.0f);
    const std::string result = instance.toString();
    EXPECT_EQ(result, "5");
  }

  TEST(FloatTest, EqualsReturnsTrueForEqualValues) {
    const Float a(2.0f);
    const Float b(2.0f);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(FloatTest, EqualsReturnsFalseForDifferentValues) {
    const Float a(2.0f);
    const Float b(3.0f);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(FloatTest, CompareToReturnsZeroForEqualValues) {
    const Float a(5.5f);
    const Float b(5.5f);
    EXPECT_EQ(a.compareTo(b), 0);
  }

  TEST(FloatTest, CompareToReturnsPositiveWhenGreater) {
    const Float a(10.0f);
    const Float b(5.0f);
    EXPECT_EQ(a.compareTo(b), 1);
  }

  TEST(FloatTest, CompareToReturnsNegativeWhenLess) {
    const Float a(1.5f);
    const Float b(2.5f);
    EXPECT_EQ(a.compareTo(b), -1);
  }

  TEST(FloatTest, EqualityOperatorReturnsTrueForSameValues) {
    const Float a(4.2f);
    const Float b(4.2f);
    EXPECT_TRUE(a == b);
  }

  TEST(FloatTest, EqualityOperatorReturnsFalseForDifferentValues) {
    const Float a(4.2f);
    const Float b(5.2f);
    EXPECT_FALSE(a == b);
  }

  TEST(FloatTest, InequalityOperatorReturnsTrueForDifferentValues) {
    const Float a(3.0f);
    const Float b(4.0f);
    EXPECT_TRUE(a != b);
  }

  TEST(FloatTest, InequalityOperatorReturnsFalseForSameValues) {
    const Float a(3.0f);
    const Float b(3.0f);
    EXPECT_FALSE(a != b);
  }

  TEST(FloatTest, LessThanOperatorWorksWhenTrue) {
    const Float a(2.0f);
    const Float b(3.0f);
    EXPECT_TRUE(a < b);
  }

  TEST(FloatTest, LessThanOperatorWorksWhenFalse) {
    const Float a(4.0f);
    const Float b(3.0f);
    EXPECT_FALSE(a < b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenTrue) {
    const Float a(5.0f);
    const Float b(3.0f);
    EXPECT_TRUE(a > b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenFalse) {
    const Float a(2.0f);
    const Float b(3.0f);
    EXPECT_FALSE(a > b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenEqual) {
    const Float a(3.0f);
    const Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenLess) {
    const Float a(2.0f);
    const Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenEqual) {
    const Float a(4.0f);
    const Float b(4.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenGreater) {
    const Float a(5.0f);
    const Float b(3.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, AdditionOperatorWorksCorrectly) {
    const Float a(2.0f);
    const Float b(3.0f);
    const Float result = a + b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, SubtractionOperatorWorksCorrectly) {
    const Float a(5.0f);
    const Float b(2.0f);
    const Float result = a - b;
    EXPECT_EQ(result.floatValue(), 3.0f);
  }

  TEST(FloatTest, MultiplicationOperatorWorksCorrectly) {
    const Float a(3.0f);
    const Float b(4.0f);
    const Float result = a * b;
    EXPECT_EQ(result.floatValue(), 12.0f);
  }

  TEST(FloatTest, DivisionOperatorWorksCorrectly) {
    const Float a(10.0f);
    const Float b(2.0f);
    const Float result = a / b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, DivisionOperatorThrowsWhenDividingByZero) {
    const Float a(10.0f);
    const Float b(0.0f);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(FloatTest, ParseFloatConvertsValidStringToFloat) {
    const std::string str = "123.45";
    const Float result = Float::parseFloat(str);
    EXPECT_EQ(result.floatValue(), 123.45f);
  }

  TEST(FloatTest, ParseFloatThrowsInvalidArgumentForInvalidString) {
    const std::string str = "abc";
    EXPECT_THROW(Float::parseFloat(str), std::invalid_argument);
  }

  TEST(FloatTest, ParseFloatThrowsOutOfRangeForExceedingString) {
    const std::string str = "1e1000";
    EXPECT_THROW(Float::parseFloat(str), std::out_of_range);
  }
}
