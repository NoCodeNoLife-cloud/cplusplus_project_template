#include <entity/base_type/BigInteger.hpp>
#include <gtest/gtest.h>
using common::BigInteger;

namespace gtest_case {
  TEST(BigIntegerTest, DefaultConstructorInitializesToZero) {
    const BigInteger bigInt;
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, StringConstructorWithPositiveNumber) {
    const BigInteger bigInt("12345");
    EXPECT_EQ(bigInt.toString(), "12345");
  }

  TEST(BigIntegerTest, StringConstructorWithNegativeNumber) {
    const BigInteger bigInt("-6789");
    EXPECT_EQ(bigInt.toString(), "-6789");
  }

  TEST(BigIntegerTest, StringConstructorWithZero) {
    const BigInteger bigInt("0");
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, IntConstructorWithPositive) {
    const BigInteger bigInt(42);
    EXPECT_EQ(bigInt.toString(), "42");
  }

  TEST(BigIntegerTest, IntConstructorWithNegative) {
    const BigInteger bigInt(-15);
    EXPECT_EQ(bigInt.toString(), "-15");
  }

  TEST(BigIntegerTest, IntConstructorWithZero) {
    const BigInteger bigInt(0);
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, AdditionPositiveNumbers) {
    const BigInteger a("100");
    const BigInteger b("200");
    const BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, AdditionNegativeAndPositive) {
    const BigInteger a("-50");
    const BigInteger b("30");
    const BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "-20");
  }

  TEST(BigIntegerTest, AdditionWithZero) {
    const BigInteger a("123");
    const BigInteger b(0);
    const BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "123");
  }

  TEST(BigIntegerTest, SubtractionPositiveResult) {
    const BigInteger a("500");
    const BigInteger b("200");
    const BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, SubtractionNegativeResult) {
    const BigInteger a("100");
    const BigInteger b("150");
    const BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "-50");
  }

  TEST(BigIntegerTest, SubtractionWithZero) {
    const BigInteger a("789");
    const BigInteger b(0);
    const BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "789");
  }

  TEST(BigIntegerTest, MultiplicationPositive) {
    const BigInteger a("12");
    const BigInteger b("34");
    const BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "408");
  }

  TEST(BigIntegerTest, MultiplicationWithNegative) {
    const BigInteger a("-5");
    const BigInteger b("7");
    const BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "-35");
  }

  TEST(BigIntegerTest, MultiplicationByZero) {
    const BigInteger a("99");
    const BigInteger b(0);
    const BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "0");
  }

  TEST(BigIntegerTest, DivisionExact) {
    const BigInteger a("100");
    const BigInteger b("25");
    const BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "4");
  }

  TEST(BigIntegerTest, DivisionWithRemainder) {
    const BigInteger a("10");
    const BigInteger b("3");
    const BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "3");
  }

  TEST(BigIntegerTest, DivisionByNegative) {
    const BigInteger a("50");
    const BigInteger b("-5");
    const BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "-10");
  }

  TEST(BigIntegerTest, DivisionByZeroThrowsException) {
    const BigInteger a("10");
    const BigInteger b("0");
    EXPECT_THROW({ a / b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, ModuloPositiveNumbers) {
    const BigInteger a("10");
    const BigInteger b("3");
    const BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "1");
  }

  TEST(BigIntegerTest, ModuloNegativeDividend) {
    const BigInteger a("-10");
    const BigInteger b("3");
    const BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "-1");
  }

  TEST(BigIntegerTest, ModuloByZeroThrowsException) {
    const BigInteger a("5");
    const BigInteger b("0");
    EXPECT_THROW({ a % b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, EqualityOperatorTrue) {
    const BigInteger a("123");
    const BigInteger b("123");
    EXPECT_TRUE(a == b);
  }

  TEST(BigIntegerTest, EqualityOperatorFalse) {
    const BigInteger a("123");
    const BigInteger b("456");
    EXPECT_FALSE(a == b);
  }

  TEST(BigIntegerTest, InequalityOperatorTrue) {
    const BigInteger a("789");
    const BigInteger b("987");
    EXPECT_TRUE(a != b);
  }

  TEST(BigIntegerTest, InequalityOperatorFalse) {
    const BigInteger a("555");
    const BigInteger b("555");
    EXPECT_FALSE(a != b);
  }

  TEST(BigIntegerTest, LessThanOperatorTrue) {
    const BigInteger a("100");
    const BigInteger b("200");
    EXPECT_TRUE(a < b);
  }

  TEST(BigIntegerTest, LessThanOperatorFalse) {
    const BigInteger a("500");
    const BigInteger b("300");
    EXPECT_FALSE(a < b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual) {
    const BigInteger a("42");
    const BigInteger b("42");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess) {
    const BigInteger a("-5");
    const BigInteger b("5");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorTrue) {
    const BigInteger a("999");
    const BigInteger b("123");
    EXPECT_TRUE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorFalse) {
    const BigInteger a("123");
    const BigInteger b("999");
    EXPECT_FALSE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual) {
    const BigInteger a("0");
    const BigInteger b("0");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater) {
    const BigInteger a("100");
    const BigInteger b("-100");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, ToStringCanBeConvertedBack) {
    const BigInteger original("1234567890");
    const std::string str = original.toString();
    const BigInteger copied(str);
    EXPECT_EQ(copied.toString(), "1234567890");
  }

  TEST(BigIntegerTest, FromStringHandlesNegative) {
    const BigInteger bigInt = BigInteger::fromString("-456");
    EXPECT_EQ(bigInt.toString(), "-456");
  }

  TEST(BigIntegerTest, FromIntHandlesLargePositive) {
    const BigInteger bigInt = BigInteger::fromInt(9223372036854775807LL);
    EXPECT_EQ(bigInt.toString(), "9223372036854775807");
  }

  TEST(BigIntegerTest, FromIntHandlesLargeNegative) {
    const BigInteger bigInt = BigInteger::fromInt(-9223372036854775807LL - 1);
    EXPECT_EQ(bigInt.toString(), "-9223372036854775808");
  }
}
