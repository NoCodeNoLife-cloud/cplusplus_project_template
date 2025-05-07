#include <stdexcept>
#include <entity/base_type/Byte.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ByteTest, ConstructorInitializesValueCorrectly) {
    constexpr uint8_t value = 42;
    const common::Byte byte(value);
    EXPECT_EQ(byte.byteValue(), value);
  }

  TEST(ByteTest, ByteValueReturnsInternalValue) {
    constexpr uint8_t value = 200;
    const common::Byte byte(value);
    EXPECT_EQ(byte.byteValue(), value);
  }

  TEST(ByteTest, EqualsComparesValuesCorrectly) {
    const common::Byte byte1(100);
    const common::Byte byte2(100);
    const common::Byte byte3(50);
    EXPECT_TRUE(byte1.equals(byte2));
    EXPECT_FALSE(byte1.equals(byte3));
  }

  TEST(ByteTest, CompareToReturnsCorrectResult) {
    const common::Byte byte1(50);
    const common::Byte byte2(50);
    const common::Byte byte3(30);
    const common::Byte byte4(70);
    EXPECT_EQ(byte1.compareTo(byte2), 0);
    EXPECT_GT(byte1.compareTo(byte3), 0);
    EXPECT_LT(byte1.compareTo(byte4), 0);
  }

  TEST(ByteTest, OperatorEqualityComparesValues) {
    const common::Byte byte1(10);
    const common::Byte byte2(10);
    const common::Byte byte3(20);
    EXPECT_TRUE(std::is_eq(byte1 <=> byte2));
    EXPECT_FALSE(std::is_eq(byte1 <=> byte3));
  }

  TEST(ByteTest, OperatorInequalityComparesValues) {
    const common::Byte byte1(15);
    const common::Byte byte2(25);
    const common::Byte byte3(15);
    EXPECT_TRUE(std::is_neq(byte1 <=> byte2));
    EXPECT_FALSE(std::is_neq(byte1 <=> byte3));
  }

  TEST(ByteTest, OperatorLessThanComparesValues) {
    const common::Byte byte1(30);
    const common::Byte byte2(40);
    const common::Byte byte3(30);
    EXPECT_TRUE(byte1 < byte2);
    EXPECT_FALSE(byte2 < byte1);
    EXPECT_FALSE(byte1 < byte3);
  }

  TEST(ByteTest, OperatorGreaterThanComparesValues) {
    const common::Byte byte1(50);
    const common::Byte byte2(40);
    const common::Byte byte3(50);
    EXPECT_TRUE(byte1 > byte2);
    EXPECT_FALSE(byte2 > byte1);
    EXPECT_FALSE(byte1 > byte3);
  }

  TEST(ByteTest, OperatorLessThanOrEqualComparesValues) {
    const common::Byte byte1(60);
    const common::Byte byte2(60);
    const common::Byte byte3(70);
    EXPECT_TRUE(byte1 <= byte2);
    EXPECT_TRUE(byte1 <= byte3);
    EXPECT_FALSE(byte3 <= byte1);
  }

  TEST(ByteTest, OperatorGreaterThanOrEqualComparesValues) {
    const common::Byte byte1(80);
    const common::Byte byte2(80);
    const common::Byte byte3(70);
    EXPECT_TRUE(byte1 >= byte2);
    EXPECT_TRUE(byte1 >= byte3);
    EXPECT_FALSE(byte3 >= byte1);
  }

  TEST(ByteTest, OperatorAdditionReturnsCorrectValue) {
    const common::Byte byte1(100);
    const common::Byte byte2(50);
    const common::Byte result = byte1 + byte2;
    EXPECT_EQ(result.byteValue(), 150);
  }

  TEST(ByteTest, OperatorAdditionOverflowThrowsOverflowError) {
    const common::Byte byte1(255);
    const common::Byte byte2(1);
    ASSERT_THROW(byte1 + byte2, std::overflow_error);
  }

  TEST(ByteTest, OperatorSubtractionReturnsCorrectValue) {
    const common::Byte byte1(100);
    const common::Byte byte2(30);
    const common::Byte result = byte1 - byte2;
    EXPECT_EQ(result.byteValue(), 70);
  }

  TEST(ByteTest, OperatorSubtractionUnderflowThrowsUnderflowError) {
    const common::Byte byte1(0);
    const common::Byte byte2(1);
    ASSERT_THROW(byte1 - byte2, std::underflow_error);
  }

  TEST(ByteTest, ParseByteValidStringReturnsCorrectValue) {
    const std::string str = "123";
    const common::Byte byte = common::Byte::parseByte(str);
    EXPECT_EQ(byte.byteValue(), 123);
  }

  TEST(ByteTest, ParseByteEmptyStringThrowsInvalidArgument) {
    const std::string str;
    ASSERT_THROW(common::Byte::parseByte(str), std::invalid_argument);
  }

  TEST(ByteTest, ParseByteInvalidCharacterThrowsInvalidArgument) {
    const std::string str = "12a";
    ASSERT_THROW(common::Byte::parseByte(str), std::invalid_argument);
  }

  TEST(ByteTest, ParseByteNegativeValueThrowsOutOfRange) {
    const std::string str = "-1";
    ASSERT_THROW(common::Byte::parseByte(str), std::out_of_range);
  }

  TEST(ByteTest, ParseByteExceedsMaxValueThrowsOutOfRange) {
    const std::string str = "256";
    ASSERT_THROW(common::Byte::parseByte(str), std::out_of_range);
  }

  TEST(ByteTest, ToStringReturnsCorrectFormat) {
    const common::Byte byte(42);
    EXPECT_EQ(byte.toString(), "42");
  }
}
