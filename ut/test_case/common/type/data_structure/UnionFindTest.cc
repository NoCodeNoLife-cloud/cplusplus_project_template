#pragma once
#include <gtest/gtest.h>

#include "type/container/UnionSet.hpp"

namespace gtest_case
{
    TEST(UnionFindTest, SingleElementSelfConnection)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        EXPECT_TRUE(uf.connected(x, x));
        EXPECT_EQ(uf.find(x), x);
    }

    TEST(UnionFindTest, TwoElementsUnion)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        constexpr int32_t y = 2;
        const bool result = uf.unionSets(x, y);
        EXPECT_TRUE(result);
        EXPECT_TRUE(uf.connected(x, y));
        EXPECT_EQ(uf.find(x), uf.find(y));
    }

    TEST(UnionFindTest, UnionByRankMergeSameRank)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        constexpr int32_t y = 2;
        const bool result1 = uf.unionSets(x, y);
        EXPECT_TRUE(result1);
        constexpr int32_t z = 3;
        const bool result2 = uf.unionSets(x, z);
        EXPECT_TRUE(result2);
        EXPECT_EQ(uf.find(z), uf.find(x));
    }

    TEST(UnionFindTest, PathCompression)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t a = 1;
        constexpr int32_t b = 2;
        constexpr int32_t c = 3;
        const bool result1 = uf.unionSets(a, b);
        EXPECT_TRUE(result1);
        const bool result2 = uf.unionSets(b, c);
        EXPECT_TRUE(result2);
        uf.find(c);
        EXPECT_EQ(uf.find(c), uf.find(a));
        EXPECT_EQ(uf.find(c), a);
    }

    TEST(UnionFindTest, MultipleUnionsTransitivity)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        constexpr int32_t y = 2;
        const bool result1 = uf.unionSets(x, y);
        EXPECT_TRUE(result1);
        constexpr int32_t z = 3;
        const bool result2 = uf.unionSets(y, z);
        EXPECT_TRUE(result2);
        EXPECT_TRUE(uf.connected(x, z));
        EXPECT_EQ(uf.find(x), uf.find(z));
    }

    TEST(UnionFindTest, NonExistentElementHandling)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        constexpr int32_t y = 2;
        EXPECT_EQ(uf.find(x), x);
        uf.find(y);
        EXPECT_FALSE(uf.connected(x, y));
    }

    TEST(UnionFindTest, RepeatedUnion)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        constexpr int32_t y = 2;
        const bool firstResult = uf.unionSets(x, y);
        EXPECT_TRUE(firstResult);
        const bool result = uf.unionSets(x, y);
        EXPECT_FALSE(result);
    }

    TEST(UnionFindTest, EnsureRegisteredCreatesEntry)
    {
        fox::UnionSet<int32_t> uf;
        constexpr int32_t x = 1;
        uf.find(x);
        EXPECT_EQ(uf.find(x), x);
        EXPECT_EQ(uf.parent.find(x)->second, x);
        EXPECT_EQ(uf.rank.find(x)->second, 1);
    }
} // namespace gtest_case
