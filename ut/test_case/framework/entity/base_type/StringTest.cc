#include <regex>
#include <stdexcept>
#include <vector>
#include <type/base_type/String.hpp>
#include <gtest/gtest.h>

namespace gtest_case
{
    TEST(StringTest, DefaultConstructor)
    {
        const coco::String str;
        EXPECT_EQ(str.toStdString(), "");
        EXPECT_TRUE(str.isEmpty());
    }

    TEST(StringTest, CharPtrConstructor)
    {
        const coco::String str("hello");
        EXPECT_EQ(str.toStdString(), "hello");
        EXPECT_EQ(str.length(), 5);
    }

    TEST(StringTest, StdStringConstructor)
    {
        const std::string stdStr = "world";
        const coco::String str(stdStr);
        EXPECT_EQ(str.toStdString(), "world");
    }

    TEST(StringTest, CopyConstructor)
    {
        const coco::String str1("copy");
        const coco::String str2(str1);
        EXPECT_EQ(str2.toStdString(), "copy");
    }

    TEST(StringTest, MoveConstructor)
    {
        coco::String str1("move");
        const coco::String str2(std::move(str1));
        EXPECT_EQ(str2.toStdString(), "move");
        // Note: str1.value_ may be in valid state per C++ move semantics
    }

    TEST(StringTest, AssignOperator)
    {
        const coco::String str1("assign");
        const coco::String str2 = str1;
        EXPECT_EQ(str2.toStdString(), "assign");
    }

    TEST(StringTest, MoveAssignOperator)
    {
        coco::String str1("move_assign");
        const coco::String str2 = std::move(str1);
        EXPECT_EQ(str2.toStdString(), "move_assign");
    }

    TEST(StringTest, CharAt_NormalIndex)
    {
        const coco::String str("index");
        EXPECT_EQ(str.charAt(0), 'i');
        EXPECT_EQ(str.charAt(4), 'x');
    }

    TEST(StringTest, CharAt_OutOfBounds)
    {
        coco::String str("error");
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.charAt(-1), std::out_of_range);
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.charAt(5), std::out_of_range);
    }

    TEST(StringTest, Substring_NormalRange)
    {
        const coco::String str("substring");
        EXPECT_EQ(str.substring(0, 3).toStdString(), "sub");
        EXPECT_EQ(str.substring(3, 6).toStdString(), "str");
    }

    TEST(StringTest, Substring_EmptyRange)
    {
        const coco::String str("empty");
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.substring(2, 6), std::out_of_range);
    }

    TEST(StringTest, ConcatOperation)
    {
        const coco::String str1("hello");
        const coco::String str2("world");
        const coco::String result = str1.concat(str2);
        EXPECT_EQ(result.toStdString(), "helloworld");
    }

    TEST(StringTest, CompareToIgnoreCase_Equal)
    {
        const coco::String str1("Equal");
        const coco::String str2("equal");
        EXPECT_EQ(str1.compareToIgnoreCase(str2), 0);
    }

    TEST(StringTest, Replace_Char)
    {
        const coco::String str("a_b_c");
        const coco::String result = str.replace('_', '-');
        EXPECT_EQ(result.toStdString(), "a-b-c");
    }

    TEST(StringTest, ToLowerAndUpper)
    {
        const coco::String str("MixEd");
        EXPECT_EQ(str.toLowerCase().toStdString(), "mixed");
        EXPECT_EQ(str.toUpperCase().toStdString(), "MIXED");
    }

    TEST(StringTest, TrimOperation)
    {
        const coco::String str("  trim  ");
        EXPECT_EQ(str.trim().toStdString(), "trim");
    }

    TEST(StringTest, IndexOf_Char)
    {
        const coco::String str("findme");
        EXPECT_EQ(str.indexOf('m'), 4);
        EXPECT_EQ(str.indexOf('x'), -1);
    }

    TEST(StringTest, LastIndexOf_Char)
    {
        const coco::String str("abracadabra");
        EXPECT_EQ(str.lastIndexOf('a'), 10);
    }

    TEST(StringTest, Regex_Match)
    {
        const coco::String str("12345");
        EXPECT_TRUE(str.matches("\\d+"));
        EXPECT_FALSE(str.matches("\\D+"));
    }

    TEST(StringTest, Regex_ReplaceAll)
    {
        const coco::String str("a1b2c3");
        const coco::String result = str.replaceAll("\\d", "X");
        EXPECT_EQ(result.toStdString(), "aXbXcX");
    }

    TEST(StringTest, Split_Operator)
    {
        const coco::String str("a,b,c");
        const auto result = str.split(",");
        EXPECT_EQ(result.size(), 3);
        EXPECT_EQ(result[1].toStdString(), "b");
    }

    TEST(StringTest, ValueOf_Integers)
    {
        EXPECT_EQ(coco::String::valueOf(123).toStdString(), "123");
        EXPECT_EQ(coco::String::valueOf(-456).toStdString(), "-456");
    }

    TEST(StringTest, ValueOf_Floats)
    {
        EXPECT_EQ(coco::String::valueOf(1.23f).toStdString(), "1.230000");
    }

    TEST(StringTest, ValueOf_Boolean)
    {
        EXPECT_EQ(coco::String::valueOf(true).toStdString(), "true");
        EXPECT_EQ(coco::String::valueOf(false).toStdString(), "false");
    }

    TEST(StringTest, RegionMatches)
    {
        const coco::String str1("abcdef");
        const coco::String str2("cdefgh");
        EXPECT_TRUE(str1.regionMatches(2, str2, 0, 4));
        EXPECT_FALSE(str1.regionMatches(1, str2, 0, 4));
    }

    TEST(StringTest, Operator_Equality)
    {
        const coco::String str1("equal");
        const coco::String str2("equal");
        EXPECT_TRUE(str1 == str2);
        EXPECT_FALSE(str1 != str2);
    }

    TEST(StringTest, Operator_LessThan)
    {
        const coco::String str1("abc");
        const coco::String str2("def");
        EXPECT_TRUE(str1 < str2);
    }
}
