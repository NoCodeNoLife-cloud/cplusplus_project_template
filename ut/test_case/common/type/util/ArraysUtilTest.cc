#include <gtest/gtest.h>

#include <stdexcept>

#include "type/util/ArraysUtil.hpp"

namespace gtest_case {
TEST(ArraysUtilTest, AsList_ConvertsIntArrayToVector) {
  constexpr int arr[] = {1, 2, 3};
  const std::vector<int> result = common::ArraysUtil::asList(arr, 3);
  const std::vector expected = {1, 2, 3};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, AsList_ConvertsStringArrayToVector) {
  const std::string arr[] = {"a", "b"};
  const std::vector<std::string> result = common::ArraysUtil::asList(arr, 2);
  const std::vector<std::string> expected = {"a", "b"};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundAtBeginning) {
  int arr[] = {1, 3, 5, 7};
  common::ArraysUtil::sort(arr, 4);
  const int32_t result = common::ArraysUtil::binarySearch(arr, 4, 1);
  EXPECT_EQ(result, 0);
}

TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundInMiddle) {
  int arr[] = {1, 3, 5, 7};
  common::ArraysUtil::sort(arr, 4);
  const int32_t result = common::ArraysUtil::binarySearch(arr, 4, 5);
  EXPECT_EQ(result, 2);
}

TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundAtEnd) {
  int arr[] = {1, 3, 5, 7};
  common::ArraysUtil::sort(arr, 4);
  const int32_t result = common::ArraysUtil::binarySearch(arr, 4, 7);
  EXPECT_EQ(result, 3);
}

TEST(ArraysUtilTest, BinarySearch_ReturnsNegativeOneWhenElementNotFound) {
  int arr[] = {1, 3, 5, 7};
  common::ArraysUtil::sort(arr, 4);
  const int32_t result = common::ArraysUtil::binarySearch(arr, 4, 6);
  EXPECT_EQ(result, -1);
}

TEST(ArraysUtilTest, BinarySearchWithRange_ReturnsIndexWithinSpecifiedRange) {
  int arr[] = {1, 3, 5, 7, 9};
  common::ArraysUtil::sort(arr, 5);
  const int32_t result = common::ArraysUtil::binarySearch(arr, 1, 4, 7);
  EXPECT_EQ(result, 3);
}

TEST(ArraysUtilTest, BinarySearchWithRange_ThrowsExceptionForInvalidRange) {
  constexpr int arr[] = {1, 3, 5};
  EXPECT_THROW(common::ArraysUtil::binarySearch(arr, 2, 1, 3), std::out_of_range);
}

TEST(ArraysUtilTest, CopyOf_ShrinksArraySize) {
  const int original[] = {1, 2, 3, 4, 5};
  const std::vector<int> result = common::ArraysUtil::copyOf(original, 5, 3);
  const std::vector expected = {1, 2, 3};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, CopyOf_ExpandsArraySizeWithDefaultValues) {
  constexpr int original[] = {1, 2};
  const std::vector<int> result = common::ArraysUtil::copyOf(original, 2, 4);
  const std::vector expected = {1, 2, 0, 0};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, CopyOfRange_CopiesFullRange) {
  constexpr int original[] = {1, 2, 3, 4};
  const std::vector<int> result = common::ArraysUtil::copyOfRange(original, 0, 4);
  const std::vector expected = {1, 2, 3, 4};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, CopyOfRange_CopiesPartialRange) {
  constexpr int original[] = {1, 2, 3, 4};
  const std::vector<int> result = common::ArraysUtil::copyOfRange(original, 1, 3);
  const std::vector expected = {2, 3};
  EXPECT_EQ(result, expected);
}

TEST(ArraysUtilTest, CopyOfRange_ThrowsExceptionForFromGreaterThanTo) {
  constexpr int original[] = {1, 2, 3};
  EXPECT_THROW(common::ArraysUtil::copyOfRange(original, 3, 1), std::out_of_range);
}

TEST(ArraysUtilTest, Equals_ReturnsTrueForIdenticalArrays) {
  constexpr int a[] = {1, 2, 3};
  constexpr int b[] = {1, 2, 3};
  const bool result = common::ArraysUtil::equals(a, 3, b, 3);
  EXPECT_TRUE(result);
}

TEST(ArraysUtilTest, Equals_ReturnsFalseForDifferentLengths) {
  constexpr int a[] = {1, 2};
  constexpr int b[] = {1, 2, 3};
  const bool result = common::ArraysUtil::equals(a, 2, b, 3);
  EXPECT_FALSE(result);
}

TEST(ArraysUtilTest, Equals_ReturnsFalseForSameLengthDifferentContent) {
  constexpr int a[] = {1, 2, 3};
  constexpr int b[] = {1, 4, 3};
  const bool result = common::ArraysUtil::equals(a, 3, b, 3);
  EXPECT_FALSE(result);
}

TEST(ArraysUtilTest, Fill_FillsEntireArrayWithValue) {
  int arr[4];
  common::ArraysUtil::fill(arr, 4, 7);
  for (int i : arr) {
    EXPECT_EQ(i, 7);
  }
}

TEST(ArraysUtilTest, Sort_FullSortsArray) {
  int arr[] = {5, 2, 8, 1};
  common::ArraysUtil::sort(arr, 4);
  constexpr int expected[] = {1, 2, 5, 8};
  EXPECT_TRUE(std::equal(arr, arr + 4, expected));
}

TEST(ArraysUtilTest, Sort_PartialSortsArray) {
  int arr[] = {5, 2, 8, 1, 3};
  common::ArraysUtil::sort(arr, 1, 4);
  const int expected[] = {5, 1, 2, 8, 3};
  EXPECT_TRUE(std::equal(arr, arr + 5, expected));
}

TEST(ArraysUtilTest, Sort_ThrowsExceptionForInvalidRange) {
  int arr[] = {1, 2, 3};
  EXPECT_THROW(common::ArraysUtil::sort(arr, 2, 1), std::out_of_range);
}

TEST(ArraysUtilTest, ToString_ReturnsSingleElementString) {
  constexpr int arr[] = {42};
  const std::string result = common::ArraysUtil::toString(arr, 1);
  EXPECT_EQ(result, "[42]");
}

TEST(ArraysUtilTest, ToString_ReturnsMultiElementString) {
  constexpr int arr[] = {1, 2, 3};
  const std::string result = common::ArraysUtil::toString(arr, 3);
  EXPECT_EQ(result, "[1, 2, 3]");
}
}  // namespace gtest_case
