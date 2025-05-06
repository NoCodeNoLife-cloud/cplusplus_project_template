#include <stdexcept>
#include <entity/base_type/BigDecimal.hpp>
#include <gtest/gtest.h>
using framework::BigDecimal;

namespace gtest_case {
  TEST(BigDecimalTest, ConstructorFromString) {
    const BigDecimal num("123.45");
    EXPECT_EQ(num.toString(), "123.45");
  }

  TEST(BigDecimalTest, ConstructorFromDouble) {
    const BigDecimal num(123.45);
    EXPECT_EQ(num.toString().substr(0,6), "123.45");
  }

  TEST(BigDecimalTest, Addition) {
    const BigDecimal a("5.5");
    const BigDecimal b("3.3");
    const BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "8.8");
  }

  TEST(BigDecimalTest, Subtraction) {
    const BigDecimal a("5.5");
    const BigDecimal b("3.3");
    const BigDecimal result = a - b;
    EXPECT_EQ(result.toString(), "2.2");
  }

  TEST(BigDecimalTest, Multiplication) {
    const BigDecimal a("5.5");
    const BigDecimal b("2.0");
    const BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "11");
  }

  TEST(BigDecimalTest, Division) {
    const BigDecimal a("10.0");
    const BigDecimal b("2.0");
    const BigDecimal result = a / b;
    EXPECT_EQ(result.toString(), "5");
  }

  TEST(BigDecimalTest, DivisionByZero) {
    const BigDecimal a("10.0");
    const BigDecimal b("0.0");
    EXPECT_THROW(a / b, std::invalid_argument);
  }

  TEST(BigDecimalTest, EqualityOperator) {
    const BigDecimal a("5.5");
    const BigDecimal b("5.5");
    EXPECT_TRUE(a == b);
  }

  TEST(BigDecimalTest, InequalityOperator) {
    const BigDecimal a("5.5");
    const BigDecimal b("3.3");
    EXPECT_TRUE(a != b);
  }

  TEST(BigDecimalTest, LessThanOperator) {
    const BigDecimal a("2.2");
    const BigDecimal b("3.3");
    EXPECT_TRUE(a < b);
  }

  TEST(BigDecimalTest, GreaterThanOperator) {
    const BigDecimal a("5.5");
    const BigDecimal b("3.3");
    EXPECT_TRUE(a > b);
  }

  TEST(BigDecimalTest, ToString) {
    const BigDecimal num("123.456");
    EXPECT_EQ(num.toString(), "123.456");
  }

  TEST(BigDecimalTest, NegativeNumbers) {
    const BigDecimal a("-5.5");
    const BigDecimal b("-3.3");
    const BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "-8.8");
  }

  TEST(BigDecimalTest, ZeroHandling) {
    const BigDecimal a("0.0");
    const BigDecimal b("5.5");
    EXPECT_TRUE(a < b);
    EXPECT_EQ((b - b).toString(), "0");
  }

  TEST(BigDecimalTest, LargeNumbers) {
    const BigDecimal a("12345678901234567890.12345");
    const BigDecimal b("98765432109876543210.98765");
    const BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "111111111011111111101.1111");
  }

  TEST(BigDecimalTest, SelfAssignmentOperations) {
    BigDecimal a("10.0");
    a = a + a;
    EXPECT_EQ(a.toString(), "20");
  }
}
