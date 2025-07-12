#include <stdexcept>
#include <string>
#include <gtest/gtest.h>

#include "type/base_type/Boolean.hpp"

namespace gtest_case
{
    TEST(BooleanTest, DefaultConstructor)
    {
        const coco::Boolean boolean;
        EXPECT_FALSE(static_cast<bool>(boolean));
    }

    TEST(BooleanTest, ValueConstructor)
    {
        const coco::Boolean trueBool(true);
        const coco::Boolean falseBool(false);
        EXPECT_TRUE(static_cast<bool>(trueBool));
        EXPECT_FALSE(static_cast<bool>(falseBool));
    }

    TEST(BooleanTest, CopyConstructor)
    {
        const coco::Boolean original(true);
        const coco::Boolean copy(original);
        EXPECT_TRUE(static_cast<bool>(copy));
    }

    TEST(BooleanTest, MoveConstructor)
    {
        coco::Boolean original(true);
        const coco::Boolean moved(std::move(original));
        EXPECT_TRUE(static_cast<bool>(moved));
    }

    TEST(BooleanTest, CopyAssignment)
    {
        const coco::Boolean original(false);
        const coco::Boolean target = original;
        EXPECT_FALSE(static_cast<bool>(target));
    }

    TEST(BooleanTest, MoveAssignment)
    {
        coco::Boolean original(true);
        const coco::Boolean target = std::move(original);
        EXPECT_TRUE(static_cast<bool>(target));
    }

    TEST(BooleanTest, SelfAssignment)
    {
        coco::Boolean boolean(true);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        boolean = boolean;
        EXPECT_TRUE(static_cast<bool>(boolean));
    }

    TEST(BooleanTest, ParseBooleanTrue)
    {
        const coco::Boolean result = coco::Boolean::parseBoolean("true");
        EXPECT_TRUE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanUpperCase)
    {
        const coco::Boolean result = coco::Boolean::parseBoolean("TRUE");
        EXPECT_TRUE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanFalse)
    {
        const coco::Boolean result = coco::Boolean::parseBoolean("false");
        EXPECT_FALSE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanInvalidInput)
    {
        ASSERT_THROW(coco::Boolean::parseBoolean("invalid"), std::invalid_argument);
    }

    TEST(BooleanTest, BooleanTypeConversion)
    {
        const coco::Boolean trueBool(true);
        const coco::Boolean falseBool(false);
        EXPECT_TRUE(static_cast<bool>(trueBool));
        EXPECT_FALSE(static_cast<bool>(falseBool));
    }

    TEST(BooleanTest, BooleanValueMethod)
    {
        const coco::Boolean trueBool(true);
        const coco::Boolean falseBool(false);
        EXPECT_TRUE(trueBool.booleanValue());
        EXPECT_FALSE(falseBool.booleanValue());
    }

    TEST(BooleanTest, SpaceshipOperator)
    {
        const coco::Boolean trueBool(true);
        const coco::Boolean falseBool(false);
        EXPECT_EQ(trueBool <=> trueBool, std::partial_ordering::equivalent);
        EXPECT_EQ(trueBool <=> falseBool, std::partial_ordering::greater);
        EXPECT_EQ(falseBool <=> trueBool, std::partial_ordering::less);
    }

    TEST(BooleanTest, EqualityOperator)
    {
        const coco::Boolean bool1(true);
        const coco::Boolean bool2(true);
        const coco::Boolean bool3(false);
        EXPECT_TRUE(bool1 == bool2);
        EXPECT_FALSE(bool1 == bool3);
    }

    TEST(BooleanTest, StaticConstants)
    {
        EXPECT_TRUE(coco::True.booleanValue());
        EXPECT_FALSE(coco::False.booleanValue());
    }

    TEST(BooleanTest, HashCodeDifferentiation)
    {
        const size_t trueHash = coco::True.hashCode();
        const size_t falseHash = coco::False.hashCode();
        EXPECT_NE(trueHash, falseHash);
    }

    TEST(BooleanTest, ToStringFormat)
    {
        const coco::Boolean trueBool(true);
        const coco::Boolean falseBool(false);
        EXPECT_EQ(trueBool.toString(), "class coco::Boolean{1}");
        EXPECT_EQ(falseBool.toString(), "class coco::Boolean{0}");
    }
}
