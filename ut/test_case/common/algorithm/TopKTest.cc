#include <gtest/gtest.h>

#include "algorithm/TopK.hpp"

TEST(TopKTest, BasicTest)
{
    fox::TopK topK(3);
    topK.add(4);
    topK.add(5);
    topK.add(8);
    topK.add(2);

    const std::vector expected = {4, 5, 8};
    const std::vector<int32_t> result = topK.getTopK();

    EXPECT_EQ(result, expected);
}

TEST(TopKTest, LessThanKElements)
{
    fox::TopK topK(5);
    topK.add(10);
    topK.add(20);
    topK.add(30);
    const std::vector expected = {10, 20, 30};
    const std::vector<int32_t> result = topK.getTopK();

    EXPECT_EQ(result, expected);
}

TEST(TopKTest, EqualToKElements)
{
    fox::TopK topK(3);
    topK.add(1);
    topK.add(2);
    topK.add(3);

    const std::vector expected = {1, 2, 3};
    const std::vector<int32_t> result = topK.getTopK();

    EXPECT_EQ(result, expected);
}

TEST(TopKTest, Duplicates)
{
    fox::TopK topK(3);
    topK.add(5);
    topK.add(5);
    topK.add(5);
    topK.add(5);

    const std::vector expected = {5, 5, 5};
    const std::vector<int32_t> result = topK.getTopK();

    EXPECT_EQ(result, expected);
}

TEST(TopKTest, LargeNumbers)
{
    fox::TopK topK(2);
    topK.add(1000000);
    topK.add(999999);
    topK.add(1000001);

    const std::vector expected = {1000000, 1000001};
    const std::vector<int32_t> result = topK.getTopK();

    EXPECT_EQ(result, expected);
}
