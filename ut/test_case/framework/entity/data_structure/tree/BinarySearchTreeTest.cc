#include <gtest/gtest.h>

#include "type/data_structure/tree/BinarySearchTree.hpp"

namespace gtest_case
{
    TEST(BinarySearchTreeTest, InsertAndFindBasic)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);

        EXPECT_TRUE(tree.find(5));
        EXPECT_TRUE(tree.find(3));
        EXPECT_TRUE(tree.find(7));
        EXPECT_FALSE(tree.find(2));
    }

    TEST(BinarySearchTreeTest, EmptyTreeFindReturnsFalse)
    {
        const coco::BinarySearchTree<int32_t> tree;
        EXPECT_FALSE(tree.find(1));
    }

    TEST(BinarySearchTreeTest, RemoveLeafNode)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(3);
        tree.remove(3);

        EXPECT_FALSE(tree.find(3));
        EXPECT_TRUE(tree.find(5));
    }

    TEST(BinarySearchTreeTest, RemoveNodeWithOneChild)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(2);
        tree.remove(3);

        EXPECT_TRUE(tree.find(2));
        EXPECT_TRUE(tree.find(5));
        EXPECT_FALSE(tree.find(3));
    }

    TEST(BinarySearchTreeTest, RemoveNodeWithTwoChildren)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(6);
        tree.remove(5);

        EXPECT_FALSE(tree.find(5));
        EXPECT_TRUE(tree.find(3));
        EXPECT_TRUE(tree.find(7));
        EXPECT_TRUE(tree.find(6));
    }

    TEST(BinarySearchTreeTest, InorderTraversalOrder)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);

        testing::internal::CaptureStdout();
        tree.inorderTraversal();
        const std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "2 3 4 5 7 \n");
    }

    TEST(BinarySearchTreeTest, RemoveEmptyTreeNoop)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.remove(1);
        EXPECT_FALSE(tree.find(1));
    }

    TEST(BinarySearchTreeTest, DuplicateInserts)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(5);
        tree.insert(5);

        EXPECT_TRUE(tree.find(5));
    }

    TEST(BinarySearchTreeTest, DeleteRootWithTwoChildren)
    {
        coco::BinarySearchTree<int32_t> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(7);
        tree.insert(12);
        tree.remove(10);

        EXPECT_FALSE(tree.find(10));
        EXPECT_TRUE(tree.find(7));
        EXPECT_TRUE(tree.find(12));
        EXPECT_TRUE(tree.find(5));
        EXPECT_TRUE(tree.find(15));
    }
}
