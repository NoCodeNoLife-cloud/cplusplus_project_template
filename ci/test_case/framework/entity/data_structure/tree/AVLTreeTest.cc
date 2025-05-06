#include <entity/data_structure/tree/AVLTree.hpp>
#include <gtest/gtest.h>
using framework::AVLTree;

namespace gtest_case {
  TEST(AVLTreeTest, InsertSingleNodeCheckExistence) {
    AVLTree<int> tree;
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
  }

  TEST(AVLTreeTest, InsertDuplicateValueCheckNoGrowth) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
  }

  TEST(AVLTreeTest, InsertLeftLeftCaseCheckRotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertRightRightCaseCheckRotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertLeftRightCaseCheckRotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, InsertRightLeftCaseCheckRotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, RemoveLeafNodeCheckExistence) {
    AVLTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.remove(10);
    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, RemoveNodeWithOneChildCheckStructure) {
    AVLTree<int> tree;
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
    AVLTree<int> tree;
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
    AVLTree<int> tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.remove(20);
    EXPECT_FALSE(tree.find(20));
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(30));
  }

  TEST(AVLTreeTest, FindNonExistentValueCheckFalse) {
    AVLTree<int> tree;
    tree.insert(20);
    EXPECT_FALSE(tree.find(99));
  }

  TEST(AVLTreeTest, InsertRemoveCheckEmptyState) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.remove(10);
    EXPECT_FALSE(tree.find(10));
  }
}
