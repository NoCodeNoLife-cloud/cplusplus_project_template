#include <gtest/gtest.h>

#include "type/base_type/Character.hpp"

namespace gtest_case
{
    TEST(CharacterTest, ConstructorTest)
    {
        const coco::Character c('A');
        EXPECT_EQ(c.characterValue(), 'A');
    }

    TEST(CharacterTest, CopyConstructorTest)
    {
        const coco::Character c1('B');
        const coco::Character c2(c1);
        EXPECT_EQ(c2.characterValue(), 'B');
    }

    TEST(CharacterTest, MoveConstructorTest)
    {
        coco::Character c1('C');
        const coco::Character c2(std::move(c1));
        EXPECT_EQ(c2.characterValue(), 'C');
    }

    TEST(CharacterTest, CopyAssignmentTest)
    {
        const coco::Character c1('D');
        coco::Character c2('E');
        c2 = c1;
        EXPECT_EQ(c2.characterValue(), 'D');
    }

    TEST(CharacterTest, MoveAssignmentTest)
    {
        coco::Character c1('F');
        coco::Character c2('G');
        c2 = std::move(c1);
        EXPECT_EQ(c2.characterValue(), 'F');
    }

    TEST(CharacterTest, HashCodeTest)
    {
        const coco::Character c1('H');
        const coco::Character c2('H');
        const coco::Character c3('I');
        EXPECT_EQ(c1.hashCode(), c2.hashCode());
        EXPECT_NE(c1.hashCode(), c3.hashCode());
    }

    TEST(CharacterTest, ToStringTest)
    {
        const coco::Character c('J');
        EXPECT_EQ(c.toString(), "class coco::Character{J}");
    }

    TEST(CharacterTest, CharCastTest)
    {
        const coco::Character c('K');
        EXPECT_EQ(static_cast<char>(c), 'K');
    }

    TEST(CharacterTest, IsLetterTest)
    {
        EXPECT_TRUE(coco::Character::isLetter('L'));
        EXPECT_FALSE(coco::Character::isLetter('1'));
        EXPECT_FALSE(coco::Character::isLetter('@'));
    }

    TEST(CharacterTest, IsDigitTest)
    {
        EXPECT_TRUE(coco::Character::isDigit('3'));
        EXPECT_FALSE(coco::Character::isDigit('A'));
        EXPECT_FALSE(coco::Character::isDigit('#'));
    }

    TEST(CharacterTest, IsLetterOrDigitTest)
    {
        EXPECT_TRUE(coco::Character::isLetterOrDigit('M'));
        EXPECT_TRUE(coco::Character::isLetterOrDigit('5'));
        EXPECT_FALSE(coco::Character::isLetterOrDigit('&'));
    }

    TEST(CharacterTest, IsUpperCaseTest)
    {
        EXPECT_TRUE(coco::Character::isUpperCase('N'));
        EXPECT_FALSE(coco::Character::isUpperCase('n'));
        EXPECT_FALSE(coco::Character::isUpperCase('6'));
    }

    TEST(CharacterTest, IsLowerCaseTest)
    {
        EXPECT_TRUE(coco::Character::isLowerCase('o'));
        EXPECT_FALSE(coco::Character::isLowerCase('O'));
        EXPECT_FALSE(coco::Character::isLowerCase('7'));
    }

    TEST(CharacterTest, ToUpperCaseTest)
    {
        EXPECT_EQ(coco::Character::toUpperCase('p'), 'P');
        EXPECT_EQ(coco::Character::toUpperCase('Q'), 'Q');
        EXPECT_EQ(coco::Character::toUpperCase('2'), '2');
    }

    TEST(CharacterTest, ToLowerCaseTest)
    {
        EXPECT_EQ(coco::Character::toLowerCase('R'), 'r');
        EXPECT_EQ(coco::Character::toLowerCase('s'), 's');
        EXPECT_EQ(coco::Character::toLowerCase('3'), '3');
    }

    TEST(CharacterTest, CharacterValueTest)
    {
        const coco::Character c('T');
        EXPECT_EQ(c.characterValue(), 'T');
    }

    TEST(CharacterTest, ComparisonOperatorsTest)
    {
        const coco::Character c1('U');
        const coco::Character c2('V');
        const coco::Character c3('U');

        EXPECT_EQ(c1 <=> c3, std::partial_ordering::equivalent);
        EXPECT_EQ(c1 <=> c2, std::partial_ordering::less);
        EXPECT_EQ(c2 <=> c1, std::partial_ordering::greater);
        EXPECT_TRUE(c1 == c3);
        EXPECT_FALSE(c1 == c2);
    }
}
