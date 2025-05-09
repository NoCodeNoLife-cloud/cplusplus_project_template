#include <stdexcept>
#include <string>
#include <entity/base_type/Boolean.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BooleanTest, ConstructorInitializesValueCorrectly) {
    const common::Boolean booleanTrue(true);
    EXPECT_TRUE(booleanTrue.boolValue());
    const common::Boolean booleanFalse(false);
    EXPECT_FALSE(booleanFalse.boolValue());
  }

  TEST(BooleanTest, ConversionToBoolReturnsCorrectValue) {
    const common::Boolean booleanTrue(true);
    EXPECT_TRUE(static_cast<bool>(booleanTrue));
    const common::Boolean booleanFalse(false);
    EXPECT_FALSE(static_cast<bool>(booleanFalse));
  }

  TEST(BooleanTest, ToStringReturnsCorrectString) {
    const common::Boolean booleanTrue(true);
    EXPECT_EQ(booleanTrue.toString(), "class common::Boolean{1}");
    const common::Boolean booleanFalse(false);
    EXPECT_EQ(booleanFalse.toString(), "class common::Boolean{0}");
  }

  TEST(BooleanTest, ParseBooleanValidStrings) {
    EXPECT_TRUE(common::Boolean::parseBoolean("true").booleanValue());
    EXPECT_TRUE(common::Boolean::parseBoolean("TRUE").booleanValue());
    EXPECT_FALSE(common::Boolean::parseBoolean("false").booleanValue());
    EXPECT_FALSE(common::Boolean::parseBoolean("FALSE").booleanValue());
  }

  TEST(BooleanTest, ParseBooleanInvalidStringThrowsException) {
    EXPECT_THROW(common::Boolean::parseBoolean("invalid"), std::invalid_argument);
  }

  TEST(BooleanTest, CompareToReturnsCorrectValues) {
    const common::Boolean trueObj(true);
    const common::Boolean falseObj(false);
    EXPECT_EQ(trueObj.compareTo(trueObj), 0);
    EXPECT_EQ(falseObj.compareTo(falseObj), 0);
    EXPECT_EQ(trueObj.compareTo(falseObj), 1);
    EXPECT_EQ(falseObj.compareTo(trueObj), -1);
  }

  TEST(BooleanTest, EqualsComparesValueCorrectly) {
    const common::Boolean true1(true);
    const common::Boolean true2(true);
    const common::Boolean false1(false);
    EXPECT_TRUE(true1.equals(true2));
    EXPECT_FALSE(true1.equals(false1));
    EXPECT_TRUE(true1.equals(true1));
    EXPECT_FALSE(false1.equals(true1));
  }

  TEST(BooleanTest, EqualityOperatorsWorkCorrectly) {
    const common::Boolean a(true);
    const common::Boolean b(true);
    const common::Boolean c(false);
    EXPECT_TRUE(std::is_eq(a <=> b));
    EXPECT_FALSE(std::is_eq(a <=> c));
    EXPECT_FALSE(std::is_neq(a <=> b));
    EXPECT_TRUE(std::is_neq(a <=> c));
  }

  TEST(BooleanTest, StaticConstantsHaveCorrectValues) {
    EXPECT_TRUE(common::True);
    EXPECT_FALSE(common::False);
  }

  TEST(BooleanTest, BooleanValueAndBoolValueReturnSameValue) {
    const common::Boolean obj1(true);
    EXPECT_TRUE(obj1.booleanValue());
    EXPECT_TRUE(obj1.boolValue());
    const common::Boolean obj2(false);
    EXPECT_FALSE(obj2.booleanValue());
    EXPECT_FALSE(obj2.boolValue());
  }
}
