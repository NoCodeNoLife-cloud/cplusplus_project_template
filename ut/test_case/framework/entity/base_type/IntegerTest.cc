#include <string>
#include <entity/base_type/Integer.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(IntegerTest, ConstructorInitializesValueCorrectly) {
    const common::Integer integer(42);
    EXPECT_EQ(integer.intValue(), 42);
  }

  TEST(IntegerTest, TypeConversionReturnsCorrectValue) {
    const common::Integer integer(-7);
    EXPECT_EQ(static_cast<int32_t>(integer), -7);
  }

  TEST(IntegerTest, IntValueReturnsStoredValue) {
    const common::Integer integer(100);
    EXPECT_EQ(integer.intValue(), 100);
  }

  TEST(IntegerTest, ToStringReturnsCorrectString) {
    const common::Integer integer(123);
    EXPECT_EQ(integer.toString(), "class common::Integer{123}");
  }

  TEST(IntegerTest, ParseIntValidInput) {
    const common::Integer zero = common::Integer::parseInt("0");
    const common::Integer positive = common::Integer::parseInt("+42");
    const common::Integer negative = common::Integer::parseInt("-15");

    EXPECT_EQ(zero.intValue(), 0);
    EXPECT_EQ(positive.intValue(), 42);
    EXPECT_EQ(negative.intValue(), -15);
  }

  TEST(IntegerTest, ParseIntInvalidInputThrows) {
    EXPECT_THROW(common::Integer::parseInt(""), std::invalid_argument);
    EXPECT_THROW(common::Integer::parseInt("abc"), std::invalid_argument);
    EXPECT_THROW(common::Integer::parseInt("12a3"), std::invalid_argument);
    // EXPECT_THROW(, std::invalid_argument);
    common::Integer::parseInt(" 123");
  }

  TEST(IntegerTest, ParseIntOutOfRangeThrows) {
    EXPECT_THROW(common::Integer::parseInt("2147483648"), std::out_of_range);
    EXPECT_THROW(common::Integer::parseInt("-2147483649"), std::out_of_range);
  }

  TEST(IntegerTest, EqualsMethodComparesValues) {
    const common::Integer a(5);
    const common::Integer b(5);
    const common::Integer c(8);

    EXPECT_TRUE(a.equals(b));
    EXPECT_FALSE(a.equals(c));
  }

  TEST(IntegerTest, CompareToReturnsCorrectResult) {
    const common::Integer a(3);
    const common::Integer b(3);
    const common::Integer c(7);

    EXPECT_EQ(a.compareTo(b), 0);
    EXPECT_LT(a.compareTo(c), 0);
    EXPECT_GT(c.compareTo(a), 0);
  }

  TEST(IntegerTest, EqualityOperatorsWorkCorrectly) {
    const common::Integer a(2);
    const common::Integer b(2);
    const common::Integer c(5);

    EXPECT_TRUE(std::is_eq(a <=> b));
    EXPECT_FALSE(std::is_eq(a <=> c));
    EXPECT_TRUE(std::is_neq(a <=> c));
  }

  TEST(IntegerTest, RelationalOperatorsWorkCorrectly) {
    const common::Integer a(4);
    const common::Integer b(6);
    const common::Integer c(4);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(b >= a);
  }

  TEST(IntegerTest, AdditionOperatorReturnsCorrectResult) {
    const common::Integer a(3);
    const common::Integer b(5);
    const common::Integer result = a + b;

    EXPECT_EQ(result.intValue(), 8);
  }

  TEST(IntegerTest, SubtractionOperatorReturnsCorrectResult) {
    const common::Integer a(10);
    const common::Integer b(4);
    const common::Integer result = a - b;

    EXPECT_EQ(result.intValue(), 6);
  }

  TEST(IntegerTest, MultiplicationOperatorReturnsCorrectResult) {
    const common::Integer a(7);
    const common::Integer b(3);
    const common::Integer result = a * b;

    EXPECT_EQ(result.intValue(), 21);
  }

  TEST(IntegerTest, DivisionOperatorReturnsCorrectResult) {
    const common::Integer a(15);
    const common::Integer b(3);
    const common::Integer result = a / b;

    EXPECT_EQ(result.intValue(), 5);
  }

  TEST(IntegerTest, DivisionByZeroThrowsException) {
    const common::Integer a(10);
    const common::Integer b(0);

    EXPECT_THROW(a / b, std::invalid_argument);
  }
}
