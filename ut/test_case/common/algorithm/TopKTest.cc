#include <gtest/gtest.h>

#include "algorithm/TopK.hpp"

TEST(TopKTest, BasicTest) {
  common::TopK topK(3);
  topK.add(4);
  topK.add(5);
  topK.add(8);
  topK.add(2);

  const std::vector expected = {4, 5, 8};
  const std::vector<int> result = topK.getTopK();

  EXPECT_EQ(result, expected);
}

TEST(TopKTest, LessThanKElements) {
  common::TopK topK(5);
  topK.add(10);
  topK.add(20);
  topK.add(30);
  const std::vector expected = {10, 20, 30};
  const std::vector<int> result = topK.getTopK();

  EXPECT_EQ(result, expected);
}

TEST(TopKTest, EqualToKElements) {
  common::TopK topK(3);
  topK.add(1);
  topK.add(2);
  topK.add(3);

  const std::vector expected = {1, 2, 3};
  const std::vector<int> result = topK.getTopK();

  EXPECT_EQ(result, expected);
}

TEST(TopKTest, Duplicates) {
  common::TopK topK(3);
  topK.add(5);
  topK.add(5);
  topK.add(5);
  topK.add(5);

  const std::vector expected = {5, 5, 5};
  const std::vector<int> result = topK.getTopK();

  EXPECT_EQ(result, expected);
}

TEST(TopKTest, LargeNumbers) {
  common::TopK topK(2);
  topK.add(1000000);
  topK.add(999999);
  topK.add(1000001);

  const std::vector expected = {1000000, 1000001};
  const std::vector<int> result = topK.getTopK();

  EXPECT_EQ(result, expected);
}
