#include <stdexcept>
#include <entity/base_type/BigDecimal.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BigDecimalTest, ConstructFromString) {
    const framework::entity::base_type::BigDecimal num("123.45");
    EXPECT_EQ(num.toString(), "123.45");
  }

  TEST(BigDecimalTest, ConstructFromDouble) {
    const framework::entity::base_type::BigDecimal num(2.5);
    EXPECT_EQ(num.toString(), "2.5");
  }

  TEST(BigDecimalTest, AddTwoPositiveNumbers) {
    const framework::entity::base_type::BigDecimal a("123.45");
    const framework::entity::base_type::BigDecimal b("67.89");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "191.34");
  }

  TEST(BigDecimalTest, AddNegativeAndPositive) {
    const framework::entity::base_type::BigDecimal a("-10.5");
    const framework::entity::base_type::BigDecimal b("5.0");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "-5.5");
  }

  TEST(BigDecimalTest, AddZeros) {
    const framework::entity::base_type::BigDecimal a("0.0");
    const framework::entity::base_type::BigDecimal b("0.0");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "0");
  }

  TEST(BigDecimalTest, SubtractPositiveNumbers) {
    const framework::entity::base_type::BigDecimal a("100.0");
    const framework::entity::base_type::BigDecimal b("50.5");
    const framework::entity::base_type::BigDecimal result = a - b;
    EXPECT_EQ(result.toString(), "49.5");
  }

  TEST(BigDecimalTest, SubtractResultNegative) {
    const framework::entity::base_type::BigDecimal a("3.0");
    const framework::entity::base_type::BigDecimal b("5.0");
    const framework::entity::base_type::BigDecimal result = a - b;
    EXPECT_EQ(result.toString(), "-2");
  }

  TEST(BigDecimalTest, MultiplyPositiveNumbers) {
    const framework::entity::base_type::BigDecimal a("12.5");
    const framework::entity::base_type::BigDecimal b("8.0");
    const framework::entity::base_type::BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "100");
  }

  TEST(BigDecimalTest, MultiplyNegativeAndPositive) {
    const framework::entity::base_type::BigDecimal a("-3.0");
    const framework::entity::base_type::BigDecimal b("4.0");
    const framework::entity::base_type::BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "-12");
  }

  TEST(BigDecimalTest, MultiplyByZero) {
    const framework::entity::base_type::BigDecimal a("123.45");
    const framework::entity::base_type::BigDecimal b("0.0");
    const framework::entity::base_type::BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "0");
  }

  TEST(BigDecimalTest, DivideEvenly) {
    const framework::entity::base_type::BigDecimal a("100.0");
    const framework::entity::base_type::BigDecimal b("4.0");
    const framework::entity::base_type::BigDecimal result = a / b;
    EXPECT_EQ(result.toString(), "25");
  }

  TEST(BigDecimalTest, DivideWithFraction) {
    const framework::entity::base_type::BigDecimal a("1.0");
    const framework::entity::base_type::BigDecimal b("3.0");
    const framework::entity::base_type::BigDecimal result = a / b;
    EXPECT_EQ(result.toString().substr(0, 17), "0.333333333333333");
  }

  TEST(BigDecimalTest, DivideByZeroThrowsException) {
    const framework::entity::base_type::BigDecimal a("10.0");
    const framework::entity::base_type::BigDecimal b("0.0");
    EXPECT_THROW(
      {
      try {
      a / b;
      }
      catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Division by zero is not allowed.");
      throw;
      }
      }, std::invalid_argument);
  }

  TEST(BigDecimalTest, EqualityOperators) {
    const framework::entity::base_type::BigDecimal a("5.0");
    const framework::entity::base_type::BigDecimal b("5.0");
    const framework::entity::base_type::BigDecimal c("3.0");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  }

  TEST(BigDecimalTest, RelationalOperators) {
    const framework::entity::base_type::BigDecimal a("10.0");
    const framework::entity::base_type::BigDecimal b("5.0");
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
    EXPECT_FALSE(b > a);
  }

  TEST(BigDecimalTest, ToStringReturnsCorrectValue) {
    const framework::entity::base_type::BigDecimal num("987.654");
    EXPECT_EQ(num.toString(), "987.654");
  }

  TEST(BigDecimalTest, NegativeNumberOperations) {
    const framework::entity::base_type::BigDecimal a("-10.5");
    const framework::entity::base_type::BigDecimal b("5.0");
    EXPECT_EQ((a + b).toString(), "-5.5");
    EXPECT_EQ((a - b).toString(), "-15.5");
    EXPECT_EQ((a * b).toString(), "-52.5");
    EXPECT_EQ((a / b).toString(), "-2.1");
  }

  TEST(BigDecimalTest, ZeroOperations) {
    const framework::entity::base_type::BigDecimal zero("0.0");
    const framework::entity::base_type::BigDecimal a("5.0");
    EXPECT_EQ((zero + a).toString(), "5");
    EXPECT_EQ((zero - a).toString(), "-5");
    EXPECT_EQ((zero * a).toString(), "0");
    EXPECT_THROW(zero / zero, std::invalid_argument);
  }
} // namespace gtest_case
