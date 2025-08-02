#pragma once
#include <algorithm>
#include <memory>

#include "TreeNode.hpp"

namespace common {
template <typename T>
class AVLTree {
 public:
  AVLTree();
  auto insert(T value) -> void;
  auto remove(T value) -> void;
  auto find(T value) const -> bool;

 private:
  std::shared_ptr<TreeNode<T>> root_;
  auto getHeight(const std::shared_ptr<TreeNode<T>>& node) -> int32_t;
  auto getBalance(const std::shared_ptr<TreeNode<T>>& node) -> int32_t;
  auto rotateRight(std::shared_ptr<TreeNode<T>> y) -> std::shared_ptr<TreeNode<T>>;
  auto rotateLeft(std::shared_ptr<TreeNode<T>> x) -> std::shared_ptr<TreeNode<T>>;
  auto insert(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>>;
  auto remove(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>>;
  auto findMin(const std::shared_ptr<TreeNode<T>>& node) const -> std::shared_ptr<TreeNode<T>>;
  auto find(const std::shared_ptr<TreeNode<T>>& node, T value) const -> std::shared_ptr<TreeNode<T>>;
};

template <typename T>
AVLTree<T>::AVLTree() : root_(nullptr) {}

template <typename T>
auto AVLTree<T>::insert(T value) -> void {
  root_ = insert(root_, value);
}

template <typename T>
auto AVLTree<T>::remove(T value) -> void {
  root_ = remove(root_, value);
}

template <typename T>
auto AVLTree<T>::find(T value) const -> bool {
  return find(root_, value) != nullptr;
}

template <typename T>
auto AVLTree<T>::getHeight(const std::shared_ptr<TreeNode<T>>& node) -> int32_t {
  return node ? node->height : 0;
}

template <typename T>
auto AVLTree<T>::getBalance(const std::shared_ptr<TreeNode<T>>& node) -> int32_t {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename T>
auto AVLTree<T>::rotateRight(std::shared_ptr<TreeNode<T>> y) -> std::shared_ptr<TreeNode<T>> {
  auto x = y->left;
  auto T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
  return x;
}

template <typename T>
auto AVLTree<T>::rotateLeft(std::shared_ptr<TreeNode<T>> x) -> std::shared_ptr<TreeNode<T>> {
  auto y = x->right;
  auto T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
  return y;
}

template <typename T>
auto AVLTree<T>::insert(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>> {
  if (!node) return std::make_shared<TreeNode<T>>(value);
  if (value < node->data)
    node->left = insert(node->left, value);
  else if (value > node->data)
    node->right = insert(node->right, value);
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  const int32_t balance = getBalance(node);
  if (balance > 1 && value < node->left->data) return rotateRight(node);
  if (balance < -1 && value > node->right->data) return rotateLeft(node);
  if (balance > 1 && value > node->left->data) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && value < node->right->data) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

template <typename T>
auto AVLTree<T>::remove(std::shared_ptr<TreeNode<T>> node, T value) -> std::shared_ptr<TreeNode<T>> {
  if (!node) return node;
  if (value < node->data)
    node->left = remove(node->left, value);
  else if (value > node->data)
    node->right = remove(node->right, value);
  else {
    if (!node->left && !node->right)
      node = nullptr;
    else if (!node->left)
      node = node->right;
    else if (!node->right)
      node = node->left;
    else {
      auto successor = findMin(node->right);
      node->data = successor->data;
      node->right = remove(node->right, successor->data);
    }
  }
  if (!node) return node;
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  const int32_t balance = getBalance(node);
  if (balance > 1) {
    if (getBalance(node->left) >= 0) return rotateRight(node);
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1) {
    if (getBalance(node->right) <= 0) return rotateLeft(node);
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

template <typename T>
auto AVLTree<T>::findMin(const std::shared_ptr<TreeNode<T>>& node) const -> std::shared_ptr<TreeNode<T>> {
  auto current = node;
  while (current->left) current = current->left;
  return current;
}

template <typename T>
auto AVLTree<T>::find(const std::shared_ptr<TreeNode<T>>& node, T value) const -> std::shared_ptr<TreeNode<T>> {
  if (!node) return nullptr;
  if (value == node->data) return node;
  return value < node->data ? find(node->left, value) : find(node->right, value);
}
}  // namespace common
