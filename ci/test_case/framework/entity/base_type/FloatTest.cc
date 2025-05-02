#include <entity/base_type/Float.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(FloatTest, ConstructorInitializesValueCorrectly) {
    const framework::entity::base_type::Float instance(3.14f);
    EXPECT_EQ(instance.floatValue(), 3.14f);
  }

  TEST(FloatTest, ToStringReturnsCorrectString) {
    const framework::entity::base_type::Float instance(5.0f);
    const std::string result = instance.toString();
    EXPECT_EQ(result, "5");
  }

  TEST(FloatTest, EqualsReturnsTrueForEqualValues) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(2.0f);
    EXPECT_TRUE(a.equals(b));
  }

  TEST(FloatTest, EqualsReturnsFalseForDifferentValues) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_FALSE(a.equals(b));
  }

  TEST(FloatTest, CompareToReturnsZeroForEqualValues) {
    const framework::entity::base_type::Float a(5.5f);
    const framework::entity::base_type::Float b(5.5f);
    EXPECT_EQ(a.compareTo(b), 0);
  }

  TEST(FloatTest, CompareToReturnsPositiveWhenGreater) {
    const framework::entity::base_type::Float a(10.0f);
    const framework::entity::base_type::Float b(5.0f);
    EXPECT_EQ(a.compareTo(b), 1);
  }

  TEST(FloatTest, CompareToReturnsNegativeWhenLess) {
    const framework::entity::base_type::Float a(1.5f);
    const framework::entity::base_type::Float b(2.5f);
    EXPECT_EQ(a.compareTo(b), -1);
  }

  TEST(FloatTest, EqualityOperatorReturnsTrueForSameValues) {
    const framework::entity::base_type::Float a(4.2f);
    const framework::entity::base_type::Float b(4.2f);
    EXPECT_TRUE(a == b);
  }

  TEST(FloatTest, EqualityOperatorReturnsFalseForDifferentValues) {
    const framework::entity::base_type::Float a(4.2f);
    const framework::entity::base_type::Float b(5.2f);
    EXPECT_FALSE(a == b);
  }

  TEST(FloatTest, InequalityOperatorReturnsTrueForDifferentValues) {
    const framework::entity::base_type::Float a(3.0f);
    const framework::entity::base_type::Float b(4.0f);
    EXPECT_TRUE(a != b);
  }

  TEST(FloatTest, InequalityOperatorReturnsFalseForSameValues) {
    const framework::entity::base_type::Float a(3.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_FALSE(a != b);
  }

  TEST(FloatTest, LessThanOperatorWorksWhenTrue) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_TRUE(a < b);
  }

  TEST(FloatTest, LessThanOperatorWorksWhenFalse) {
    const framework::entity::base_type::Float a(4.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_FALSE(a < b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenTrue) {
    const framework::entity::base_type::Float a(5.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_TRUE(a > b);
  }

  TEST(FloatTest, GreaterThanOperatorWorksWhenFalse) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_FALSE(a > b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenEqual) {
    const framework::entity::base_type::Float a(3.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, LessThanOrEqualOperatorWorksWhenLess) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_TRUE(a <= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenEqual) {
    const framework::entity::base_type::Float a(4.0f);
    const framework::entity::base_type::Float b(4.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, GreaterThanOrEqualOperatorWorksWhenGreater) {
    const framework::entity::base_type::Float a(5.0f);
    const framework::entity::base_type::Float b(3.0f);
    EXPECT_TRUE(a >= b);
  }

  TEST(FloatTest, AdditionOperatorWorksCorrectly) {
    const framework::entity::base_type::Float a(2.0f);
    const framework::entity::base_type::Float b(3.0f);
    const framework::entity::base_type::Float result = a + b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, SubtractionOperatorWorksCorrectly) {
    const framework::entity::base_type::Float a(5.0f);
    const framework::entity::base_type::Float b(2.0f);
    const framework::entity::base_type::Float result = a - b;
    EXPECT_EQ(result.floatValue(), 3.0f);
  }

  TEST(FloatTest, MultiplicationOperatorWorksCorrectly) {
    const framework::entity::base_type::Float a(3.0f);
    const framework::entity::base_type::Float b(4.0f);
    const framework::entity::base_type::Float result = a * b;
    EXPECT_EQ(result.floatValue(), 12.0f);
  }

  TEST(FloatTest, DivisionOperatorWorksCorrectly) {
    const framework::entity::base_type::Float a(10.0f);
    const framework::entity::base_type::Float b(2.0f);
    const framework::entity::base_type::Float result = a / b;
    EXPECT_EQ(result.floatValue(), 5.0f);
  }

  TEST(FloatTest, DivisionOperatorThrowsWhenDividingByZero) {
    const framework::entity::base_type::Float a(10.0f);
    const framework::entity::base_type::Float b(0.0f);
    EXPECT_THROW(a / b, std::overflow_error);
  }

  TEST(FloatTest, ParseFloatConvertsValidStringToFloat) {
    const std::string str = "123.45";
    const framework::entity::base_type::Float result = framework::entity::base_type::Float::parseFloat(str);
    EXPECT_EQ(result.floatValue(), 123.45f);
  }

  TEST(FloatTest, ParseFloatThrowsInvalidArgumentForInvalidString) {
    const std::string str = "abc";
    EXPECT_THROW(framework::entity::base_type::Float::parseFloat(str), std::invalid_argument);
  }

  TEST(FloatTest, ParseFloatThrowsOutOfRangeForExceedingString) {
    const std::string str = "1e1000";
    EXPECT_THROW(framework::entity::base_type::Float::parseFloat(str), std::out_of_range);
  }
} // namespace gtest_case
