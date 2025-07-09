#include <stdexcept>
#include <type/base_type/Byte.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(ByteTest, DefaultConstructorInitializesToZero)
    {
        const coco::Byte b;
        EXPECT_EQ(b.byteValue(), 0);
    }

    TEST(ByteTest, ParameterizedConstructorSetsValue)
    {
        const coco::Byte b(100);
        EXPECT_EQ(b.byteValue(), 100);
    }

    TEST(ByteTest, CopyConstructorCopiesValue)
    {
        const coco::Byte b1(50);
        const coco::Byte b2 = b1;
        EXPECT_EQ(b2.byteValue(), 50);
    }

    TEST(ByteTest, MoveConstructorTransfersValue)
    {
        coco::Byte b1(50);
        const coco::Byte b2 = std::move(b1);
        EXPECT_EQ(b2.byteValue(), 50);
    }

    TEST(ByteTest, CopyAssignmentCopiesValue)
    {
        const coco::Byte b1(50);
        const coco::Byte b2 = b1;
        EXPECT_EQ(b2.byteValue(), 50);
    }

    TEST(ByteTest, MoveAssignmentTransfersValue)
    {
        coco::Byte b1(50);
        const coco::Byte b2 = std::move(b1);
        EXPECT_EQ(b2.byteValue(), 50);
    }

    TEST(ByteTest, HashCodeSameForEqualObjects)
    {
        const coco::Byte b1(10);
        const coco::Byte b2(10);
        EXPECT_EQ(b1.hashCode(), b2.hashCode());
    }

    TEST(ByteTest, HashCodeDifferentForDifferentObjects)
    {
        const coco::Byte b1(10);
        const coco::Byte b2(20);
        EXPECT_NE(b1.hashCode(), b2.hashCode());
    }

    TEST(ByteTest, ToStringReturnsNumericValue)
    {
        const coco::Byte b(65);
        EXPECT_EQ(b.toString(), "class coco::Byte{A}");
    }

    TEST(ParseByteTest, ValidInputParsesCorrectly)
    {
        const auto b = coco::Byte::parseByte("100");
        EXPECT_EQ(b.byteValue(), 100);
    }

    TEST(ParseByteTest, EmptyStringThrowsInvalidArgument)
    {
        EXPECT_THROW(coco::Byte::parseByte(""), std::invalid_argument);
    }

    TEST(ParseByteTest, LeadingWhitespaceAllowed)
    {
        const auto b = coco::Byte::parseByte(" 255");
        EXPECT_EQ(b.byteValue(), 255);
    }

    TEST(ParseByteTest, InvalidTrailingCharactersThrow)
    {
        EXPECT_THROW(coco::Byte::parseByte("12a"), std::invalid_argument);
    }

    TEST(ParseByteTest, NegativeValueOutOfRangeThrows)
    {
        EXPECT_THROW(coco::Byte::parseByte("-1"), std::out_of_range);
    }

    TEST(ParseByteTest, PositiveValueOutOfRangeThrows)
    {
        EXPECT_THROW(coco::Byte::parseByte("256"), std::out_of_range);
    }

    TEST(ByteTest, EqualityOperator)
    {
        const coco::Byte b1(50);
        const coco::Byte b2(50);
        const coco::Byte b3(60);
        EXPECT_TRUE(b1 == b2);
        EXPECT_FALSE(b1 == b3);
    }

    TEST(ByteTest, SpaceshipOperator)
    {
        const coco::Byte b1(50);
        const coco::Byte b2(60);
        EXPECT_TRUE(b1 < b2);
    }

    TEST(ByteTest, AdditionValid)
    {
        const coco::Byte b1(100);
        const coco::Byte b2(50);
        const coco::Byte result = b1 + b2;
        EXPECT_EQ(result.byteValue(), 150);
    }

    TEST(ByteTest, AdditionOverflowThrows)
    {
        const coco::Byte b1(255);
        const coco::Byte b2(1);
        EXPECT_THROW(b1 + b2, std::overflow_error);
    }

    TEST(ByteTest, SubtractionValid)
    {
        const coco::Byte b1(100);
        const coco::Byte b2(50);
        const coco::Byte result = b1 - b2;
        EXPECT_EQ(result.byteValue(), 50);
    }

    TEST(ByteTest, SubtractionUnderflowThrows)
    {
        const coco::Byte b1(0);
        const coco::Byte b2(1);
        EXPECT_THROW(b1 - b2, std::underflow_error);
    }
}
