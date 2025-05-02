#include <regex>
#include <stdexcept>
#include <vector>
#include <entity/base_type/String.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(StringTest, Constructors) {
    const framework::entity::base_type::String s1;
    EXPECT_TRUE(s1.isEmpty());
    const framework::entity::base_type::String s2("hello");
    EXPECT_EQ(s2.toStdString(), "hello");
    const framework::entity::base_type::String s3(std::string("world"));
    EXPECT_EQ(s3.toStdString(), "world");
  }

  TEST(StringTest, charAt) {
    const framework::entity::base_type::String s("abc");
    EXPECT_EQ(s.charAt(0), 'a');
    EXPECT_EQ(s.charAt(1), 'b');
    EXPECT_EQ(s.charAt(2), 'c');
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.charAt(-1), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.charAt(3), std::out_of_range);
  }

  TEST(StringTest, length) {
    const framework::entity::base_type::String s1;
    EXPECT_EQ(s1.length(), 0);
    const framework::entity::base_type::String s2("abc");
    EXPECT_EQ(s2.length(), 3);
  }

  TEST(StringTest, substring) {
    const framework::entity::base_type::String s("hello world");
    EXPECT_EQ(s.substring(0, 5).toStdString(), "hello");
    EXPECT_EQ(s.substring(6, 11).toStdString(), "world");
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.substring(-1, 5), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.substring(0, 12), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.substring(3, 2), std::out_of_range);
  }

  TEST(StringTest, concat) {
    const framework::entity::base_type::String s1("abc");
    const framework::entity::base_type::String s2("def");
    const framework::entity::base_type::String result = s1.concat(s2);
    EXPECT_EQ(result.toStdString(), "abcdef");
  }

  TEST(StringTest, compareTo) {
    const framework::entity::base_type::String s1("abc");
    const framework::entity::base_type::String s2("abd");
    const framework::entity::base_type::String s3("abc");
    EXPECT_LT(s1.compareTo(s2), 0);
    EXPECT_GT(s2.compareTo(s1), 0);
    EXPECT_EQ(s1.compareTo(s3), 0);
  }

  TEST(StringTest, compareToIgnoreCase) {
    const framework::entity::base_type::String s1("abc");
    const framework::entity::base_type::String s2("ABC");
    EXPECT_EQ(s1.compareToIgnoreCase(s2), 0);
    const framework::entity::base_type::String s3("abd");
    EXPECT_LT(s1.compareToIgnoreCase(s3), 0);
  }

  TEST(StringTest, isEmpty) {
    const framework::entity::base_type::String s1;
    EXPECT_TRUE(s1.isEmpty());
    const framework::entity::base_type::String s2("abc");
    EXPECT_FALSE(s2.isEmpty());
  }

  TEST(StringTest, contains) {
    const framework::entity::base_type::String s("hello world");
    const framework::entity::base_type::String sub("world");
    EXPECT_TRUE(s.contains(sub));
    const framework::entity::base_type::String notSub("earth");
    EXPECT_FALSE(s.contains(notSub));
  }

  TEST(StringTest, replace) {
    const framework::entity::base_type::String s("abracadabra");
    const framework::entity::base_type::String result = s.replace('a', 'z');
    EXPECT_EQ(result.toStdString(), "zbrzczdzbrz");
  }

  TEST(StringTest, toLowerCase) {
    const framework::entity::base_type::String s("AbC");
    const framework::entity::base_type::String result = s.toLowerCase();
    EXPECT_EQ(result.toStdString(), "abc");
  }

  TEST(StringTest, toUpperCase) {
    const framework::entity::base_type::String s("aBc");
    const framework::entity::base_type::String result = s.toUpperCase();
    EXPECT_EQ(result.toStdString(), "ABC");
  }

  TEST(StringTest, trim) {
    const framework::entity::base_type::String s("  \t\n\rtrim me   \t\n\r");
    const framework::entity::base_type::String result = s.trim();
    EXPECT_EQ(result.toStdString(), "trim me");
    const framework::entity::base_type::String empty;
    EXPECT_TRUE(empty.trim().isEmpty());
  }

  TEST(StringTest, toStdString) {
    const std::string stdStr = "hello";
    const framework::entity::base_type::String s(stdStr);
    EXPECT_EQ(s.toStdString(), stdStr);
  }

  TEST(StringTest, equals) {
    const framework::entity::base_type::String s1("abc");
    const framework::entity::base_type::String s2("abc");
    const framework::entity::base_type::String s3("def");
    EXPECT_TRUE(s1.equals(s2));
    EXPECT_FALSE(s1.equals(s3));
  }

  TEST(StringTest, codePointAt) {
    const framework::entity::base_type::String s("abc");
    EXPECT_EQ(s.codePointAt(0), 'a');
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.codePointAt(3), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.codePointAt(-1), std::out_of_range);
  }

  TEST(StringTest, codePointBefore) {
    const framework::entity::base_type::String s("abc");
    EXPECT_EQ(s.codePointBefore(1), 'a');
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.codePointBefore(0), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.codePointBefore(4), std::out_of_range);
  }

  TEST(StringTest, codePointCount) {
    const framework::entity::base_type::String s("abcd");
    EXPECT_EQ(s.codePointCount(1, 3), 2);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.codePointCount(-1, 3), std::out_of_range);
  }

  TEST(StringTest, indexOfChar) {
    const framework::entity::base_type::String s("abracadabra");
    EXPECT_EQ(s.indexOf('a'), 0);
    EXPECT_EQ(s.indexOf('c'), 4);
    EXPECT_EQ(s.indexOf('z'), -1);
  }

  TEST(StringTest, indexOfCharFromIndex) {
    const framework::entity::base_type::String s("abracadabra");
    EXPECT_EQ(s.indexOf('a', 1), 3);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.indexOf('a', -1), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.indexOf('a', 11), std::out_of_range);
  }

  TEST(StringTest, indexOfString) {
    const framework::entity::base_type::String s("abracadabra");
    const framework::entity::base_type::String sub1("cad");
    const framework::entity::base_type::String sub2("xyz");
    EXPECT_EQ(s.indexOf(sub1), 4);
    EXPECT_EQ(s.indexOf(sub2), -1);
  }

  TEST(StringTest, indexOfStringFromIndex) {
    const framework::entity::base_type::String s("abracadabra");
    const framework::entity::base_type::String sub("abra");
    EXPECT_EQ(s.indexOf(sub, 1), 7);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.indexOf(sub, -1), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.indexOf(sub, 11), std::out_of_range);
  }

  TEST(StringTest, lastIndexOfChar) {
    const framework::entity::base_type::String s("abracadabra");
    EXPECT_EQ(s.lastIndexOf('a'), 10);
    EXPECT_EQ(s.lastIndexOf('z'), -1);
  }

  TEST(StringTest, lastIndexOfCharFromIndex) {
    const framework::entity::base_type::String s("abracadabra");
    EXPECT_EQ(s.lastIndexOf('a', 7), 7);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.lastIndexOf('a', -1), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.lastIndexOf('a', 11), std::out_of_range);
  }

  TEST(StringTest, lastIndexOfString) {
    const framework::entity::base_type::String s("abracadabra");
    const framework::entity::base_type::String sub1("abra");
    const framework::entity::base_type::String sub2("xyz");
    EXPECT_EQ(s.lastIndexOf(sub1), 7);
    EXPECT_EQ(s.lastIndexOf(sub2), -1);
  }

  TEST(StringTest, lastIndexOfStringFromIndex) {
    const framework::entity::base_type::String s("abracadabra");
    const framework::entity::base_type::String sub("a");
    EXPECT_EQ(s.lastIndexOf(sub, 5), 5);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.lastIndexOf(sub, -1), std::out_of_range);
    // ReSharper disable once CppNoDiscardExpression
    EXPECT_THROW(s.lastIndexOf(sub, 11), std::out_of_range);
  }

  TEST(StringTest, matches) {
    const framework::entity::base_type::String s("12345");
    EXPECT_TRUE(s.matches("\\d+"));
    EXPECT_FALSE(s.matches("\\d{3}"));
  }

  TEST(StringTest, replaceAll) {
    const framework::entity::base_type::String s("a1b2c3");
    const framework::entity::base_type::String result = s.replaceAll("\\d+", "X");
    EXPECT_EQ(result.toStdString(), "aXbXcX");
  }

  TEST(StringTest, replaceFirst) {
    const framework::entity::base_type::String s("a1b2c3");
    const framework::entity::base_type::String result = s.replaceFirst("\\d", "X");
    EXPECT_EQ(result.toStdString(), "aXb2c3");
  }

  TEST(StringTest, split) {
    const framework::entity::base_type::String s("a,b,c,d");
    const std::vector<framework::entity::base_type::String> result = s.split(",");
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].toStdString(), "a");
    EXPECT_EQ(result[1].toStdString(), "b");
    EXPECT_EQ(result[2].toStdString(), "c");
    EXPECT_EQ(result[3].toStdString(), "d");
  }

  TEST(StringTest, splitWithLimit) {
    const framework::entity::base_type::String s("a,b,c,d");
    const std::vector<framework::entity::base_type::String> result = s.split(",", 2);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].toStdString(), "a");
    EXPECT_EQ(result[1].toStdString(), "b,c,d");
  }

  TEST(StringTest, valueOfBool) {
    const auto sTrue = framework::entity::base_type::String::valueOf(true);
    EXPECT_EQ(sTrue.toStdString(), "true");
    const auto sFalse = framework::entity::base_type::String::valueOf(false);
    EXPECT_EQ(sFalse.toStdString(), "false");
  }

  TEST(StringTest, valueOfChar) {
    const auto s = framework::entity::base_type::String::valueOf('X');
    EXPECT_EQ(s.toStdString(), "X");
  }

  TEST(StringTest, valueOfCharArray) {
    const auto str = "hello";
    const auto s = framework::entity::base_type::String::valueOf(str);
    EXPECT_EQ(s.toStdString(), str);
  }

  TEST(StringTest, valueOfInt32) {
    const auto s = framework::entity::base_type::String::valueOf(123);
    EXPECT_EQ(s.toStdString(), "123");
  }

  TEST(StringTest, valueOfInt64) {
    const auto s = framework::entity::base_type::String::valueOf(1234567890123LL);
    EXPECT_EQ(s.toStdString(), "1234567890123");
  }

  TEST(StringTest, valueOfFloat) {
    const auto s = framework::entity::base_type::String::valueOf(1.23f);
    EXPECT_EQ(s.toStdString(), "1.230000");
  }

  TEST(StringTest, valueOfDouble) {
    const auto s = framework::entity::base_type::String::valueOf(1.23);
    EXPECT_EQ(s.toStdString(), "1.230000");
  }

  TEST(StringTest, valueOfString) {
    const framework::entity::base_type::String s("copy");
    const auto result = framework::entity::base_type::String::valueOf(s);
    EXPECT_EQ(result.toStdString(), "copy");
  }

  TEST(StringTest, regionMatches) {
    const framework::entity::base_type::String s1("hello world");
    const framework::entity::base_type::String s2("worldwide");
    EXPECT_TRUE(s1.regionMatches(6, s2, 0, 5));
    EXPECT_FALSE(s1.regionMatches(6, s2, 0, 6));
  }

  TEST(StringTest, regionMatchesIgnoreCase) {
    const framework::entity::base_type::String s1("HELLO world");
    const framework::entity::base_type::String s2("hello WORLD");
    EXPECT_TRUE(s1.regionMatches(true, 0, s2, 0, 5));
    EXPECT_FALSE(s1.regionMatches(false, 6, s2, 6, 5));
  }

  TEST(StringTest, Operators) {
    const framework::entity::base_type::String s1("hello");
    const framework::entity::base_type::String s2(" world");
    const framework::entity::base_type::String s3 = s1 + s2;
    EXPECT_EQ(s3.toStdString(), "hello world");
    const framework::entity::base_type::String s4("hello");
    EXPECT_TRUE(s1 == s4);
    EXPECT_FALSE(s1 != s4);
  }

  TEST(StringTest, toString) {
    const framework::entity::base_type::String s("test");
    const std::string result = s.toString();
    EXPECT_EQ(result, "String{data: test}");
  }
} // namespace gtest_case
