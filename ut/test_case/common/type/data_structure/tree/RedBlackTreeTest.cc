#include <gtest/gtest.h>

#include "type/data_structure/tree/RedBlackTree.hpp"

namespace gtest_case {
TEST(RedBlackTreeTest, InsertSingleNode_RootIsBlackAndHasCorrectValue) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  const auto root = tree.root_;
  ASSERT_TRUE(root != nullptr);
  EXPECT_EQ(root->getData(), 10);
  EXPECT_EQ(root->getColor(), fox::Color::Black);
  EXPECT_EQ(root->getParent(), nullptr);
}

TEST(RedBlackTreeTest, InsertTwoNodes_ParentAndChildRelationCorrect) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  tree.insert(20);
  const auto root = tree.root_;
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

TEST(RedBlackTreeTest, InsertThreeNodes_RightRightRotation) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  const auto root = tree.root_;
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

TEST(RedBlackTreeTest, InsertThreeNodes_LeftLeftRotation) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(1);
  const auto root = tree.root_;
  ASSERT_TRUE(root != nullptr);
  EXPECT_EQ(root->getData(), 5);
  EXPECT_EQ(root->getColor(), fox::Color::Black);
  const auto left = root->getLeft();
  const auto right = root->getRight();
  ASSERT_TRUE(left != nullptr && right != nullptr);
  EXPECT_EQ(left->getData(), 1);
  EXPECT_EQ(left->getColor(), fox::Color::Red);
  EXPECT_EQ(left->getParent(), root);
  EXPECT_EQ(right->getData(), 10);
  EXPECT_EQ(right->getColor(), fox::Color::Red);
  EXPECT_EQ(right->getParent(), root);
}

TEST(RedBlackTreeTest, InsertWithUncleRed_ColorsFlipped) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(6);
  const auto root = tree.root_;
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
  const auto left_right = left->getRight();
  ASSERT_TRUE(left_right != nullptr);
  EXPECT_EQ(left_right->getData(), 6);
  EXPECT_EQ(left_right->getColor(), fox::Color::Red);
  EXPECT_EQ(left_right->getParent(), left);
}

TEST(RedBlackTreeTest, InsertDuplicateValue_RightChildCreated) {
  fox::RedBlackTree<int32_t> tree;
  tree.insert(10);
  tree.insert(10);
  const auto root = tree.root_;
  ASSERT_TRUE(root != nullptr);
  const auto right = root->getRight();
  ASSERT_TRUE(right != nullptr);
  EXPECT_EQ(right->getData(), 10);
  EXPECT_EQ(right->getColor(), fox::Color::Red);
  EXPECT_EQ(right->getParent(), root);
}
}  // namespace gtest_case
