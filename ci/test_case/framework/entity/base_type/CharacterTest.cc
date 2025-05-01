#include <entity/base_type/Character.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(CharacterTest, ConstructorTest) {
    const framework::entity::base_type::Character c1('A');
    EXPECT_EQ(c1.characterValue(), 'A');

    const framework::entity::base_type::Character c2('z');
    EXPECT_EQ(c2.characterValue(), 'z');

    const framework::entity::base_type::Character c3('5');
    EXPECT_EQ(c3.characterValue(), '5');

    const framework::entity::base_type::Character c4('#');
    EXPECT_EQ(c4.characterValue(), '#');
  }

  TEST(CharacterTest, ConversionOperatorTest) {
    const framework::entity::base_type::Character c('B');
    EXPECT_EQ(static_cast<char>(c), 'B');
  }

  TEST(CharacterTest, ToStringTest) {
    const framework::entity::base_type::Character c1('X');
    EXPECT_EQ(c1.toString(), "X");

    const framework::entity::base_type::Character c2(' ');
    EXPECT_EQ(c2.toString(), " ");

    const framework::entity::base_type::Character c3('\n');
    EXPECT_EQ(c3.toString(), "\n");
  }

  TEST(CharacterTest, EqualsTest) {
    const framework::entity::base_type::Character c1('a');
    const framework::entity::base_type::Character c2('a');
    const framework::entity::base_type::Character c3('b');

    EXPECT_TRUE(c1.equals(c2));
    EXPECT_FALSE(c1.equals(c3));
  }

  TEST(CharacterTest, CompareToTest) {
    const framework::entity::base_type::Character c1('a');
    const framework::entity::base_type::Character c2('a');
    const framework::entity::base_type::Character c3('b');
    const framework::entity::base_type::Character c4('A');

    EXPECT_EQ(c1.compareTo(c2), 0);
    EXPECT_EQ(c3.compareTo(c1), static_cast<int32_t>('b' - 'a'));
    EXPECT_EQ(c4.compareTo(c1), static_cast<int32_t>('A' - 'a'));
  }

  TEST(CharacterTest, ComparisonOperatorsTest) {
    const framework::entity::base_type::Character a('a');
    const framework::entity::base_type::Character b('b');
    const framework::entity::base_type::Character same('a');

    EXPECT_TRUE(a == same);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != same);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);

    EXPECT_TRUE(b > a);
    EXPECT_FALSE(a > b);

    EXPECT_TRUE(a <= same);
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(b <= a);

    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(a >= b);
  }

  TEST(CharacterTest, IsLetterTest) {
    EXPECT_TRUE(framework::entity::base_type::Character::isLetter('A'));
    EXPECT_TRUE(framework::entity::base_type::Character::isLetter('z'));
    EXPECT_FALSE(framework::entity::base_type::Character::isLetter('5'));
    EXPECT_FALSE(framework::entity::base_type::Character::isLetter('@'));
  }

  TEST(CharacterTest, IsDigitTest) {
    EXPECT_TRUE(framework::entity::base_type::Character::isDigit('3'));
    EXPECT_FALSE(framework::entity::base_type::Character::isDigit('A'));
    EXPECT_FALSE(framework::entity::base_type::Character::isDigit(' '));
  }

  TEST(CharacterTest, IsLetterOrDigitTest) {
    EXPECT_TRUE(framework::entity::base_type::Character::isLetterOrDigit('A'));
    EXPECT_TRUE(framework::entity::base_type::Character::isLetterOrDigit('9'));
    EXPECT_FALSE(framework::entity::base_type::Character::isLetterOrDigit('!'));
  }

  TEST(CharacterTest, IsUpperCaseTest) {
    EXPECT_TRUE(framework::entity::base_type::Character::isUpperCase('A'));
    EXPECT_FALSE(framework::entity::base_type::Character::isUpperCase('a'));
    EXPECT_FALSE(framework::entity::base_type::Character::isUpperCase('5'));
  }

  TEST(CharacterTest, IsLowerCaseTest) {
    EXPECT_TRUE(framework::entity::base_type::Character::isLowerCase('z'));
    EXPECT_FALSE(framework::entity::base_type::Character::isLowerCase('Z'));
    EXPECT_FALSE(framework::entity::base_type::Character::isLowerCase('0'));
  }

  TEST(CharacterTest, ToUpperCaseTest) {
    EXPECT_EQ(framework::entity::base_type::Character::toUpperCase('a'), static_cast<int32_t>('A'));
    EXPECT_EQ(framework::entity::base_type::Character::toUpperCase('A'), static_cast<int32_t>('A'));
    EXPECT_EQ(framework::entity::base_type::Character::toUpperCase('5'), static_cast<int32_t>('5'));
  }

  TEST(CharacterTest, ToLowerCaseTest) {
    EXPECT_EQ(framework::entity::base_type::Character::toLowerCase('A'), static_cast<int32_t>('a'));
    EXPECT_EQ(framework::entity::base_type::Character::toLowerCase('a'), static_cast<int32_t>('a'));
    EXPECT_EQ(framework::entity::base_type::Character::toLowerCase('3'), static_cast<int32_t>('3'));
  }
} // namespace gtest_case
