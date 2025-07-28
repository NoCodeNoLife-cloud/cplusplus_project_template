#pragma once
#include <gtest/gtest.h>

#include "type/container/UnionSet.hpp"

namespace gtest_case {
TEST(UnionFindTest, SingleElementSelfConnection) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  EXPECT_TRUE(uf.connected(x, x));
  EXPECT_EQ(uf.find(x), x);
}

TEST(UnionFindTest, TwoElementsUnion) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  constexpr int y = 2;
  uf.unionSets(x, y);
  EXPECT_TRUE(uf.connected(x, y));
  EXPECT_EQ(uf.find(x), uf.find(y));
}

TEST(UnionFindTest, UnionByRankMergeSameRank) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  constexpr int y = 2;
  uf.unionSets(x, y);
  constexpr int z = 3;
  uf.unionSets(x, z);
  EXPECT_EQ(uf.find(z), uf.find(x));
}

TEST(UnionFindTest, PathCompression) {
  common::UnionSet<int> uf;
  constexpr int a = 1;
  constexpr int b = 2;
  constexpr int c = 3;
  uf.unionSets(a, b);
  uf.unionSets(b, c);
  uf.find(c);
  EXPECT_EQ(uf.find(c), uf.find(a));
  EXPECT_EQ(uf.find(c), a);
}

TEST(UnionFindTest, MultipleUnionsTransitivity) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  constexpr int y = 2;
  constexpr int z = 3;
  uf.unionSets(x, y);
  uf.unionSets(y, z);
  EXPECT_TRUE(uf.connected(x, z));
  EXPECT_EQ(uf.find(x), uf.find(z));
}

TEST(UnionFindTest, NonExistentElementHandling) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  constexpr int y = 2;
  EXPECT_EQ(uf.find(x), x);
  uf.find(y);
  EXPECT_FALSE(uf.connected(x, y));
}

TEST(UnionFindTest, RepeatedUnion) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  constexpr int y = 2;
  uf.unionSets(x, y);
  const bool result = uf.unionSets(x, y);
  EXPECT_FALSE(result);
}

TEST(UnionFindTest, EnsureRegisteredCreatesEntry) {
  common::UnionSet<int> uf;
  constexpr int x = 1;
  uf.find(x);
  EXPECT_EQ(uf.find(x), x);
  EXPECT_EQ(uf.parent.find(x)->second, x);
  EXPECT_EQ(uf.rank.find(x)->second, 1);
}
}  // namespace gtest_case
