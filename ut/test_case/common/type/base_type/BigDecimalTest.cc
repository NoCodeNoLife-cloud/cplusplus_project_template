#include <gtest/gtest.h>

#include <stdexcept>

#include "type/base_type/BigDecimal.hpp"

namespace gtest_case {
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
}  // namespace gtest_case
