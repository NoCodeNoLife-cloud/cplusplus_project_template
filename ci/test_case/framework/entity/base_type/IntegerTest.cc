#include <string>
#include <entity/base_type/Integer.hpp>
#include <gtest/gtest.h>
using common::Integer;

namespace gtest_case {
  TEST(IntegerTest, ConstructorInitializesValueCorrectly) {
    const Integer integer(42);
    EXPECT_EQ(integer.intValue(), 42);
  }

  TEST(IntegerTest, TypeConversionReturnsCorrectValue) {
    const Integer integer(-7);
    EXPECT_EQ(static_cast<int32_t>(integer), -7);
  }

  TEST(IntegerTest, IntValueReturnsStoredValue) {
    const Integer integer(100);
    EXPECT_EQ(integer.intValue(), 100);
  }

  TEST(IntegerTest, ToStringReturnsCorrectString) {
    const Integer integer(123);
    EXPECT_EQ(integer.toString(), "123");
  }

  TEST(IntegerTest, ParseIntValidInput) {
    const Integer zero = Integer::parseInt("0");
    const Integer positive = Integer::parseInt("+42");
    const Integer negative = Integer::parseInt("-15");

    EXPECT_EQ(zero.intValue(), 0);
    EXPECT_EQ(positive.intValue(), 42);
    EXPECT_EQ(negative.intValue(), -15);
  }

  TEST(IntegerTest, ParseIntInvalidInputThrows) {
    EXPECT_THROW(Integer::parseInt(""), std::invalid_argument);
    EXPECT_THROW(Integer::parseInt("abc"), std::invalid_argument);
    EXPECT_THROW(Integer::parseInt("12a3"), std::invalid_argument);
    // EXPECT_THROW(, std::invalid_argument);
    Integer::parseInt(" 123");
  }

  TEST(IntegerTest, ParseIntOutOfRangeThrows) {
    EXPECT_THROW(Integer::parseInt("2147483648"), std::out_of_range);
    EXPECT_THROW(Integer::parseInt("-2147483649"), std::out_of_range);
  }

  TEST(IntegerTest, EqualsMethodComparesValues) {
    const Integer a(5);
    const Integer b(5);
    const Integer c(8);

    EXPECT_TRUE(a.equals(b));
    EXPECT_FALSE(a.equals(c));
  }

  TEST(IntegerTest, CompareToReturnsCorrectResult) {
    const Integer a(3);
    const Integer b(3);
    const Integer c(7);

    EXPECT_EQ(a.compareTo(b), 0);
    EXPECT_LT(a.compareTo(c), 0);
    EXPECT_GT(c.compareTo(a), 0);
  }

  TEST(IntegerTest, EqualityOperatorsWorkCorrectly) {
    const Integer a(2);
    const Integer b(2);
    const Integer c(5);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
  }

  TEST(IntegerTest, RelationalOperatorsWorkCorrectly) {
    const Integer a(4);
    const Integer b(6);
    const Integer c(4);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(b >= a);
  }

  TEST(IntegerTest, AdditionOperatorReturnsCorrectResult) {
    const Integer a(3);
    const Integer b(5);
    const Integer result = a + b;

    EXPECT_EQ(result.intValue(), 8);
  }

  TEST(IntegerTest, SubtractionOperatorReturnsCorrectResult) {
    const Integer a(10);
    const Integer b(4);
    const Integer result = a - b;

    EXPECT_EQ(result.intValue(), 6);
  }

  TEST(IntegerTest, MultiplicationOperatorReturnsCorrectResult) {
    const Integer a(7);
    const Integer b(3);
    const Integer result = a * b;

    EXPECT_EQ(result.intValue(), 21);
  }

  TEST(IntegerTest, DivisionOperatorReturnsCorrectResult) {
    const Integer a(15);
    const Integer b(3);
    const Integer result = a / b;

    EXPECT_EQ(result.intValue(), 5);
  }

  TEST(IntegerTest, DivisionByZeroThrowsException) {
    const Integer a(10);
    const Integer b(0);

    EXPECT_THROW(a / b, std::invalid_argument);
  }
}
