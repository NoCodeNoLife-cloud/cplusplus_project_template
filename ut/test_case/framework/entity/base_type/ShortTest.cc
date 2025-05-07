#include <entity/base_type/Short.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(ShortTest, ConstructorInitializesValueCorrectly) {
    const common::Short short_obj(42);
    EXPECT_EQ(short_obj.shortValue(), 42);
  }

  TEST(ShortTest, MinAndMaxValues) {
    constexpr auto min_val = common::Short::MIN_VALUE;
    constexpr auto max_val = common::Short::MAX_VALUE;
    const common::Short min_obj(min_val);
    const common::Short max_obj(max_val);
    EXPECT_EQ(min_obj.shortValue(), min_val);
    EXPECT_EQ(max_obj.shortValue(), max_val);
  }

  TEST(ShortTest, ExplicitConversionToShort) {
    const common::Short obj(123);
    const auto converted = static_cast<int16_t>(obj);
    EXPECT_EQ(converted, 123);
  }

  TEST(ShortTest, ToStringReturnsCorrectString) {
    const common::Short obj(5);
    EXPECT_EQ(obj.toString(), "5");
  }

  TEST(ShortTest, EqualsComparesValuesCorrectly) {
    const common::Short a(10);
    const common::Short b(10);
    const common::Short c(20);
    EXPECT_TRUE(a.equals(b));
    EXPECT_FALSE(a.equals(c));
  }

  TEST(ShortTest, CompareToReturnsCorrectResult) {
    const common::Short a(5);
    const common::Short b(10);
    const common::Short c(5);
    EXPECT_EQ(a.compareTo(c), 0);
    EXPECT_LT(a.compareTo(b), 0);
    EXPECT_GT(b.compareTo(a), 0);
  }

  TEST(ShortTest, EqualityOperatorsWorkCorrectly) {
    const common::Short a(5);
    const common::Short b(5);
    const common::Short c(10);
    EXPECT_TRUE(std::is_eq(a <=> b));
    EXPECT_FALSE(std::is_eq(a <=> c));
    EXPECT_FALSE(std::is_neq(a <=> b));
    EXPECT_TRUE(std::is_neq(a <=> c));
  }

  TEST(ShortTest, RelationalOperatorsWorkCorrectly) {
    const common::Short a(5);
    const common::Short b(10);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(b < a);
  }

  TEST(ShortTest, ArithmeticOperatorsReturnCorrectValues) {
    const common::Short a(10);
    const common::Short b(3);
    const common::Short sum = a + b;
    const common::Short diff = a - b;
    const common::Short prod = a * b;
    const common::Short div = a / b;
    const common::Short mod = a % b;
    EXPECT_EQ(sum.shortValue(), 13);
    EXPECT_EQ(diff.shortValue(), 7);
    EXPECT_EQ(prod.shortValue(), 30);
    EXPECT_EQ(div.shortValue(), 3);
    EXPECT_EQ(mod.shortValue(), 1);
  }

  TEST(ShortTest, DivisionByZeroThrowsOverflowError) {
    const common::Short a(5);
    const common::Short zero(0);
    EXPECT_THROW(a / zero, std::overflow_error);
  }

  TEST(ShortTest, ModuloByZeroThrowsOverflowError) {
    const common::Short a(5);
    const common::Short zero(0);
    EXPECT_THROW(a % zero, std::overflow_error);
  }

  TEST(ShortTest, ParseValidStrings) {
    const auto str1 = "123";
    const auto str2 = "-456";
    const common::Short s1 = common::Short::parseShort(str1);
    const common::Short s2 = common::Short::parseShort(str2);
    EXPECT_EQ(s1.shortValue(), 123);
    EXPECT_EQ(s2.shortValue(), -456);
  }

  TEST(ShortTest, ParseInvalidStringsThrowsInvalidArgument) {
    const auto invalid_str = "abc";
    EXPECT_THROW(common::Short::parseShort(invalid_str), std::invalid_argument);
  }

  TEST(ShortTest, ParseOutOfRangeValuesThrowsOutOfRange) {
    const auto over_max = std::to_string(static_cast<int>(common::Short::MAX_VALUE) + 1);
    const auto under_min = std::to_string(static_cast<int>(common::Short::MIN_VALUE) - 1);
    EXPECT_THROW(common::Short::parseShort(over_max), std::out_of_range);
    EXPECT_THROW(common::Short::parseShort(under_min), std::out_of_range);
  }

  TEST(ShortTest, AdditionOverflowWrapsAround) {
    const common::Short max_val(common::Short::MAX_VALUE);
    const common::Short one(1);
    const common::Short result = max_val + one;
    EXPECT_EQ(result.shortValue(), -32768);
  }

  TEST(ShortTest, SubtractionUnderflowWrapsAround) {
    const common::Short min_val(common::Short::MIN_VALUE);
    const common::Short one(1);
    const common::Short result = min_val - one;
    EXPECT_EQ(result.shortValue(), 32767);
  }
}
