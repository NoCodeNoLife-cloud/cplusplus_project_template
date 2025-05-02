#include <stdexcept>
#include <string>
#include <entity/base_type/Boolean.hpp>
#include <gtest/gtest.h>
using framework::entity::base_type::Boolean;
using framework::entity::base_type::True;
using framework::entity::base_type::False;

namespace gtest_case {
  TEST(BooleanTest, ConstructorInitializesValueCorrectly) {
    const Boolean booleanTrue(true);
    EXPECT_TRUE(booleanTrue.boolValue());
    const Boolean booleanFalse(false);
    EXPECT_FALSE(booleanFalse.boolValue());
  }

  TEST(BooleanTest, ConversionToBoolReturnsCorrectValue) {
    const Boolean booleanTrue(true);
    EXPECT_TRUE(static_cast<bool>(booleanTrue));
    const Boolean booleanFalse(false);
    EXPECT_FALSE(static_cast<bool>(booleanFalse));
  }

  TEST(BooleanTest, ToStringReturnsCorrectString) {
    const Boolean booleanTrue(true);
    EXPECT_EQ(booleanTrue.toString(), "true");
    const Boolean booleanFalse(false);
    EXPECT_EQ(booleanFalse.toString(), "false");
  }

  TEST(BooleanTest, ParseBooleanValidStrings) {
    EXPECT_TRUE(Boolean::parseBoolean("true").booleanValue());
    EXPECT_TRUE(Boolean::parseBoolean("TRUE").booleanValue());
    EXPECT_FALSE(Boolean::parseBoolean("false").booleanValue());
    EXPECT_FALSE(Boolean::parseBoolean("FALSE").booleanValue());
  }

  TEST(BooleanTest, ParseBooleanInvalidStringThrowsException) {
    EXPECT_THROW(Boolean::parseBoolean("invalid"), std::invalid_argument);
  }

  TEST(BooleanTest, CompareToReturnsCorrectValues) {
    const Boolean trueObj(true);
    const Boolean falseObj(false);
    EXPECT_EQ(trueObj.compareTo(trueObj), 0);
    EXPECT_EQ(falseObj.compareTo(falseObj), 0);
    EXPECT_EQ(trueObj.compareTo(falseObj), 1);
    EXPECT_EQ(falseObj.compareTo(trueObj), -1);
  }

  TEST(BooleanTest, EqualsComparesValueCorrectly) {
    const Boolean true1(true);
    const Boolean true2(true);
    const Boolean false1(false);
    EXPECT_TRUE(true1.equals(true2));
    EXPECT_FALSE(true1.equals(false1));
    EXPECT_TRUE(true1.equals(true1));
    EXPECT_FALSE(false1.equals(true1));
  }

  TEST(BooleanTest, EqualityOperatorsWorkCorrectly) {
    const Boolean a(true);
    const Boolean b(true);
    const Boolean c(false);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  }

  TEST(BooleanTest, StaticConstantsHaveCorrectValues) {
    EXPECT_TRUE(True);
    EXPECT_FALSE(False);
  }

  TEST(BooleanTest, BooleanValueAndBoolValueReturnSameValue) {
    const Boolean obj1(true);
    EXPECT_TRUE(obj1.booleanValue());
    EXPECT_TRUE(obj1.boolValue());
    const Boolean obj2(false);
    EXPECT_FALSE(obj2.booleanValue());
    EXPECT_FALSE(obj2.boolValue());
  }
} // namespace gtest_case
