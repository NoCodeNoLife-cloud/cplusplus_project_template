#include <gtest/gtest.h>

#include <stdexcept>

#include "type/util/ArraysToolkit.hpp"

namespace gtest_case
{
    TEST(ArraysUtilTest, AsList_ConvertsIntArrayToVector)
    {
        constexpr int32_t arr[] = {1, 2, 3};
        const std::vector<int32_t> result = fox::ArraysToolkit::asList(arr, 3);
        const std::vector expected = {1, 2, 3};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, AsList_ConvertsStringArrayToVector)
    {
        const std::string arr[] = {"a", "b"};
        const std::vector<std::string> result = fox::ArraysToolkit::asList(arr, 2);
        const std::vector<std::string> expected = {"a", "b"};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundAtBeginning)
    {
        int32_t arr[] = {1, 3, 5, 7};
        fox::ArraysToolkit::sort(arr, 4);
        const int32_t result = fox::ArraysToolkit::binarySearch(arr, 4, 1);
        EXPECT_EQ(result, 0);
    }

    TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundInMiddle)
    {
        int32_t arr[] = {1, 3, 5, 7};
        fox::ArraysToolkit::sort(arr, 4);
        const int32_t result = fox::ArraysToolkit::binarySearch(arr, 4, 5);
        EXPECT_EQ(result, 2);
    }

    TEST(ArraysUtilTest, BinarySearch_ReturnsIndexWhenElementFoundAtEnd)
    {
        int32_t arr[] = {1, 3, 5, 7};
        fox::ArraysToolkit::sort(arr, 4);
        const int32_t result = fox::ArraysToolkit::binarySearch(arr, 4, 7);
        EXPECT_EQ(result, 3);
    }

    TEST(ArraysUtilTest, BinarySearch_ReturnsNegativeOneWhenElementNotFound)
    {
        int32_t arr[] = {1, 3, 5, 7};
        fox::ArraysToolkit::sort(arr, 4);
        const int32_t result = fox::ArraysToolkit::binarySearch(arr, 4, 6);
        EXPECT_EQ(result, -1);
    }

    TEST(ArraysUtilTest, BinarySearchWithRange_ReturnsIndexWithinSpecifiedRange)
    {
        int32_t arr[] = {1, 3, 5, 7, 9};
        fox::ArraysToolkit::sort(arr, 5);
        const int32_t result = fox::ArraysToolkit::binarySearch(arr, 1, 4, 7);
        EXPECT_EQ(result, 3);
    }

    TEST(ArraysUtilTest, BinarySearchWithRange_ThrowsExceptionForInvalidRange)
    {
        constexpr int32_t arr[] = {1, 3, 5};
        EXPECT_THROW(fox::ArraysToolkit::binarySearch(arr, 2, 1, 3), std::out_of_range);
    }

    TEST(ArraysUtilTest, CopyOf_ShrinksArraySize)
    {
        const int32_t original[] = {1, 2, 3, 4, 5};
        const std::vector<int32_t> result = fox::ArraysToolkit::copyOf(original, 5, 3);
        const std::vector expected = {1, 2, 3};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, CopyOf_ExpandsArraySizeWithDefaultValues)
    {
        constexpr int32_t original[] = {1, 2};
        const std::vector<int32_t> result = fox::ArraysToolkit::copyOf(original, 2, 4);
        const std::vector expected = {1, 2, 0, 0};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, CopyOfRange_CopiesFullRange)
    {
        constexpr int32_t original[] = {1, 2, 3, 4};
        const std::vector<int32_t> result = fox::ArraysToolkit::copyOfRange(original, 0, 4);
        const std::vector expected = {1, 2, 3, 4};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, CopyOfRange_CopiesPartialRange)
    {
        constexpr int32_t original[] = {1, 2, 3, 4};
        const std::vector<int32_t> result = fox::ArraysToolkit::copyOfRange(original, 1, 3);
        const std::vector expected = {2, 3};
        EXPECT_EQ(result, expected);
    }

    TEST(ArraysUtilTest, CopyOfRange_ThrowsExceptionForFromGreaterThanTo)
    {
        constexpr int32_t original[] = {1, 2, 3};
        EXPECT_THROW(fox::ArraysToolkit::copyOfRange(original, 3, 1), std::out_of_range);
    }

    TEST(ArraysUtilTest, Equals_ReturnsTrueForIdenticalArrays)
    {
        constexpr int32_t a[] = {1, 2, 3};
        constexpr int32_t b[] = {1, 2, 3};
        const bool result = fox::ArraysToolkit::equals(a, 3, b, 3);
        EXPECT_TRUE(result);
    }

    TEST(ArraysUtilTest, Equals_ReturnsFalseForDifferentLengths)
    {
        constexpr int32_t a[] = {1, 2};
        constexpr int32_t b[] = {1, 2, 3};
        const bool result = fox::ArraysToolkit::equals(a, 2, b, 3);
        EXPECT_FALSE(result);
    }

    TEST(ArraysUtilTest, Equals_ReturnsFalseForSameLengthDifferentContent)
    {
        constexpr int32_t a[] = {1, 2, 3};
        constexpr int32_t b[] = {1, 4, 3};
        const bool result = fox::ArraysToolkit::equals(a, 3, b, 3);
        EXPECT_FALSE(result);
    }

    TEST(ArraysUtilTest, Fill_FillsEntireArrayWithValue)
    {
        int32_t arr[4];
        fox::ArraysToolkit::fill(arr, 4, 7);
        for (int32_t i : arr)
        {
            EXPECT_EQ(i, 7);
        }
    }

    TEST(ArraysUtilTest, Sort_FullSortsArray)
    {
        int32_t arr[] = {5, 2, 8, 1};
        fox::ArraysToolkit::sort(arr, 4);
        constexpr int32_t expected[] = {1, 2, 5, 8};
        EXPECT_TRUE(std::equal(arr, arr + 4, expected));
    }

    TEST(ArraysUtilTest, Sort_PartialSortsArray)
    {
        int32_t arr[] = {5, 2, 8, 1, 3};
        fox::ArraysToolkit::sort(arr, 1, 4);
        const int32_t expected[] = {5, 1, 2, 8, 3};
        EXPECT_TRUE(std::equal(arr, arr + 5, expected));
    }

    TEST(ArraysUtilTest, Sort_ThrowsExceptionForInvalidRange)
    {
        int32_t arr[] = {1, 2, 3};
        EXPECT_THROW(fox::ArraysToolkit::sort(arr, 2, 1), std::out_of_range);
    }

    TEST(ArraysUtilTest, ToString_ReturnsSingleElementString)
    {
        constexpr int32_t arr[] = {42};
        const std::string result = fox::ArraysToolkit::toString(arr, 1);
        EXPECT_EQ(result, "[42]");
    }

    TEST(ArraysUtilTest, ToString_ReturnsMultiElementString)
    {
        constexpr int32_t arr[] = {1, 2, 3};
        const std::string result = fox::ArraysToolkit::toString(arr, 3);
        EXPECT_EQ(result, "[1, 2, 3]");
    }
} // namespace gtest_case
