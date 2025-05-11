#include <stdexcept>
#include <entity/base_type/Byte.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ByteTest, DefaultConstructorInitializesToZero) {
    common::Byte b;
    EXPECT_EQ(b.byteValue(), 0);
  }

  TEST(ByteTest, ParameterizedConstructorSetsValue) {
    common::Byte b(100);
    EXPECT_EQ(b.byteValue(), 100);
  }

  TEST(ByteTest, CopyConstructorCopiesValue) {
    common::Byte b1(50);
    common::Byte b2 = b1;
    EXPECT_EQ(b2.byteValue(), 50);
  }

  TEST(ByteTest, MoveConstructorTransfersValue) {
    common::Byte b1(50);
    common::Byte b2 = std::move(b1);
    EXPECT_EQ(b2.byteValue(), 50);
  }

  TEST(ByteTest, CopyAssignmentCopiesValue) {
    common::Byte b1(50);
    common::Byte b2;
    b2 = b1;
    EXPECT_EQ(b2.byteValue(), 50);
  }

  TEST(ByteTest, MoveAssignmentTransfersValue) {
    common::Byte b1(50);
    common::Byte b2;
    b2 = std::move(b1);
    EXPECT_EQ(b2.byteValue(), 50);
  }

  TEST(ByteTest, HashCodeSameForEqualObjects) {
    common::Byte b1(10);
    common::Byte b2(10);
    EXPECT_EQ(b1.hashCode(), b2.hashCode());
  }

  TEST(ByteTest, HashCodeDifferentForDifferentObjects) {
    common::Byte b1(10);
    common::Byte b2(20);
    EXPECT_NE(b1.hashCode(), b2.hashCode());
  }

  TEST(ByteTest, ToStringReturnsNumericValue) {
    common::Byte b(65);
    EXPECT_EQ(b.toString(), "class common::Byte{A}");
  }

  TEST(ParseByteTest, ValidInputParsesCorrectly) {
    auto b = common::Byte::parseByte("100");
    EXPECT_EQ(b.byteValue(), 100);
  }

  TEST(ParseByteTest, EmptyStringThrowsInvalidArgument) {
    EXPECT_THROW(common::Byte::parseByte(""), std::invalid_argument);
  }

  TEST(ParseByteTest, LeadingWhitespaceAllowed) {
    auto b = common::Byte::parseByte(" 255");
    EXPECT_EQ(b.byteValue(), 255);
  }

  TEST(ParseByteTest, InvalidTrailingCharactersThrow) {
    EXPECT_THROW(common::Byte::parseByte("12a"), std::invalid_argument);
  }

  TEST(ParseByteTest, NegativeValueOutOfRangeThrows) {
    EXPECT_THROW(common::Byte::parseByte("-1"), std::out_of_range);
  }

  TEST(ParseByteTest, PositiveValueOutOfRangeThrows) {
    EXPECT_THROW(common::Byte::parseByte("256"), std::out_of_range);
  }

  TEST(ByteTest, EqualityOperator) {
    common::Byte b1(50);
    common::Byte b2(50);
    common::Byte b3(60);
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
  }

  TEST(ByteTest, SpaceshipOperator) {
    common::Byte b1(50);
    common::Byte b2(60);
    EXPECT_TRUE(b1 < b2);
  }

  TEST(ByteTest, AdditionValid) {
    common::Byte b1(100);
    common::Byte b2(50);
    common::Byte result = b1 + b2;
    EXPECT_EQ(result.byteValue(), 150);
  }

  TEST(ByteTest, AdditionOverflowThrows) {
    common::Byte b1(255);
    common::Byte b2(1);
    EXPECT_THROW(b1 + b2, std::overflow_error);
  }

  TEST(ByteTest, SubtractionValid) {
    common::Byte b1(100);
    common::Byte b2(50);
    common::Byte result = b1 - b2;
    EXPECT_EQ(result.byteValue(), 50);
  }

  TEST(ByteTest, SubtractionUnderflowThrows) {
    common::Byte b1(0);
    common::Byte b2(1);
    EXPECT_THROW(b1 - b2, std::underflow_error);
  }
}
