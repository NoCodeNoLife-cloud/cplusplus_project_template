#include <gtest/gtest.h>

#include "type/data_structure/tree/AVLTree.hpp"

namespace gtest_case
{
    TEST(AVLTreeTest, InsertSingleNodeCheckExistence)
    {
        coco::AVLTree<int> tree;
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
    }

    TEST(AVLTreeTest, InsertDuplicateValueCheckNoGrowth)
    {
        coco::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
    }

    TEST(AVLTreeTest, InsertLeftLeftCaseCheckRotation)
    {
        coco::AVLTree<int> tree;
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertRightRightCaseCheckRotation)
    {
        coco::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertLeftRightCaseCheckRotation)
    {
        coco::AVLTree<int> tree;
        tree.insert(30);
        tree.insert(10);
        tree.insert(20);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, InsertRightLeftCaseCheckRotation)
    {
        coco::AVLTree<int> tree;
        tree.insert(10);
        tree.insert(30);
        tree.insert(20);
        EXPECT_TRUE(tree.find(10));
        EXPECT_TRUE(tree.find(20));
        EXPECT_TRUE(tree.find(30));
    }

    TEST(AVLTreeTest, RemoveLeafNodeCheckExistence)
    {
        coco::AVLTree<int> tree;
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
        coco::AVLTree<int> tree;
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
        coco::AVLTree<int> tree;
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
        coco::AVLTree<int> tree;
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
        coco::AVLTree<int> tree;
        tree.insert(20);
        EXPECT_FALSE(tree.find(99));
    }

    TEST(AVLTreeTest, InsertRemoveCheckEmptyState)
    {
        coco::AVLTree<int> tree;
        tree.insert(10);
        tree.remove(10);
        EXPECT_FALSE(tree.find(10));
    }
}
