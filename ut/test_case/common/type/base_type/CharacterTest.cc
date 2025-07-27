#include <gtest/gtest.h>

#include "type/base_type/Character.hpp"

namespace gtest_case
{
    TEST(CharacterTest, ConstructorTest)
    {
        const common::Character c('A');
        EXPECT_EQ(c.characterValue(), 'A');
    }

    TEST(CharacterTest, CopyConstructorTest)
    {
        const common::Character c1('B');
        const common::Character c2(c1);
        EXPECT_EQ(c2.characterValue(), 'B');
    }

    TEST(CharacterTest, MoveConstructorTest)
    {
        common::Character c1('C');
        const common::Character c2(std::move(c1));
        EXPECT_EQ(c2.characterValue(), 'C');
    }

    TEST(CharacterTest, CopyAssignmentTest)
    {
        const common::Character c1('D');
        common::Character c2('E');
        c2 = c1;
        EXPECT_EQ(c2.characterValue(), 'D');
    }

    TEST(CharacterTest, MoveAssignmentTest)
    {
        common::Character c1('F');
        common::Character c2('G');
        c2 = std::move(c1);
        EXPECT_EQ(c2.characterValue(), 'F');
    }

    TEST(CharacterTest, HashCodeTest)
    {
        const common::Character c1('H');
        const common::Character c2('H');
        const common::Character c3('I');
        EXPECT_EQ(c1.hashCode(), c2.hashCode());
        EXPECT_NE(c1.hashCode(), c3.hashCode());
    }

    TEST(CharacterTest, ToStringTest)
    {
        const common::Character c('J');
        EXPECT_EQ(c.toString(), "class common::Character{J}");
    }

    TEST(CharacterTest, CharCastTest)
    {
        const common::Character c('K');
        EXPECT_EQ(static_cast<char>(c), 'K');
    }

    TEST(CharacterTest, IsLetterTest)
    {
        EXPECT_TRUE(common::Character::isLetter('L'));
        EXPECT_FALSE(common::Character::isLetter('1'));
        EXPECT_FALSE(common::Character::isLetter('@'));
    }

    TEST(CharacterTest, IsDigitTest)
    {
        EXPECT_TRUE(common::Character::isDigit('3'));
        EXPECT_FALSE(common::Character::isDigit('A'));
        EXPECT_FALSE(common::Character::isDigit('#'));
    }

    TEST(CharacterTest, IsLetterOrDigitTest)
    {
        EXPECT_TRUE(common::Character::isLetterOrDigit('M'));
        EXPECT_TRUE(common::Character::isLetterOrDigit('5'));
        EXPECT_FALSE(common::Character::isLetterOrDigit('&'));
    }

    TEST(CharacterTest, IsUpperCaseTest)
    {
        EXPECT_TRUE(common::Character::isUpperCase('N'));
        EXPECT_FALSE(common::Character::isUpperCase('n'));
        EXPECT_FALSE(common::Character::isUpperCase('6'));
    }

    TEST(CharacterTest, IsLowerCaseTest)
    {
        EXPECT_TRUE(common::Character::isLowerCase('o'));
        EXPECT_FALSE(common::Character::isLowerCase('O'));
        EXPECT_FALSE(common::Character::isLowerCase('7'));
    }

    TEST(CharacterTest, ToUpperCaseTest)
    {
        EXPECT_EQ(common::Character::toUpperCase('p'), 'P');
        EXPECT_EQ(common::Character::toUpperCase('Q'), 'Q');
        EXPECT_EQ(common::Character::toUpperCase('2'), '2');
    }

    TEST(CharacterTest, ToLowerCaseTest)
    {
        EXPECT_EQ(common::Character::toLowerCase('R'), 'r');
        EXPECT_EQ(common::Character::toLowerCase('s'), 's');
        EXPECT_EQ(common::Character::toLowerCase('3'), '3');
    }

    TEST(CharacterTest, CharacterValueTest)
    {
        const common::Character c('T');
        EXPECT_EQ(c.characterValue(), 'T');
    }

    TEST(CharacterTest, ComparisonOperatorsTest)
    {
        const common::Character c1('U');
        const common::Character c2('V');
        const common::Character c3('U');

        EXPECT_EQ(c1 <=> c3, std::partial_ordering::equivalent);
        EXPECT_EQ(c1 <=> c2, std::partial_ordering::less);
        EXPECT_EQ(c2 <=> c1, std::partial_ordering::greater);
        EXPECT_TRUE(c1 == c3);
        EXPECT_FALSE(c1 == c2);
    }
}
