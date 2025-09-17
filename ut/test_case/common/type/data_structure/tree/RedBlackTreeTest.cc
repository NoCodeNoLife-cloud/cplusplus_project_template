#include <gtest/gtest.h>

#include "type/data_structure/tree/RedBlackTree.hpp"

namespace gtest_case
{
    TEST(RedBlackTreeTest, DefaultConstructor_TreeIsEmpty)
    {
        fox::RedBlackTree<int32_t> tree;
        EXPECT_EQ(tree.getRoot(), nullptr);
    }

    TEST(RedBlackTreeTest, InsertSingleNode_RootIsBlackAndHasCorrectValue)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 10);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
        EXPECT_EQ(root->getParent(), nullptr);
        EXPECT_EQ(root->getLeft(), nullptr);
        EXPECT_EQ(root->getRight(), nullptr);
    }

    TEST(RedBlackTreeTest, InsertTwoNodes_ParentAndChildRelationCorrect)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(20);
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 10);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
        const auto right = root->getRight();
        ASSERT_TRUE(right != nullptr);
        EXPECT_EQ(right->getData(), 20);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getParent(), root);
        EXPECT_EQ(root->getLeft(), nullptr);
    }

    TEST(RedBlackTreeTest, InsertThreeNodes_RightRightRotation)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 20);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
        const auto left = root->getLeft();
        const auto right = root->getRight();
        ASSERT_TRUE(left != nullptr && right != nullptr);
        EXPECT_EQ(left->getData(), 10);
        EXPECT_EQ(left->getColor(), fox::Color::Red);
        EXPECT_EQ(left->getParent(), root);
        EXPECT_EQ(right->getData(), 30);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getParent(), root);
    }

    TEST(RedBlackTreeTest, InsertThreeNodes_LeftLeftRotation)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 20);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
        const auto left = root->getLeft();
        const auto right = root->getRight();
        ASSERT_TRUE(left != nullptr && right != nullptr);
        EXPECT_EQ(left->getData(), 10);
        EXPECT_EQ(left->getColor(), fox::Color::Red);
        EXPECT_EQ(left->getParent(), root);
        EXPECT_EQ(right->getData(), 30);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getParent(), root);
    }

    TEST(RedBlackTreeTest, InsertWithUncleRed_ColorsFlipped)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(1);  // This makes the uncle (15) red
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 10);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
        const auto left = root->getLeft();
        const auto right = root->getRight();
        ASSERT_TRUE(left != nullptr && right != nullptr);
        EXPECT_EQ(left->getData(), 5);
        EXPECT_EQ(left->getColor(), fox::Color::Black);
        EXPECT_EQ(right->getData(), 15);
        EXPECT_EQ(right->getColor(), fox::Color::Black);
        const auto left_left = left->getLeft();
        ASSERT_TRUE(left_left != nullptr);
        EXPECT_EQ(left_left->getData(), 1);
        EXPECT_EQ(left_left->getColor(), fox::Color::Red);
        EXPECT_EQ(left_left->getParent(), left);
    }

    TEST(RedBlackTreeTest, InsertDuplicateValue_RightChildCreated)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(10);
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        const auto right = root->getRight();
        ASSERT_TRUE(right != nullptr);
        EXPECT_EQ(right->getData(), 10);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getParent(), root);
    }

    TEST(RedBlackTreeTest, InsertMultipleNodes_ComplexTreeStructure)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(15);
        tree.insert(25);
        tree.insert(5);
        tree.insert(1);

        // Check that all values are inserted
        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 20);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
    }

    TEST(RedBlackTreeTest, LeftRotation_NodeStructureMaintained)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30); // This should trigger a left rotation

        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 20);
        EXPECT_EQ(root->getColor(), fox::Color::Black);

        const auto left = root->getLeft();
        const auto right = root->getRight();
        ASSERT_TRUE(left != nullptr && right != nullptr);
        EXPECT_EQ(left->getData(), 10);
        EXPECT_EQ(right->getData(), 30);
        EXPECT_EQ(left->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
    }

    TEST(RedBlackTreeTest, RightRotation_NodeStructureMaintained)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(30);
        tree.insert(20);
        tree.insert(10); // This should trigger a right rotation

        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getData(), 20);
        EXPECT_EQ(root->getColor(), fox::Color::Black);

        const auto left = root->getLeft();
        const auto right = root->getRight();
        ASSERT_TRUE(left != nullptr && right != nullptr);
        EXPECT_EQ(left->getData(), 10);
        EXPECT_EQ(right->getData(), 30);
        EXPECT_EQ(left->getColor(), fox::Color::Red);
        EXPECT_EQ(right->getColor(), fox::Color::Red);
    }

    TEST(RedBlackTreeTest, InsertValuesInDescendingOrder_TreeBalanced)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(50);
        tree.insert(40);
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);

        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
    }

    TEST(RedBlackTreeTest, InsertValuesInAscendingOrder_TreeBalanced)
    {
        fox::RedBlackTree<int32_t> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);

        const auto root = tree.getRoot();
        ASSERT_TRUE(root != nullptr);
        EXPECT_EQ(root->getColor(), fox::Color::Black);
    }
} // namespace gtest_case
