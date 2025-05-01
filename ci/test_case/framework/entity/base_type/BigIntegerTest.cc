#include <entity/base_type/BigInteger.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BigIntegerTest, DefaultConstructorInitializesToZero) {
    const framework::entity::base_type::BigInteger bigInt;
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, StringConstructorWithPositiveNumber) {
    const framework::entity::base_type::BigInteger bigInt("12345");
    EXPECT_EQ(bigInt.toString(), "12345");
  }

  TEST(BigIntegerTest, StringConstructorWithNegativeNumber) {
    const framework::entity::base_type::BigInteger bigInt("-6789");
    EXPECT_EQ(bigInt.toString(), "-6789");
  }

  TEST(BigIntegerTest, StringConstructorWithZero) {
    const framework::entity::base_type::BigInteger bigInt("0");
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, IntConstructorWithPositive) {
    const framework::entity::base_type::BigInteger bigInt(42);
    EXPECT_EQ(bigInt.toString(), "42");
  }

  TEST(BigIntegerTest, IntConstructorWithNegative) {
    const framework::entity::base_type::BigInteger bigInt(-15);
    EXPECT_EQ(bigInt.toString(), "-15");
  }

  TEST(BigIntegerTest, IntConstructorWithZero) {
    const framework::entity::base_type::BigInteger bigInt(0);
    EXPECT_EQ(bigInt.toString(), "0");
  }

  TEST(BigIntegerTest, AdditionPositiveNumbers) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("200");
    const framework::entity::base_type::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, AdditionNegativeAndPositive) {
    const framework::entity::base_type::BigInteger a("-50");
    const framework::entity::base_type::BigInteger b("30");
    const framework::entity::base_type::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "-20");
  }

  TEST(BigIntegerTest, AdditionWithZero) {
    const framework::entity::base_type::BigInteger a("123");
    const framework::entity::base_type::BigInteger b(0);
    const framework::entity::base_type::BigInteger result = a + b;
    EXPECT_EQ(result.toString(), "123");
  }

  TEST(BigIntegerTest, SubtractionPositiveResult) {
    const framework::entity::base_type::BigInteger a("500");
    const framework::entity::base_type::BigInteger b("200");
    const framework::entity::base_type::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "300");
  }

  TEST(BigIntegerTest, SubtractionNegativeResult) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("150");
    const framework::entity::base_type::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "-50");
  }

  TEST(BigIntegerTest, SubtractionWithZero) {
    const framework::entity::base_type::BigInteger a("789");
    const framework::entity::base_type::BigInteger b(0);
    const framework::entity::base_type::BigInteger result = a - b;
    EXPECT_EQ(result.toString(), "789");
  }

  TEST(BigIntegerTest, MultiplicationPositive) {
    const framework::entity::base_type::BigInteger a("12");
    const framework::entity::base_type::BigInteger b("34");
    const framework::entity::base_type::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "408");
  }

  TEST(BigIntegerTest, MultiplicationWithNegative) {
    const framework::entity::base_type::BigInteger a("-5");
    const framework::entity::base_type::BigInteger b("7");
    const framework::entity::base_type::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "-35");
  }

  TEST(BigIntegerTest, MultiplicationByZero) {
    const framework::entity::base_type::BigInteger a("99");
    const framework::entity::base_type::BigInteger b(0);
    const framework::entity::base_type::BigInteger result = a * b;
    EXPECT_EQ(result.toString(), "0");
  }

  TEST(BigIntegerTest, DivisionExact) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("25");
    const framework::entity::base_type::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "4");
  }

  TEST(BigIntegerTest, DivisionWithRemainder) {
    const framework::entity::base_type::BigInteger a("10");
    const framework::entity::base_type::BigInteger b("3");
    const framework::entity::base_type::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "3");
  }

  TEST(BigIntegerTest, DivisionByNegative) {
    const framework::entity::base_type::BigInteger a("50");
    const framework::entity::base_type::BigInteger b("-5");
    const framework::entity::base_type::BigInteger result = a / b;
    EXPECT_EQ(result.toString(), "-10");
  }

  TEST(BigIntegerTest, DivisionByZeroThrowsException) {
    const framework::entity::base_type::BigInteger a("10");
    const framework::entity::base_type::BigInteger b("0");
    EXPECT_THROW({ a / b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, ModuloPositiveNumbers) {
    const framework::entity::base_type::BigInteger a("10");
    const framework::entity::base_type::BigInteger b("3");
    const framework::entity::base_type::BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "1");
  }

  TEST(BigIntegerTest, ModuloNegativeDividend) {
    const framework::entity::base_type::BigInteger a("-10");
    const framework::entity::base_type::BigInteger b("3");
    const framework::entity::base_type::BigInteger result = a % b;
    EXPECT_EQ(result.toString(), "-1");
  }

  TEST(BigIntegerTest, ModuloByZeroThrowsException) {
    const framework::entity::base_type::BigInteger a("5");
    const framework::entity::base_type::BigInteger b("0");
    EXPECT_THROW({ a % b; }, std::invalid_argument);
  }

  TEST(BigIntegerTest, EqualityOperatorTrue) {
    const framework::entity::base_type::BigInteger a("123");
    const framework::entity::base_type::BigInteger b("123");
    EXPECT_TRUE(a == b);
  }

  TEST(BigIntegerTest, EqualityOperatorFalse) {
    const framework::entity::base_type::BigInteger a("123");
    const framework::entity::base_type::BigInteger b("456");
    EXPECT_FALSE(a == b);
  }

  TEST(BigIntegerTest, InequalityOperatorTrue) {
    const framework::entity::base_type::BigInteger a("789");
    const framework::entity::base_type::BigInteger b("987");
    EXPECT_TRUE(a != b);
  }

  TEST(BigIntegerTest, InequalityOperatorFalse) {
    const framework::entity::base_type::BigInteger a("555");
    const framework::entity::base_type::BigInteger b("555");
    EXPECT_FALSE(a != b);
  }

  TEST(BigIntegerTest, LessThanOperatorTrue) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("200");
    EXPECT_TRUE(a < b);
  }

  TEST(BigIntegerTest, LessThanOperatorFalse) {
    const framework::entity::base_type::BigInteger a("500");
    const framework::entity::base_type::BigInteger b("300");
    EXPECT_FALSE(a < b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueEqual) {
    const framework::entity::base_type::BigInteger a("42");
    const framework::entity::base_type::BigInteger b("42");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, LessThanOrEqualOperatorTrueLess) {
    const framework::entity::base_type::BigInteger a("-5");
    const framework::entity::base_type::BigInteger b("5");
    EXPECT_TRUE(a <= b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorTrue) {
    const framework::entity::base_type::BigInteger a("999");
    const framework::entity::base_type::BigInteger b("123");
    EXPECT_TRUE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOperatorFalse) {
    const framework::entity::base_type::BigInteger a("123");
    const framework::entity::base_type::BigInteger b("999");
    EXPECT_FALSE(a > b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueEqual) {
    const framework::entity::base_type::BigInteger a("0");
    const framework::entity::base_type::BigInteger b("0");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, GreaterThanOrEqualOperatorTrueGreater) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("-100");
    EXPECT_TRUE(a >= b);
  }

  TEST(BigIntegerTest, ToStringCanBeConvertedBack) {
    const framework::entity::base_type::BigInteger original("1234567890");
    std::string str = original.toString();
    const framework::entity::base_type::BigInteger copied(str);
    EXPECT_EQ(copied.toString(), "1234567890");
  }

  TEST(BigIntegerTest, FromStringHandlesNegative) {
    const framework::entity::base_type::BigInteger bigInt = framework::entity::base_type::BigInteger::fromString("-456");
    EXPECT_EQ(bigInt.toString(), "-456");
  }

  TEST(BigIntegerTest, FromIntHandlesLargePositive) {
    const framework::entity::base_type::BigInteger bigInt = framework::entity::base_type::BigInteger::fromInt(9223372036854775807LL);
    EXPECT_EQ(bigInt.toString(), "9223372036854775807");
  }

  TEST(BigIntegerTest, FromIntHandlesLargeNegative) {
    const framework::entity::base_type::BigInteger bigInt = framework::entity::base_type::BigInteger::fromInt(-9223372036854775807LL - 1);
    EXPECT_EQ(bigInt.toString(), "-9223372036854775808");
  }
} // namespace gtest_case
