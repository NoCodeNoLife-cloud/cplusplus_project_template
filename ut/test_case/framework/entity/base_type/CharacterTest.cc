#include <entity/base_type/Character.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(CharacterTest, ConstructorTest) {
    const common::Character c1('A');
    EXPECT_EQ(c1.characterValue(), 'A');

    const common::Character c2('z');
    EXPECT_EQ(c2.characterValue(), 'z');

    const common::Character c3('5');
    EXPECT_EQ(c3.characterValue(), '5');

    const common::Character c4('#');
    EXPECT_EQ(c4.characterValue(), '#');
  }

  TEST(CharacterTest, ConversionOperatorTest) {
    const common::Character c('B');
    EXPECT_EQ(static_cast<char>(c), 'B');
  }

  TEST(CharacterTest, EqualsTest) {
    const common::Character c1('a');
    const common::Character c2('a');
    const common::Character c3('b');

    EXPECT_TRUE(c1.equals(c2));
    EXPECT_FALSE(c1.equals(c3));
  }

  TEST(CharacterTest, CompareToTest) {
    const common::Character c1('a');
    const common::Character c2('a');
    const common::Character c3('b');
    const common::Character c4('A');

    EXPECT_EQ(c1.compareTo(c2), 0);
    EXPECT_EQ(c3.compareTo(c1), 'b' - 'a');
    EXPECT_EQ(c4.compareTo(c1), 'A' - 'a');
  }

  TEST(CharacterTest, ComparisonOperatorsTest) {
    const common::Character a('a');
    const common::Character b('b');
    const common::Character same('a');

    EXPECT_TRUE(std::is_eq(a <=> same));
    EXPECT_FALSE(std::is_eq(a <=> b));
    EXPECT_TRUE(std::is_neq(a <=> b));
    EXPECT_FALSE(std::is_neq(a <=> same));

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
    EXPECT_TRUE(common::Character::isLetter('A'));
    EXPECT_TRUE(common::Character::isLetter('z'));
    EXPECT_FALSE(common::Character::isLetter('5'));
    EXPECT_FALSE(common::Character::isLetter('@'));
  }

  TEST(CharacterTest, IsDigitTest) {
    EXPECT_TRUE(common::Character::isDigit('3'));
    EXPECT_FALSE(common::Character::isDigit('A'));
    EXPECT_FALSE(common::Character::isDigit(' '));
  }

  TEST(CharacterTest, IsLetterOrDigitTest) {
    EXPECT_TRUE(common::Character::isLetterOrDigit('A'));
    EXPECT_TRUE(common::Character::isLetterOrDigit('9'));
    EXPECT_FALSE(common::Character::isLetterOrDigit('!'));
  }

  TEST(CharacterTest, IsUpperCaseTest) {
    EXPECT_TRUE(common::Character::isUpperCase('A'));
    EXPECT_FALSE(common::Character::isUpperCase('a'));
    EXPECT_FALSE(common::Character::isUpperCase('5'));
  }

  TEST(CharacterTest, IsLowerCaseTest) {
    EXPECT_TRUE(common::Character::isLowerCase('z'));
    EXPECT_FALSE(common::Character::isLowerCase('Z'));
    EXPECT_FALSE(common::Character::isLowerCase('0'));
  }

  TEST(CharacterTest, ToUpperCaseTest) {
    EXPECT_EQ(common::Character::toUpperCase('a'), static_cast<int32_t>('A'));
    EXPECT_EQ(common::Character::toUpperCase('A'), static_cast<int32_t>('A'));
    EXPECT_EQ(common::Character::toUpperCase('5'), static_cast<int32_t>('5'));
  }

  TEST(CharacterTest, ToLowerCaseTest) {
    EXPECT_EQ(common::Character::toLowerCase('A'), static_cast<int32_t>('a'));
    EXPECT_EQ(common::Character::toLowerCase('a'), static_cast<int32_t>('a'));
    EXPECT_EQ(common::Character::toLowerCase('3'), static_cast<int32_t>('3'));
  }
}
