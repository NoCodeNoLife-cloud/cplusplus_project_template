#include <stdexcept>
#include <string>
#include <entity/base_type/Boolean.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(BooleanTest, ConstructorInitializesValueCorrectly) {
    const framework::entity::base_type::Boolean booleanTrue(true);
    EXPECT_TRUE(booleanTrue.boolValue());
    const framework::entity::base_type::Boolean booleanFalse(false);
    EXPECT_FALSE(booleanFalse.boolValue());
  }

  TEST(BooleanTest, ConversionToBoolReturnsCorrectValue) {
    const framework::entity::base_type::Boolean booleanTrue(true);
    EXPECT_TRUE(static_cast<bool>(booleanTrue));
    const framework::entity::base_type::Boolean booleanFalse(false);
    EXPECT_FALSE(static_cast<bool>(booleanFalse));
  }

  TEST(BooleanTest, ToStringReturnsCorrectString) {
    const framework::entity::base_type::Boolean booleanTrue(true);
    EXPECT_EQ(booleanTrue.toString(), "true");
    const framework::entity::base_type::Boolean booleanFalse(false);
    EXPECT_EQ(booleanFalse.toString(), "false");
  }

  TEST(BooleanTest, ParseBooleanValidStrings) {
    EXPECT_TRUE(framework::entity::base_type::Boolean::parseBoolean("true").booleanValue());
    EXPECT_TRUE(framework::entity::base_type::Boolean::parseBoolean("TRUE").booleanValue());
    EXPECT_FALSE(framework::entity::base_type::Boolean::parseBoolean("false").booleanValue());
    EXPECT_FALSE(framework::entity::base_type::Boolean::parseBoolean("FALSE").booleanValue());
  }

  TEST(BooleanTest, ParseBooleanInvalidStringThrowsException) {
    EXPECT_THROW(framework::entity::base_type::Boolean::parseBoolean("invalid"), std::invalid_argument);
  }

  TEST(BooleanTest, CompareToReturnsCorrectValues) {
    const framework::entity::base_type::Boolean trueObj(true);
    const framework::entity::base_type::Boolean falseObj(false);
    EXPECT_EQ(trueObj.compareTo(trueObj), 0);
    EXPECT_EQ(falseObj.compareTo(falseObj), 0);
    EXPECT_EQ(trueObj.compareTo(falseObj), 1);
    EXPECT_EQ(falseObj.compareTo(trueObj), -1);
  }

  TEST(BooleanTest, EqualsComparesValueCorrectly) {
    const framework::entity::base_type::Boolean true1(true);
    const framework::entity::base_type::Boolean true2(true);
    const framework::entity::base_type::Boolean false1(false);
    EXPECT_TRUE(true1.equals(true2));
    EXPECT_FALSE(true1.equals(false1));
    EXPECT_TRUE(true1.equals(true1));
    EXPECT_FALSE(false1.equals(true1));
  }

  TEST(BooleanTest, EqualityOperatorsWorkCorrectly) {
    const framework::entity::base_type::Boolean a(true);
    const framework::entity::base_type::Boolean b(true);
    const framework::entity::base_type::Boolean c(false);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
  }

  TEST(BooleanTest, StaticConstantsHaveCorrectValues) {
    EXPECT_TRUE(framework::entity::base_type::True);
    EXPECT_FALSE(framework::entity::base_type::False);
  }

  TEST(BooleanTest, BooleanValueAndBoolValueReturnSameValue) {
    const framework::entity::base_type::Boolean obj1(true);
    EXPECT_TRUE(obj1.booleanValue());
    EXPECT_TRUE(obj1.boolValue());
    const framework::entity::base_type::Boolean obj2(false);
    EXPECT_FALSE(obj2.booleanValue());
    EXPECT_FALSE(obj2.boolValue());
  }
} // namespace gtest_case
