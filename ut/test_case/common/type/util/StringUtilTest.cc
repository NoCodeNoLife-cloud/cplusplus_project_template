#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "type/util/StringUtil.hpp"

namespace gtest_case
{
    TEST(StringTest, SplitEmptyString)
    {
        const std::string target;
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {""};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitSimpleCase)
    {
        const std::string target = "a,b,c";
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {"a", "b", "c"};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitLeadingDelimiter)
    {
        const std::string target = ",a,b";
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {"", "a", "b"};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitTrailingDelimiter)
    {
        const std::string target = "a,b,";
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {"a", "b", ""};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitMultipleDelimiters)
    {
        const std::string target = "a,,b";
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {"a", "", "b"};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitNoDelimiter)
    {
        const std::string target = "hello";
        constexpr char split_char = ',';
        const std::vector<std::string> expected = {"hello"};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    TEST(StringTest, SplitSingleCharDelimiter)
    {
        const std::string target = "x";
        constexpr char split_char = 'x';
        const std::vector<std::string> expected = {"", ""};
        EXPECT_EQ(fox::StringUtil::split(target, split_char), expected);
    }

    // Tests for concatenate function
    TEST(StringTest, ConcatenateEmptyVector)
    {
        const std::vector<std::string> source;
        constexpr char split_char = ',';
        const std::string expected;
        EXPECT_EQ(fox::StringUtil::concatenate(source, split_char), expected);
    }

    TEST(StringTest, ConcatenateSingleElement)
    {
        const std::vector<std::string> source = {"hello"};
        constexpr char split_char = ',';
        const std::string expected = "hello";
        EXPECT_EQ(fox::StringUtil::concatenate(source, split_char), expected);
    }

    TEST(StringTest, ConcatenateMultipleElements)
    {
        const std::vector<std::string> source = {"a", "b", "c"};
        constexpr char split_char = ',';
        const std::string expected = "a,b,c";
        EXPECT_EQ(fox::StringUtil::concatenate(source, split_char), expected);
    }

    TEST(StringTest, ConcatenateWithEmptyStrings)
    {
        const std::vector<std::string> source = {"a", "", "b"};
        constexpr char split_char = ',';
        const std::string expected = "a,,b";
        EXPECT_EQ(fox::StringUtil::concatenate(source, split_char), expected);
    }

    // Combined tests for split and concatenate
    TEST(StringTest, ConcatenateAfterSplit)
    {
        const std::string original = "a,b,c";
        constexpr char split_char = ',';
        const auto parts = fox::StringUtil::split(original, split_char);
        const std::string result = fox::StringUtil::concatenate(parts, split_char);
        EXPECT_EQ(result, original);
    }

    TEST(StringTest, ConcatenateAfterSplitWithLeadingDelimiter)
    {
        const std::string original = ",a,b";
        constexpr char split_char = ',';
        const auto parts = fox::StringUtil::split(original, split_char);
        const std::string result = fox::StringUtil::concatenate(parts, split_char);
        EXPECT_EQ(result, original);
    }

    TEST(StringTest, ConcatenateAfterSplitWithTrailingDelimiter)
    {
        const std::string original = "a,b,";
        constexpr char split_char = ',';
        const auto parts = fox::StringUtil::split(original, split_char);
        const std::string result = fox::StringUtil::concatenate(parts, split_char);
        EXPECT_EQ(result, original);
    }

    TEST(StringTest, ConcatenateAfterSplitWithMultipleDelimiters)
    {
        const std::string original = "a,,b";
        constexpr char split_char = ',';
        const auto parts = fox::StringUtil::split(original, split_char);
        const std::string result = fox::StringUtil::concatenate(parts, split_char);
        EXPECT_EQ(result, original);
    }
} // namespace gtest_case
