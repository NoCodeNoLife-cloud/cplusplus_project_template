#include <stdexcept>
#include <entity/base_type/BigDecimal.hpp>
#include "gtest/gtest.h"

namespace gtest_case {
  TEST(BigDecimalTest, ConstructorFromString) {
    const framework::entity::base_type::BigDecimal num("123.45");
    EXPECT_EQ(num.toString(), "123.45");
  }

  TEST(BigDecimalTest, ConstructorFromDouble) {
    const framework::entity::base_type::BigDecimal num(123.45);
    EXPECT_EQ(num.toString().substr(0,6), "123.45");
  }

  TEST(BigDecimalTest, Addition) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("3.3");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "8.8");
  }

  TEST(BigDecimalTest, Subtraction) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("3.3");
    const framework::entity::base_type::BigDecimal result = a - b;
    EXPECT_EQ(result.toString(), "2.2");
  }

  TEST(BigDecimalTest, Multiplication) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("2.0");
    const framework::entity::base_type::BigDecimal result = a * b;
    EXPECT_EQ(result.toString(), "11");
  }

  TEST(BigDecimalTest, Division) {
    const framework::entity::base_type::BigDecimal a("10.0");
    const framework::entity::base_type::BigDecimal b("2.0");
    const framework::entity::base_type::BigDecimal result = a / b;
    EXPECT_EQ(result.toString(), "5");
  }

  TEST(BigDecimalTest, DivisionByZero) {
    const framework::entity::base_type::BigDecimal a("10.0");
    const framework::entity::base_type::BigDecimal b("0.0");
    EXPECT_THROW(a / b, std::invalid_argument);
  }

  TEST(BigDecimalTest, EqualityOperator) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("5.5");
    EXPECT_TRUE(a == b);
  }

  TEST(BigDecimalTest, InequalityOperator) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("3.3");
    EXPECT_TRUE(a != b);
  }

  TEST(BigDecimalTest, LessThanOperator) {
    const framework::entity::base_type::BigDecimal a("2.2");
    const framework::entity::base_type::BigDecimal b("3.3");
    EXPECT_TRUE(a < b);
  }

  TEST(BigDecimalTest, GreaterThanOperator) {
    const framework::entity::base_type::BigDecimal a("5.5");
    const framework::entity::base_type::BigDecimal b("3.3");
    EXPECT_TRUE(a > b);
  }

  TEST(BigDecimalTest, ToString) {
    const framework::entity::base_type::BigDecimal num("123.456");
    EXPECT_EQ(num.toString(), "123.456");
  }

  TEST(BigDecimalTest, NegativeNumbers) {
    const framework::entity::base_type::BigDecimal a("-5.5");
    const framework::entity::base_type::BigDecimal b("-3.3");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "-8.8");
  }

  TEST(BigDecimalTest, ZeroHandling) {
    const framework::entity::base_type::BigDecimal a("0.0");
    const framework::entity::base_type::BigDecimal b("5.5");
    EXPECT_TRUE(a < b);
    EXPECT_EQ((b - b).toString(), "0");
  }

  TEST(BigDecimalTest, LargeNumbers) {
    const framework::entity::base_type::BigDecimal a("12345678901234567890.12345");
    const framework::entity::base_type::BigDecimal b("98765432109876543210.98765");
    const framework::entity::base_type::BigDecimal result = a + b;
    EXPECT_EQ(result.toString(), "111111111011111111101.1111");
  }

  TEST(BigDecimalTest, SelfAssignmentOperations) {
    framework::entity::base_type::BigDecimal a("10.0");
    a = a + a;
    EXPECT_EQ(a.toString(), "20");
  }
} // namespace gtest_case
