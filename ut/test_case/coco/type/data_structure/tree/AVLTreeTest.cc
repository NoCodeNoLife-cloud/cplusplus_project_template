#include <gtest/gtest.h>

#include "type/data_structure/tree/AVLTree.hpp"

namespace gtest_case
{
    TEST(AVLTreeTest, InsertSingleNodeCheckExistence)
    {
        common::AVLTree<int> tree;
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
    }

    TEST(AVLTreeTest, InsertDuplicateValueCheckNoGrowth)
    {
        common::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
    }

    TEST(AVLTreeTest, InsertLeftLeftCaseCheckRotation)
    {
        common::AVLTree<int> tree;
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertRightRightCaseCheckRotation)
    {
        common::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertLeftRightCaseCheckRotation)
    {
        common::AVLTree<int> tree;
        tree.insert(30);
        tree.insert(10);
        tree.insert(20);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertRightLeftCaseCheckRotation)
    {
        common::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(30);
        tree.insert(20);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, RemoveLeafNodeCheckExistence)
    {
        common::AVLTree<int> tree;
        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.remove(10);
        EXPECT_FALSE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, RemoveNodeWithOneChildCheckStructure)
    {
        common::AVLTree<int> tree;
        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.insert(5);
        tree.remove(10);
        EXPECT_FALSE(tree.find(10));
        EXPECT_TRUE(tree.find(5));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, RemoveNodeWithTwoChildrenCheckSuccessor)
    {
        common::AVLTree<int> tree;
        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.insert(25);
        tree.insert(35);
        tree.remove(30);
        EXPECT_FALSE(tree.find(30));
        EXPECT_TRUE(tree.find(25));
        EXPECT_TRUE(tree.find(35));
    }

    TEST(AVLTreeTest, RemoveRootNodeCheckNewRoot)
    {
        common::AVLTree<int> tree;
        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.remove(20);
        EXPECT_FALSE(tree.find(20));
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, FindNonExistentValueCheckFalse)
    {
        common::AVLTree<int> tree;
        tree.insert(20);
        EXPECT_FALSE(tree.find(99));
    }

    TEST(AVLTreeTest, InsertRemoveCheckEmptyState)
    {
        common::AVLTree<int> tree;
        tree.insert(10);
        tree.remove(10);
        EXPECT_FALSE(tree.find(10));
    }
}
