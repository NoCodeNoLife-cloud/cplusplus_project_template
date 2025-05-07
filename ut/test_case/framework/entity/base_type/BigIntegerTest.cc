#include <entity/base_type/BigInteger.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BigIntegerTest, DefaultConstructorInitializesToZero) {
    const common::BigInteger bigInt;
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, StringConstructorWithPositiveNumber) {
    const common::BigInteger bigInt("12345");
    EXPECT_EQ(bigInt.toString(), "12345");
  }

  TEST(BigIntegerTest, StringConstructorWithNegativeNumber) {
    const common::BigInteger bigInt("-6789");
    EXPECT_EQ(bigInt.toString(), "-6789");
  }

  TEST(BigIntegerTest, StringConstructorWithZero) {
    const common::BigInteger bigInt("0");
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, IntConstructorWithPositive) {
    const common::BigInteger bigInt(42);
    EXPECT_EQ(bigInt.toString(), "42");
  }

  TEST(BigIntegerTest, IntConstructorWithNegative) {
    const common::BigInteger bigInt(-15);
    EXPECT_EQ(bigInt.toString(), "-15");
  }

  TEST(BigIntegerTest, IntConstructorWithZero) {
    const common::BigInteger bigInt(0);
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, AdditionPositiveNumbers) {
    const common::BigInteger a("100");
    const common::BigInteger b("200");
    const common::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, AdditionNegativeAndPositive) {
    const common::BigInteger a("-50");
    const common::BigInteger b("30");
    const common::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "-20");
  }

  TEST(BigIntegerTest, AdditionWithZero) {
    const common::BigInteger a("123");
    const common::BigInteger b(0);
    const common::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "123");
  }

  TEST(BigIntegerTest, SubtractionPositiveResult) {
    const common::BigInteger a("500");
    const common::BigInteger b("200");
    const common::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, SubtractionNegativeResult) {
    const common::BigInteger a("100");
    const common::BigInteger b("150");
    const common::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "-50");
  }

  TEST(BigIntegerTest, SubtractionWithZero) {
    const common::BigInteger a("789");
    const common::BigInteger b(0);
    const common::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "789");
  }

  TEST(BigIntegerTest, MultiplicationPositive) {
    const common::BigInteger a("12");
    const common::BigInteger b("34");
    const common::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "408");
  }

  TEST(BigIntegerTest, MultiplicationWithNegative) {
    const common::BigInteger a("-5");
    const common::BigInteger b("7");
    const common::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "-35");
  }

  TEST(BigIntegerTest, MultiplicationByZero) {
    const common::BigInteger a("99");
    const common::BigInteger b(0);
    const common::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "0");
  }

  TEST(BigIntegerTest, DivisionExact) {
    const common::BigInteger a("100");
    const common::BigInteger b("25");
    const common::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "4");
  }

  TEST(BigIntegerTest, DivisionWithRemainder) {
    const common::BigInteger a("10");
    const common::BigInteger b("3");
    const common::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "3");
  }

  TEST(BigIntegerTest, DivisionByNegative) {
    const common::BigInteger a("50");
    const common::BigInteger b("-5");
    const common::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "-10");
  }

  TEST(BigIntegerTest, DivisionByZeroThrowsException) {
    const common::BigInteger a("10");
    const common::BigInteger b("0");
    EXPECT_THROW({ a / b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, ModuloPositiveNumbers) {
    const common::BigInteger a("10");
    const common::BigInteger b("3");
    const common::BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "1");
  }

  TEST(BigIntegerTest, ModuloNegativeDividend) {
    const common::BigInteger a("-10");
    const common::BigInteger b("3");
    const common::BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "-1");
  }

  TEST(BigIntegerTest, ModuloByZeroThrowsException) {
    const common::BigInteger a("5");
    const common::BigInteger b("0");
    EXPECT_THROW({ a % b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, EqualityOperatorTrue) {
    const common::BigInteger a("123");
    const common::BigInteger b("123");
    EXPECT_TRUE(std::is_eq(a <=> b));
  }

  TEST(BigIntegerTest, EqualityOperatorFalse) {
    const common::BigInteger a("123");
    const common::BigInteger b("456");
    EXPECT_FALSE(std::is_eq(a <=> b));
  }

  TEST(BigIntegerTest, InequalityOperatorTrue) {
    const common::BigInteger a("789");
    const common::BigInteger b("987");
    EXPECT_TRUE(std::is_neq(a <=> b));
  }

  TEST(BigIntegerTest, InequalityOperatorFalse) {
    const common::BigInteger a("555");
    const common::BigInteger b("555");
    EXPECT_FALSE(std::is_neq(a <=> b));
  }

  TEST(BigIntegerTest, LessThanOperatorTrue) {
    const common::BigInteger a("100");
    const common::BigInteger b("200");
    EXPECT_TRUE(a < b);
  }

  TEST(BigIntegerTest, LessThanOperatorFalse) {
    const common::BigInteger a("500");
    const common::BigInteger b("300");
    EXPECT_FALSE(a < b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual) {
    const common::BigInteger a("42");
    const common::BigInteger b("42");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess) {
    const common::BigInteger a("-5");
    const common::BigInteger b("5");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorTrue) {
    const common::BigInteger a("999");
    const common::BigInteger b("123");
    EXPECT_TRUE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorFalse) {
    const common::BigInteger a("123");
    const common::BigInteger b("999");
    EXPECT_FALSE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual) {
    const common::BigInteger a("0");
    const common::BigInteger b("0");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater) {
    const common::BigInteger a("100");
    const common::BigInteger b("-100");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, ToStringCanBeConvertedBack) {
    const common::BigInteger original("1234567890");
    const std::string str = original.toString();
    const common::BigInteger copied(str);
    EXPECT_EQ(copied.toString(), "1234567890");
  }

  TEST(BigIntegerTest, FromStringHandlesNegative) {
    const common::BigInteger bigInt = common::BigInteger::fromString("-456");
    EXPECT_EQ(bigInt.toString(), "-456");
  }

  TEST(BigIntegerTest, FromIntHandlesLargePositive) {
    const common::BigInteger bigInt = common::BigInteger::fromInt(9223372036854775807LL);
    EXPECT_EQ(bigInt.toString(), "9223372036854775807");
  }

  TEST(BigIntegerTest, FromIntHandlesLargeNegative) {
    const common::BigInteger bigInt = common::BigInteger::fromInt(-9223372036854775807LL - 1);
    EXPECT_EQ(bigInt.toString(), "-9223372036854775808");
  }
}
