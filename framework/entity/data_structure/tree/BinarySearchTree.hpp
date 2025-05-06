#pragma once
#include <iostream>
#include <memory>
#include <entity/data_structure/tree/TreeNode.hpp>

namespace framework {
  template <typename T>
  class BinarySearchTree {
  public:
    BinarySearchTree() : root(nullptr) {}

    auto insert(T value) -> void;
    auto find(T value) const -> bool;
    auto remove(T value) -> void;
    auto inorderTraversal() const -> void;

  private:
    std::shared_ptr<TreeNode<T>> root;
    auto insertRecursive(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>>;
    auto findRecursive(const std::shared_ptr<TreeNode<T>>& node, T value) const -> bool;
    auto removeRecursive(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>>;
    auto minValueNode(std::shared_ptr<TreeNode<T>> node) -> std::shared_ptr<TreeNode<T>>;
    auto inorderTraversalRecursive(const std::shared_ptr<TreeNode<T>>& node) const -> void;
  };

  template <typename T>
  auto BinarySearchTree<T>::insert(T value) -> void {
    root = insertRecursive(root, value);
  }

  template <typename T>
  auto BinarySearchTree<T>::insertRecursive(std::shared_ptr<TreeNode<T>> node, T value)
    -> std::shared_ptr<TreeNode<T>> {
    if (!node)
      return std::make_shared<TreeNode<T>>(value);
    if (value < node->data)
      node->left = insertRecursive(node->left, value);
    else if (value > node->data)
      node->right = insertRecursive(node->right, value);
    return node;
  }

  template <typename T>
  auto BinarySearchTree<T>::find(T value) const -> bool {
    return findRecursive(root, value);
  }

  template <typename T>
  auto BinarySearchTree<T>::findRecursive(const std::shared_ptr<TreeNode<T>>& node, T value) const -> bool {
    if (!node)
      return false;
    if (value == node->data)
      return true;
    if (value < node->data)
      return findRecursive(node->left, value);
    return findRecursive(node->right, value);
  }

  template <typename T>
  auto BinarySearchTree<T>::remove(T value) -> void {
    root = removeRecursive(root, value);
  }

  template <typename T>
  auto BinarySearchTree<T>::removeRecursive(std::shared_ptr<TreeNode<T>> node, T value)
    -> std::shared_ptr<TreeNode<T>> {
    if (!node)
      return nullptr;
    if (value < node->data)
      node->left = removeRecursive(node->left, value);
    else if (value > node->data)
      node->right = removeRecursive(node->right, value);
    else {
      if (!node->left)
        return node->right;
      if (!node->right)
        return node->left;
      node->data = minValueNode(node->right)->data;
      node->right = removeRecursive(node->right, node->data);
    }
    return node;
  }

  template <typename T>
  auto BinarySearchTree<T>::minValueNode(std::shared_ptr<TreeNode<T>> node) -> std::shared_ptr<TreeNode<T>> {
    auto current = node;
    while (current && current->left)
      current = current->left;
    return current;
  }

  template <typename T>
  auto BinarySearchTree<T>::inorderTraversal() const -> void {
    inorderTraversalRecursive(root);
    std::cout << std::endl;
  }

  template <typename T>
  auto BinarySearchTree<T>::inorderTraversalRecursive(const std::shared_ptr<TreeNode<T>>& node) const -> void {
    if (!node)
      return;
    inorderTraversalRecursive(node->left);
    std::cout << node->data << " ";
    inorderTraversalRecursive(node->right);
  }
}
