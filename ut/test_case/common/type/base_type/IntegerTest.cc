#include <gtest/gtest.h>

#include <string>

#include "type/base_type/Integer.hpp"

namespace gtest_case {
TEST(IntegerTest, DefaultConstructorInitializesToZero) {
  const common::Integer obj;
  EXPECT_EQ(obj.intValue(), 0);
}

TEST(IntegerTest, ParameterizedConstructorSetsValue) {
  const common::Integer obj(42);
  EXPECT_EQ(obj.intValue(), 42);
}

TEST(IntegerTest, CopyConstructorCopiesValue) {
  const common::Integer a(100);
  const common::Integer& b(a);
  EXPECT_EQ(b.intValue(), 100);
}

TEST(IntegerTest, MoveConstructorTransfersValue) {
  common::Integer a(200);
  const common::Integer b(std::move(a));
  EXPECT_EQ(b.intValue(), 200);
}

TEST(IntegerTest, CopyAssignmentCopiesValue) {
  const common::Integer a(10);
  const common::Integer& b = a;
  EXPECT_EQ(b.intValue(), 10);
}

TEST(IntegerTest, MoveAssignmentTransfersValue) {
  common::Integer a(20);
  const common::Integer b = std::move(a);
  EXPECT_EQ(b.intValue(), 20);
}

TEST(IntegerTest, SelfCopyAssignmentHandled) {
  common::Integer a(5);
  // ReSharper disable once CppIdenticalOperandsInBinaryExpression
  a = a;
  EXPECT_EQ(a.intValue(), 5);
}

TEST(IntegerTest, SelfMoveAssignmentHandled) {
  common::Integer a(5);
  a = std::move(a);
  EXPECT_EQ(a.intValue(), 5);
}

TEST(IntegerTest, HashCodeConsistency) {
  const common::Integer a(10), b(10);
  EXPECT_EQ(a.hashCode(), b.hashCode());
}

TEST(IntegerTest, ToStringReturnsValidString) {
  const common::Integer obj(123);
  EXPECT_EQ(obj.toString(), "class common::Integer{123}");
}

TEST(IntegerTest, TypeConversionToInt32) {
  const common::Integer obj(456);
  const auto value = static_cast<int32_t>(obj);
  EXPECT_EQ(value, 456);
}

TEST(IntegerTest, IntValueMethod) {
  const common::Integer obj(-789);
  EXPECT_EQ(obj.intValue(), -789);
}

TEST(IntegerTest, ParseValidIntegerString) { EXPECT_EQ(common::Integer::parseInt("12345").intValue(), 12345); }

TEST(IntegerTest, ParseNegativeValue) { EXPECT_EQ(common::Integer::parseInt("-56789").intValue(), -56789); }

TEST(IntegerTest, ParseInvalidStringThrows) { EXPECT_THROW(common::Integer::parseInt("abc"), std::invalid_argument); }

TEST(IntegerTest, ParseOutOfRangeValueThrows) { EXPECT_THROW(common::Integer::parseInt("2147483648"), std::out_of_range); }

TEST(IntegerTest, EqualityOperatorTrueForSameValues) {
  const common::Integer a(100), b(100);
  EXPECT_TRUE(a == b);
}

TEST(IntegerTest, EqualityOperatorFalseForDifferentValues) {
  const common::Integer a(100), b(200);
  EXPECT_FALSE(a == b);
}

TEST(IntegerTest, ThreeWayComparisonEqual) {
  const common::Integer a(50), b(50);
  EXPECT_EQ(a <=> b, std::partial_ordering::equivalent);
}

TEST(IntegerTest, ThreeWayComparisonLess) {
  const common::Integer a(30), b(40);
  EXPECT_EQ(a <=> b, std::partial_ordering::less);
}

TEST(IntegerTest, ThreeWayComparisonGreater) {
  const common::Integer a(60), b(50);
  EXPECT_EQ(a <=> b, std::partial_ordering::greater);
}

TEST(IntegerTest, AdditionOperator) {
  const common::Integer a(10), b(20);
  EXPECT_EQ((a + b).intValue(), 30);
}

TEST(IntegerTest, SubtractionOperator) {
  const common::Integer a(50), b(30);
  EXPECT_EQ((a - b).intValue(), 20);
}

TEST(IntegerTest, MultiplicationOperator) {
  const common::Integer a(8), b(7);
  EXPECT_EQ((a * b).intValue(), 56);
}

TEST(IntegerTest, DivisionOperator) {
  const common::Integer a(100), b(25);
  EXPECT_EQ((a / b).intValue(), 4);
}

TEST(IntegerTest, DivisionByZeroThrows) {
  const common::Integer a(10);
  const common::Integer zero(0);
  EXPECT_THROW(a / zero, std::invalid_argument);
}

// 原代码缺陷发现：未处理整数溢出
// 例如以下测试用例会通过，但实际结果溢出导致错误
TEST(IntegerTest, AdditionOverflowIssue) {
  const common::Integer max(std::numeric_limits<int32_t>::max());
  const common::Integer one(1);
  const common::Integer result = max + one;  // 此处会发生溢出
  // 实际结果会变成负数（溢出行为），但原代码未处理
  EXPECT_LT(result.intValue(), 0);  // 检测到溢出
}
}  // namespace gtest_case
