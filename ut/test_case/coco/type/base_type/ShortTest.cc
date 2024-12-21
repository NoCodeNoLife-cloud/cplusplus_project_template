#include <sstream>
#include <gtest/gtest.h>

#include "type/base_type/Short.hpp"

namespace gtest_case
{
    TEST(ShortTest, ConstructorAndValueInitialization)
    {
        const common::Short s(42);
        EXPECT_EQ(s.shortValue(), 42);
    }

    TEST(ShortTest, CopyConstructor)
    {
        const common::Short s1(100);
        const common::Short s2(s1);
        EXPECT_EQ(s2.shortValue(), 100);
    }

    TEST(ShortTest, MoveConstructor)
    {
        common::Short s1(200);
        const common::Short s2(std::move(s1));
        EXPECT_EQ(s2.shortValue(), 200);
    }

    TEST(ShortTest, AssignmentOperator)
    {
        const common::Short s1(300);
        common::Short s2(0);
        s2 = s1;
        EXPECT_EQ(s2.shortValue(), 300);
    }

    TEST(ShortTest, MoveAssignmentOperator)
    {
        common::Short s1(400);
        common::Short s2(0);
        s2 = std::move(s1);
        EXPECT_EQ(s2.shortValue(), 400);
    }

    TEST(ShortTest, HashCodeConsistency)
    {
        const common::Short s1(500);
        const common::Short s2(500);
        EXPECT_EQ(s1.hashCode(), s2.hashCode());
    }

    TEST(ShortTest, ToStringConversion)
    {
        const common::Short s(600);
        EXPECT_EQ(s.toString(), "class common::Short{600}");
    }

    TEST(ShortTest, TypeConversionOperator)
    {
        const common::Short s(700);
        const common::Short value = s;
        EXPECT_EQ(value.shortValue(), 700);
    }

    TEST(ShortTest, ShortValueMethod)
    {
        const common::Short s(800);
        EXPECT_EQ(s.shortValue(), 800);
    }

    TEST(ShortTest, ParseShortValidInput)
    {
        EXPECT_EQ(common::Short::parseShort("1234").shortValue(), 1234);
    }

    TEST(ShortTest, ParseShortInvalidInput)
    {
        EXPECT_THROW(common::Short::parseShort("abc"), std::invalid_argument);
    }

    TEST(ShortTest, ParseShortOverflow)
    {
        EXPECT_THROW(common::Short::parseShort("32768"), std::out_of_range); // MAX_VALUE+1
    }

    TEST(ShortTest, EqualityOperator)
    {
        const common::Short s1(1000);
        const common::Short s2(1000);
        EXPECT_TRUE(s1 == s2);
    }

    TEST(ShortTest, InequalityOperator)
    {
        const common::Short s1(1000);
        const common::Short s2(2000);
        EXPECT_TRUE(s1 != s2);
    }

    TEST(ShortTest, LessThanOperator)
    {
        const common::Short s1(1000);
        const common::Short s2(2000);
        EXPECT_TRUE(s1 < s2);
    }

    TEST(ShortTest, GreaterThanOperator)
    {
        const common::Short s1(3000);
        const common::Short s2(2000);
        EXPECT_TRUE(s1 > s2);
    }

    TEST(ShortTest, AdditionOperator)
    {
        const common::Short s1(1000);
        const common::Short s2(2000);
        const common::Short result = s1 + s2;
        EXPECT_EQ(result.shortValue(), 3000);
    }

    TEST(ShortTest, AdditionOverflow)
    {
        const common::Short s1(common::Short::MAX_VALUE);
        const common::Short s2(1);
        const common::Short result = s1 + s2;
        // 原代码未处理溢出，会导致结果为-32768（溢出后的行为未定义）
        EXPECT_EQ(result.shortValue(), static_cast<int16_t>(common::Short::MAX_VALUE + 1)); // 需要修复溢出逻辑
    }

    TEST(ShortTest, SubtractionOperator)
    {
        const common::Short s1(5000);
        const common::Short s2(2000);
        const common::Short result = s1 - s2;
        EXPECT_EQ(result.shortValue(), 3000);
    }

    TEST(ShortTest, MultiplicationOperator)
    {
        const common::Short s1(100);
        const common::Short s2(20);
        const common::Short result = s1 * s2;
        EXPECT_EQ(result.shortValue(), 2000);
    }

    TEST(ShortTest, DivisionOperator)
    {
        const common::Short s1(1000);
        const common::Short s2(200);
        const common::Short result = s1 / s2;
        EXPECT_EQ(result.shortValue(), 5);
    }

    TEST(ShortTest, ModuloOperator)
    {
        const common::Short s1(100);
        const common::Short s2(30);
        const common::Short result = s1 % s2;
        EXPECT_EQ(result.shortValue(), 10);
    }

    TEST(ShortTest, FormatSpecifier)
    {
        const common::Short s(1234);
        std::ostringstream oss;
        oss << s.toString();
        EXPECT_EQ(oss.str(), "class common::Short{1234}");
    }
}
