#include <type/base_type/Float.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(FloatTest, ConstructorInitializesValueCorrectly)
    {
        const coco::Float f(3.14f);
        EXPECT_EQ(f.floatValue(), 3.14f);
    }

    TEST(FloatTest, CopyConstructorWorks)
    {
        const coco::Float f1(2.5f);
        const coco::Float f2(f1);
        EXPECT_EQ(f1.floatValue(), f2.floatValue());
    }

    TEST(FloatTest, MoveConstructorWorks)
    {
        coco::Float f1(2.5f);
        const coco::Float f2(std::move(f1));
        EXPECT_EQ(f2.floatValue(), 2.5f);
    }

    TEST(FloatTest, CopyAssignmentWorks)
    {
        const coco::Float f1(1.0f);
        coco::Float f2(0.0f);
        f2 = f1;
        EXPECT_EQ(f1.floatValue(), f2.floatValue());
    }

    TEST(FloatTest, MoveAssignmentWorks)
    {
        coco::Float f1(1.0f);
        coco::Float f2(0.0f);
        f2 = std::move(f1);
        EXPECT_EQ(f2.floatValue(), 1.0f);
    }

    TEST(FloatTest, HashCodeReturnsSameForEqualValues)
    {
        const coco::Float f1(2.5f);
        const coco::Float f2(2.5f);
        EXPECT_EQ(f1.hashCode(), f2.hashCode());
    }

    TEST(FloatTest, ToStringReturnsValidString)
    {
        const coco::Float f(3.14f);
        EXPECT_FALSE(f.toString().empty());
    }

    TEST(FloatTest, TypeConversionWorks)
    {
        const coco::Float f(4.2f);
        const float value = static_cast<float>(f);
        EXPECT_FLOAT_EQ(value, 4.2f);
    }

    TEST(FloatTest, ParseValidString)
    {
        const auto result = coco::Float::parseFloat("123.45");
        EXPECT_FLOAT_EQ(result.floatValue(), 123.45f);
    }

    TEST(FloatTest, ParseInvalidStringThrows)
    {
        EXPECT_THROW(coco::Float::parseFloat("abc"), std::invalid_argument);
    }

    TEST(FloatTest, ParseOutOfRangeStringThrows)
    {
        EXPECT_THROW(coco::Float::parseFloat("1e10000"), std::out_of_range);
    }

    TEST(FloatTest, EqualityOperatorWorks)
    {
        const coco::Float f1(5.0f);
        const coco::Float f2(5.0f);
        EXPECT_TRUE(f1 == f2);
    }

    TEST(FloatTest, InequalityOperatorWorks)
    {
        const coco::Float f1(5.0f);
        const coco::Float f2(6.0f);
        EXPECT_TRUE(f1 != f2);
    }

    TEST(FloatTest, ThreeWayComparisonWorks)
    {
        const coco::Float f1(3.0f);
        const coco::Float f2(4.0f);
        EXPECT_TRUE(f1 <=> f2 == std::partial_ordering::less);
    }

    TEST(FloatTest, ArithmeticOperatorsWorkCorrectly)
    {
        const coco::Float f1(2.0f);
        const coco::Float f2(3.0f);
        EXPECT_FLOAT_EQ((f1 + f2).floatValue(), 5.0f);
        EXPECT_FLOAT_EQ((f1 - f2).floatValue(), -1.0f);
        EXPECT_FLOAT_EQ((f1 * f2).floatValue(), 6.0f);
    }

    TEST(FloatTest, DivisionByZeroThrowsOverflowError)
    {
        const coco::Float f1(6.0f);
        const coco::Float f2(0.0f);
        EXPECT_THROW(f1 / f2, std::overflow_error);
    }

    TEST(FloatTest, NaNComparisonBehavesCorrectly)
    {
        const coco::Float f1(coco::Float::NaN);
        const coco::Float f2(coco::Float::NaN);
        EXPECT_FALSE(f1 == f2);
        EXPECT_TRUE((f1 <=> f2) == std::partial_ordering::unordered);
    }

    TEST(FloatTest, InfinityValuesAreCorrect)
    {
        EXPECT_GT(coco::Float::POSITIVE_INFINITY, std::numeric_limits<float>::max());
        EXPECT_LT(coco::Float::NEGATIVE_INFINITY, -std::numeric_limits<float>::max());
    }
}
