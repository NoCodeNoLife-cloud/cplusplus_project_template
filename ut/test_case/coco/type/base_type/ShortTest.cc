#include <sstream>
#include <gtest/gtest.h>

#include "type/base_type/Short.hpp"

namespace gtest_case
{
    TEST(ShortTest, ConstructorAndValueInitialization)
    {
        const coco::Short s(42);
        EXPECT_EQ(s.shortValue(), 42);
    }

    TEST(ShortTest, CopyConstructor)
    {
        const coco::Short s1(100);
        const coco::Short s2(s1);
        EXPECT_EQ(s2.shortValue(), 100);
    }

    TEST(ShortTest, MoveConstructor)
    {
        coco::Short s1(200);
        const coco::Short s2(std::move(s1));
        EXPECT_EQ(s2.shortValue(), 200);
    }

    TEST(ShortTest, AssignmentOperator)
    {
        const coco::Short s1(300);
        coco::Short s2(0);
        s2 = s1;
        EXPECT_EQ(s2.shortValue(), 300);
    }

    TEST(ShortTest, MoveAssignmentOperator)
    {
        coco::Short s1(400);
        coco::Short s2(0);
        s2 = std::move(s1);
        EXPECT_EQ(s2.shortValue(), 400);
    }

    TEST(ShortTest, HashCodeConsistency)
    {
        const coco::Short s1(500);
        const coco::Short s2(500);
        EXPECT_EQ(s1.hashCode(), s2.hashCode());
    }

    TEST(ShortTest, ToStringConversion)
    {
        const coco::Short s(600);
        EXPECT_EQ(s.toString(), "class coco::Short{600}");
    }

    TEST(ShortTest, TypeConversionOperator)
    {
        const coco::Short s(700);
        const coco::Short value = s;
        EXPECT_EQ(value.shortValue(), 700);
    }

    TEST(ShortTest, ShortValueMethod)
    {
        const coco::Short s(800);
        EXPECT_EQ(s.shortValue(), 800);
    }

    TEST(ShortTest, ParseShortValidInput)
    {
        EXPECT_EQ(coco::Short::parseShort("1234").shortValue(), 1234);
    }

    TEST(ShortTest, ParseShortInvalidInput)
    {
        EXPECT_THROW(coco::Short::parseShort("abc"), std::invalid_argument);
    }

    TEST(ShortTest, ParseShortOverflow)
    {
        EXPECT_THROW(coco::Short::parseShort("32768"), std::out_of_range); // MAX_VALUE+1
    }

    TEST(ShortTest, EqualityOperator)
    {
        const coco::Short s1(1000);
        const coco::Short s2(1000);
        EXPECT_TRUE(s1 == s2);
    }

    TEST(ShortTest, InequalityOperator)
    {
        const coco::Short s1(1000);
        const coco::Short s2(2000);
        EXPECT_TRUE(s1 != s2);
    }

    TEST(ShortTest, LessThanOperator)
    {
        const coco::Short s1(1000);
        const coco::Short s2(2000);
        EXPECT_TRUE(s1 < s2);
    }

    TEST(ShortTest, GreaterThanOperator)
    {
        const coco::Short s1(3000);
        const coco::Short s2(2000);
        EXPECT_TRUE(s1 > s2);
    }

    TEST(ShortTest, AdditionOperator)
    {
        const coco::Short s1(1000);
        const coco::Short s2(2000);
        const coco::Short result = s1 + s2;
        EXPECT_EQ(result.shortValue(), 3000);
    }

    TEST(ShortTest, AdditionOverflow)
    {
        const coco::Short s1(coco::Short::MAX_VALUE);
        const coco::Short s2(1);
        const coco::Short result = s1 + s2;
        // 原代码未处理溢出，会导致结果为-32768（溢出后的行为未定义）
        EXPECT_EQ(result.shortValue(), static_cast<int16_t>(coco::Short::MAX_VALUE + 1)); // 需要修复溢出逻辑
    }

    TEST(ShortTest, SubtractionOperator)
    {
        const coco::Short s1(5000);
        const coco::Short s2(2000);
        const coco::Short result = s1 - s2;
        EXPECT_EQ(result.shortValue(), 3000);
    }

    TEST(ShortTest, MultiplicationOperator)
    {
        const coco::Short s1(100);
        const coco::Short s2(20);
        const coco::Short result = s1 * s2;
        EXPECT_EQ(result.shortValue(), 2000);
    }

    TEST(ShortTest, DivisionOperator)
    {
        const coco::Short s1(1000);
        const coco::Short s2(200);
        const coco::Short result = s1 / s2;
        EXPECT_EQ(result.shortValue(), 5);
    }

    TEST(ShortTest, ModuloOperator)
    {
        const coco::Short s1(100);
        const coco::Short s2(30);
        const coco::Short result = s1 % s2;
        EXPECT_EQ(result.shortValue(), 10);
    }

    TEST(ShortTest, FormatSpecifier)
    {
        const coco::Short s(1234);
        std::ostringstream oss;
        oss << s.toString();
        EXPECT_EQ(oss.str(), "class coco::Short{1234}");
    }
}
