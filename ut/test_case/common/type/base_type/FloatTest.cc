#include <gtest/gtest.h>

#include "type/base_type/Float.hpp"

namespace gtest_case {
TEST(FloatTest, ConstructorInitializesValueCorrectly) {
  const common::Float f(3.14f);
  EXPECT_EQ(f.floatValue(), 3.14f);
}

TEST(FloatTest, CopyConstructorWorks) {
  const common::Float f1(2.5f);
  const common::Float& f2(f1);
  EXPECT_EQ(f1.floatValue(), f2.floatValue());
}

TEST(FloatTest, MoveConstructorWorks) {
  common::Float f1(2.5f);
  const common::Float f2(std::move(f1));
  EXPECT_EQ(f2.floatValue(), 2.5f);
}

TEST(FloatTest, CopyAssignmentWorks) {
  const common::Float f1(1.0f);
  common::Float f2(0.0f);
  f2 = f1;
  EXPECT_EQ(f1.floatValue(), f2.floatValue());
}

TEST(FloatTest, MoveAssignmentWorks) {
  common::Float f1(1.0f);
  common::Float f2(0.0f);
  f2 = std::move(f1);
  EXPECT_EQ(f2.floatValue(), 1.0f);
}

TEST(FloatTest, HashCodeReturnsSameForEqualValues) {
  const common::Float f1(2.5f);
  const common::Float f2(2.5f);
  EXPECT_EQ(f1.hashCode(), f2.hashCode());
}

TEST(FloatTest, ToStringReturnsValidString) {
  const common::Float f(3.14f);
  EXPECT_FALSE(f.toString().empty());
}

TEST(FloatTest, TypeConversionWorks) {
  const common::Float f(4.2f);
  const auto value = static_cast<float>(f);
  EXPECT_FLOAT_EQ(value, 4.2f);
}

TEST(FloatTest, ParseValidString) {
  const auto result = common::Float::parseFloat("123.45");
  EXPECT_FLOAT_EQ(result.floatValue(), 123.45f);
}

TEST(FloatTest, ParseInvalidStringThrows) { EXPECT_THROW(common::Float::parseFloat("abc"), std::invalid_argument); }

TEST(FloatTest, ParseOutOfRangeStringThrows) { EXPECT_THROW(common::Float::parseFloat("1e10000"), std::out_of_range); }

TEST(FloatTest, EqualityOperatorWorks) {
  const common::Float f1(5.0f);
  const common::Float f2(5.0f);
  EXPECT_TRUE(f1 == f2);
}

TEST(FloatTest, InequalityOperatorWorks) {
  const common::Float f1(5.0f);
  const common::Float f2(6.0f);
  EXPECT_TRUE(f1 != f2);
}

TEST(FloatTest, ThreeWayComparisonWorks) {
  const common::Float f1(3.0f);
  const common::Float f2(4.0f);
  EXPECT_TRUE(f1 <=> f2 == std::partial_ordering::less);
}

TEST(FloatTest, ArithmeticOperatorsWorkCorrectly) {
  const common::Float f1(2.0f);
  const common::Float f2(3.0f);
  EXPECT_FLOAT_EQ((f1 + f2).floatValue(), 5.0f);
  EXPECT_FLOAT_EQ((f1 - f2).floatValue(), -1.0f);
  EXPECT_FLOAT_EQ((f1 * f2).floatValue(), 6.0f);
}

TEST(FloatTest, DivisionByZeroThrowsOverflowError) {
  const common::Float f1(6.0f);
  const common::Float f2(0.0f);
  EXPECT_THROW(f1 / f2, std::overflow_error);
}

TEST(FloatTest, NaNComparisonBehavesCorrectly) {
  const common::Float f1(common::Float::NaN);
  const common::Float f2(common::Float::NaN);
  EXPECT_FALSE(f1 == f2);
  EXPECT_TRUE((f1 <=> f2) == std::partial_ordering::unordered);
}

TEST(FloatTest, InfinityValuesAreCorrect) {
  EXPECT_GT(common::Float::POSITIVE_INFINITY, std::numeric_limits<float>::max());
  EXPECT_LT(common::Float::NEGATIVE_INFINITY, -std::numeric_limits<float>::max());
}
}  // namespace gtest_case
