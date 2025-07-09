#include <stdexcept>
#include <type/base_type/BigDecimal.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(BigDecimalTest, DivisionByZero)
    {
        const coco::BigDecimal a("10.0");
        const coco::BigDecimal b("0.0");
        EXPECT_THROW(a / b, std::invalid_argument);
    }

    TEST(BigDecimalTest, EqualityOperator)
    {
        const coco::BigDecimal a("5.5");
        const coco::BigDecimal b("5.5");
        EXPECT_TRUE(std::is_eq(a <=> b));
    }

    TEST(BigDecimalTest, InequalityOperator)
    {
        const coco::BigDecimal a("5.5");
        const coco::BigDecimal b("3.3");
        EXPECT_TRUE(std::is_neq(a <=> b));
    }

    TEST(BigDecimalTest, LessThanOperator)
    {
        const coco::BigDecimal a("2.2");
        const coco::BigDecimal b("3.3");
        EXPECT_TRUE(a < b);
    }

    TEST(BigDecimalTest, GreaterThanOperator)
    {
        const coco::BigDecimal a("5.5");
        const coco::BigDecimal b("3.3");
        EXPECT_TRUE(a > b);
    }
}
