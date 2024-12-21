#pragma once
#include <memory>

#include "RedBlackTreeNode.hpp"

namespace framework::entity::data_structure::tree {

template <typename T>
class RedBlackTree {
 public:
  auto insert(const T& value) -> void;

  std::shared_ptr<RedBlackTreeNode<T>> root;

 private:
  auto leftRotate(std::shared_ptr<RedBlackTreeNode<T>> node) -> void;

  auto rightRotate(std::shared_ptr<RedBlackTreeNode<T>> node) -> void;

  auto fixInsert(std::shared_ptr<RedBlackTreeNode<T>> node) -> void;
};

template <typename T>
auto RedBlackTree<T>::insert(const T& value) -> void {
  auto node = std::make_shared<RedBlackTreeNode<T>>(value);
  if (!root) {
    root = node;
    node->setColor(graphics::models::Color::Black);
    return;
  }
  std::shared_ptr<RedBlackTreeNode<T>> current = root;
  std::shared_ptr<RedBlackTreeNode<T>> parent;
  while (current) {
    parent = current;
    if (value < current->getData()) {
      current = current->getLeft();
    } else {
      current = current->getRight();
    }
  }
  node->setParent(parent);
  if (value < parent->getData()) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
  fixInsert(node);
}

template <typename T>
auto RedBlackTree<T>::leftRotate(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
  auto rightChild = node->getRight();
  node->setRight(rightChild->getLeft());
  if (rightChild->getLeft()) {
    rightChild->getLeft()->setParent(node);
  }
  rightChild->setParent(node->getParent());
  if (!node->getParent()) {
    root = rightChild;
  } else if (node == node->getParent()->getLeft()) {
    node->getParent()->setLeft(rightChild);
  } else {
    node->getParent()->setRight(rightChild);
  }
  rightChild->setLeft(node);
  node->setParent(rightChild);
}

template <typename T>
auto RedBlackTree<T>::rightRotate(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
  auto leftChild = node->getLeft();
  node->setLeft(leftChild->getRight());
  if (leftChild->getRight()) {
    leftChild->getRight()->setParent(node);
  }
  leftChild->setParent(node->getParent());
  if (!node->getParent()) {
    root = leftChild;
  } else if (node == node->getParent()->getLeft()) {
    node->getParent()->setLeft(leftChild);
  } else {
    node->getParent()->setRight(leftChild);
  }
  leftChild->setRight(node);
  node->setParent(leftChild);
}

template <typename T>
auto RedBlackTree<T>::fixInsert(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
  while (node != root && node->getParent() && node->getParent()->getColor() == graphics::models::Color::Red) {
    if (node->getParent() == node->getParent()->getParent()->getLeft()) {
      auto uncle = node->getParent()->getParent()->getRight();
      if (uncle && uncle->getColor() == graphics::models::Color::Red) {
        node->getParent()->setColor(graphics::models::Color::Black);
        uncle->setColor(graphics::models::Color::Black);
        node->getParent()->getParent()->setColor(graphics::models::Color::Red);
        node = node->getParent()->getParent();
      } else {
        if (node == node->getParent()->getRight()) {
          node = node->getParent();
          leftRotate(node);
        }
        node->getParent()->setColor(graphics::models::Color::Black);
        if (node->getParent()->getParent()) {
          node->getParent()->getParent()->setColor(graphics::models::Color::Red);
        }
        rightRotate(node->getParent()->getParent());
      }
    } else {
      auto uncle = node->getParent()->getParent()->getLeft();
      if (uncle && uncle->getColor() == graphics::models::Color::Red) {
        node->getParent()->setColor(graphics::models::Color::Black);
        uncle->setColor(graphics::models::Color::Black);
        node->getParent()->getParent()->setColor(graphics::models::Color::Red);
        node = node->getParent()->getParent();
      } else {
        if (node == node->getParent()->getLeft()) {
          node = node->getParent();
          rightRotate(node);
        }
        node->getParent()->setColor(graphics::models::Color::Black);
        if (node->getParent()->getParent()) {
          node->getParent()->getParent()->setColor(graphics::models::Color::Red);
        }
        leftRotate(node->getParent()->getParent());
      }
    }
  }
  root->setColor(graphics::models::Color::Black);
}

}  // namespace framework::entity::data_structure::tree
