#include <entity/data_structure/tree/AVLTree.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(AVLTreeTest, InsertSingleNodeCheckExistence) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
  }

  TEST(AVLTreeTest, InsertDuplicateValueCheckNoGrowth) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(10);
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
  }

  TEST(AVLTreeTest, InsertLeftLeftCaseCheckRotation) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertRightRightCaseCheckRotation) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertLeftRightCaseCheckRotation) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertRightLeftCaseCheckRotation) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, RemoveLeafNodeCheckExistence) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.remove(10);
    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, RemoveNodeWithOneChildCheckStructure) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
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

  TEST(AVLTreeTest, RemoveNodeWithTwoChildrenCheckSuccessor) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
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

  TEST(AVLTreeTest, RemoveRootNodeCheckNewRoot) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.remove(20);
    EXPECT_FALSE(tree.find(20));
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, FindNonExistentValueCheckFalse) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(20);
    EXPECT_FALSE(tree.find(99));
  }

  TEST(AVLTreeTest, InsertRemoveCheckEmptyState) {
    framework::entity::data_structure::tree::AVLTree<int> tree;
    tree.insert(10);
    tree.remove(10);
    EXPECT_FALSE(tree.find(10));
  }
} // namespace gtest_case
