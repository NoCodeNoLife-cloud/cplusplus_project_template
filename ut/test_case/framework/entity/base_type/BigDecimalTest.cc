#include <stdexcept>
#include <entity/base_type/BigDecimal.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BigDecimalTest, ConstructorFromString) {
    const common::BigDecimal num("123.45");
    EXPECT_EQ(num.toString(), "123.45");
  }

  TEST(BigDecimalTest, ConstructorFromDouble) {
    const common::BigDecimal num(123.45);
    EXPECT_EQ(num.toString().substr(0,6), "123.45");
  }

  TEST(BigDecimalTest, Addition) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("3.3");
    const common::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "8.8");
  }

  TEST(BigDecimalTest, Subtraction) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("3.3");
    const common::BigDecimal result = a - b;
    EXPECT_EQ(result.toString(), "2.2");
  }

  TEST(BigDecimalTest, Multiplication) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("2.0");
    const common::BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "11");
  }

  TEST(BigDecimalTest, Division) {
    const common::BigDecimal a("10.0");
    const common::BigDecimal b("2.0");
    const common::BigDecimal result = a / b;
    EXPECT_EQ(result.toString(), "5");
  }

  TEST(BigDecimalTest, DivisionByZero) {
    const common::BigDecimal a("10.0");
    const common::BigDecimal b("0.0");
    EXPECT_THROW(a / b, std::invalid_argument);
  }

  TEST(BigDecimalTest, EqualityOperator) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("5.5");
    EXPECT_TRUE(std::is_eq(a <=> b));
  }

  TEST(BigDecimalTest, InequalityOperator) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("3.3");
    EXPECT_TRUE(std::is_neq(a <=> b));
  }

  TEST(BigDecimalTest, LessThanOperator) {
    const common::BigDecimal a("2.2");
    const common::BigDecimal b("3.3");
    EXPECT_TRUE(a < b);
  }

  TEST(BigDecimalTest, GreaterThanOperator) {
    const common::BigDecimal a("5.5");
    const common::BigDecimal b("3.3");
    EXPECT_TRUE(a > b);
  }

  TEST(BigDecimalTest, ToString) {
    const common::BigDecimal num("123.456");
    EXPECT_EQ(num.toString(), "123.456");
  }

  TEST(BigDecimalTest, NegativeNumbers) {
    const common::BigDecimal a("-5.5");
    const common::BigDecimal b("-3.3");
    const common::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "-8.8");
  }

  TEST(BigDecimalTest, ZeroHandling) {
    const common::BigDecimal a("0.0");
    const common::BigDecimal b("5.5");
    EXPECT_TRUE(a < b);
    EXPECT_EQ((b - b).toString(), "0");
  }

  TEST(BigDecimalTest, LargeNumbers) {
    const common::BigDecimal a("12345678901234567890.12345");
    const common::BigDecimal b("98765432109876543210.98765");
    const common::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "111111111011111111101.1111");
  }

  TEST(BigDecimalTest, SelfAssignmentOperations) {
    common::BigDecimal a("10.0");
    a = a + a;
    EXPECT_EQ(a.toString(), "20");
  }
}
