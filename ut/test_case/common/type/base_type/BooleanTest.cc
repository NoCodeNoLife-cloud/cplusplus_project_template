#include <stdexcept>
#include <string>
#include <gtest/gtest.h>

#include "type/base_type/Boolean.hpp"

namespace gtest_case
{
    TEST(BooleanTest, DefaultConstructor)
    {
        const common::Boolean boolean;
        EXPECT_FALSE(static_cast<bool>(boolean));
    }

    TEST(BooleanTest, ValueConstructor)
    {
        const common::Boolean trueBool(true);
        const common::Boolean falseBool(false);
        EXPECT_TRUE(static_cast<bool>(trueBool));
        EXPECT_FALSE(static_cast<bool>(falseBool));
    }

    TEST(BooleanTest, CopyConstructor)
    {
        const common::Boolean original(true);
        const common::Boolean copy(original);
        EXPECT_TRUE(static_cast<bool>(copy));
    }

    TEST(BooleanTest, MoveConstructor)
    {
        common::Boolean original(true);
        const common::Boolean moved(std::move(original));
        EXPECT_TRUE(static_cast<bool>(moved));
    }

    TEST(BooleanTest, CopyAssignment)
    {
        const common::Boolean original(false);
        const common::Boolean target = original;
        EXPECT_FALSE(static_cast<bool>(target));
    }

    TEST(BooleanTest, MoveAssignment)
    {
        common::Boolean original(true);
        const common::Boolean target = std::move(original);
        EXPECT_TRUE(static_cast<bool>(target));
    }

    TEST(BooleanTest, SelfAssignment)
    {
        common::Boolean boolean(true);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        boolean = boolean;
        EXPECT_TRUE(static_cast<bool>(boolean));
    }

    TEST(BooleanTest, ParseBooleanTrue)
    {
        const common::Boolean result = common::Boolean::parseBoolean("true");
        EXPECT_TRUE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanUpperCase)
    {
        const common::Boolean result = common::Boolean::parseBoolean("TRUE");
        EXPECT_TRUE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanFalse)
    {
        const common::Boolean result = common::Boolean::parseBoolean("false");
        EXPECT_FALSE(result.boolValue());
    }

    TEST(BooleanTest, ParseBooleanInvalidInput)
    {
        ASSERT_THROW(common::Boolean::parseBoolean("invalid"), std::invalid_argument);
    }

    TEST(BooleanTest, BooleanTypeConversion)
    {
        const common::Boolean trueBool(true);
        const common::Boolean falseBool(false);
        EXPECT_TRUE(static_cast<bool>(trueBool));
        EXPECT_FALSE(static_cast<bool>(falseBool));
    }

    TEST(BooleanTest, BooleanValueMethod)
    {
        const common::Boolean trueBool(true);
        const common::Boolean falseBool(false);
        EXPECT_TRUE(trueBool.booleanValue());
        EXPECT_FALSE(falseBool.booleanValue());
    }

    TEST(BooleanTest, SpaceshipOperator)
    {
        const common::Boolean trueBool(true);
        const common::Boolean falseBool(false);
        EXPECT_EQ(trueBool <=> trueBool, std::partial_ordering::equivalent);
        EXPECT_EQ(trueBool <=> falseBool, std::partial_ordering::greater);
        EXPECT_EQ(falseBool <=> trueBool, std::partial_ordering::less);
    }

    TEST(BooleanTest, EqualityOperator)
    {
        const common::Boolean bool1(true);
        const common::Boolean bool2(true);
        const common::Boolean bool3(false);
        EXPECT_TRUE(bool1 == bool2);
        EXPECT_FALSE(bool1 == bool3);
    }

    TEST(BooleanTest, StaticConstants)
    {
        EXPECT_TRUE(common::True.booleanValue());
        EXPECT_FALSE(common::False.booleanValue());
    }

    TEST(BooleanTest, HashCodeDifferentiation)
    {
        const size_t trueHash = common::True.hashCode();
        const size_t falseHash = common::False.hashCode();
        EXPECT_NE(trueHash, falseHash);
    }

    TEST(BooleanTest, ToStringFormat)
    {
        const common::Boolean trueBool(true);
        const common::Boolean falseBool(false);
        EXPECT_EQ(trueBool.toString(), "class common::Boolean{1}");
        EXPECT_EQ(falseBool.toString(), "class common::Boolean{0}");
    }
}
