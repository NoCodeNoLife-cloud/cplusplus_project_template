#include <regex>
#include <stdexcept>
#include <vector>
#include <gtest/gtest.h>

#include "type/base_type/String.hpp"

namespace gtest_case
{
    TEST(StringTest, DefaultConstructor)
    {
        const common::String str;
        EXPECT_EQ(str.toStdString(), "");
        EXPECT_TRUE(str.isEmpty());
    }

    TEST(StringTest, CharPtrConstructor)
    {
        const common::String str("hello");
        EXPECT_EQ(str.toStdString(), "hello");
        EXPECT_EQ(str.length(), 5);
    }

    TEST(StringTest, StdStringConstructor)
    {
        const std::string stdStr = "world";
        const common::String str(stdStr);
        EXPECT_EQ(str.toStdString(), "world");
    }

    TEST(StringTest, CopyConstructor)
    {
        const common::String str1("copy");
        const common::String str2(str1);
        EXPECT_EQ(str2.toStdString(), "copy");
    }

    TEST(StringTest, MoveConstructor)
    {
        common::String str1("move");
        const common::String str2(std::move(str1));
        EXPECT_EQ(str2.toStdString(), "move");
        // Note: str1.value_ may be in valid state per C++ move semantics
    }

    TEST(StringTest, AssignOperator)
    {
        const common::String str1("assign");
        const common::String str2 = str1;
        EXPECT_EQ(str2.toStdString(), "assign");
    }

    TEST(StringTest, MoveAssignOperator)
    {
        common::String str1("move_assign");
        const common::String str2 = std::move(str1);
        EXPECT_EQ(str2.toStdString(), "move_assign");
    }

    TEST(StringTest, CharAt_NormalIndex)
    {
        const common::String str("index");
        EXPECT_EQ(str.charAt(0), 'i');
        EXPECT_EQ(str.charAt(4), 'x');
    }

    TEST(StringTest, CharAt_OutOfBounds)
    {
        common::String str("error");
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.charAt(-1), std::out_of_range);
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.charAt(5), std::out_of_range);
    }

    TEST(StringTest, Substring_NormalRange)
    {
        const common::String str("substring");
        EXPECT_EQ(str.substring(0, 3).toStdString(), "sub");
        EXPECT_EQ(str.substring(3, 6).toStdString(), "str");
    }

    TEST(StringTest, Substring_EmptyRange)
    {
        const common::String str("empty");
        // ReSharper disable once CppNoDiscardExpression
        EXPECT_THROW(str.substring(2, 6), std::out_of_range);
    }

    TEST(StringTest, ConcatOperation)
    {
        const common::String str1("hello");
        const common::String str2("world");
        const common::String result = str1.concat(str2);
        EXPECT_EQ(result.toStdString(), "helloworld");
    }

    TEST(StringTest, CompareToIgnoreCase_Equal)
    {
        const common::String str1("Equal");
        const common::String str2("equal");
        EXPECT_EQ(str1.compareToIgnoreCase(str2), 0);
    }

    TEST(StringTest, Replace_Char)
    {
        const common::String str("a_b_c");
        const common::String result = str.replace('_', '-');
        EXPECT_EQ(result.toStdString(), "a-b-c");
    }

    TEST(StringTest, ToLowerAndUpper)
    {
        const common::String str("MixEd");
        EXPECT_EQ(str.toLowerCase().toStdString(), "mixed");
        EXPECT_EQ(str.toUpperCase().toStdString(), "MIXED");
    }

    TEST(StringTest, TrimOperation)
    {
        const common::String str("  trim  ");
        EXPECT_EQ(str.trim().toStdString(), "trim");
    }

    TEST(StringTest, IndexOf_Char)
    {
        const common::String str("findme");
        EXPECT_EQ(str.indexOf('m'), 4);
        EXPECT_EQ(str.indexOf('x'), -1);
    }

    TEST(StringTest, LastIndexOf_Char)
    {
        const common::String str("abracadabra");
        EXPECT_EQ(str.lastIndexOf('a'), 10);
    }

    TEST(StringTest, Regex_Match)
    {
        const common::String str("12345");
        EXPECT_TRUE(str.matches("\\d+"));
        EXPECT_FALSE(str.matches("\\D+"));
    }

    TEST(StringTest, Regex_ReplaceAll)
    {
        const common::String str("a1b2c3");
        const common::String result = str.replaceAll("\\d", "X");
        EXPECT_EQ(result.toStdString(), "aXbXcX");
    }

    TEST(StringTest, Split_Operator)
    {
        const common::String str("a,b,c");
        const auto result = str.split(",");
        EXPECT_EQ(result.size(), 3);
        EXPECT_EQ(result[1].toStdString(), "b");
    }

    TEST(StringTest, ValueOf_Integers)
    {
        EXPECT_EQ(common::String::valueOf(123).toStdString(), "123");
        EXPECT_EQ(common::String::valueOf(-456).toStdString(), "-456");
    }

    TEST(StringTest, ValueOf_Floats)
    {
        EXPECT_EQ(common::String::valueOf(1.23f).toStdString(), "1.230000");
    }

    TEST(StringTest, ValueOf_Boolean)
    {
        EXPECT_EQ(common::String::valueOf(true).toStdString(), "true");
        EXPECT_EQ(common::String::valueOf(false).toStdString(), "false");
    }

    TEST(StringTest, RegionMatches)
    {
        const common::String str1("abcdef");
        const common::String str2("cdefgh");
        EXPECT_TRUE(str1.regionMatches(2, str2, 0, 4));
        EXPECT_FALSE(str1.regionMatches(1, str2, 0, 4));
    }

    TEST(StringTest, Operator_Equality)
    {
        const common::String str1("equal");
        const common::String str2("equal");
        EXPECT_TRUE(str1 == str2);
        EXPECT_FALSE(str1 != str2);
    }

    TEST(StringTest, Operator_LessThan)
    {
        const common::String str1("abc");
        const common::String str2("def");
        EXPECT_TRUE(str1 < str2);
    }
}
