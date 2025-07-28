#pragma once
#include <memory>

#include "type/data_structure/Color.hpp"

namespace common {
template <typename T>
class RedBlackTreeNode {
 public:
  explicit RedBlackTreeNode(const T& value);
  auto getData() const -> T;
  auto setData(const T& value) -> void;
  auto getLeft() const -> std::shared_ptr<RedBlackTreeNode>;
  auto setLeft(std::shared_ptr<RedBlackTreeNode> node) -> void;
  auto getRight() const -> std::shared_ptr<RedBlackTreeNode>;
  auto setRight(std::shared_ptr<RedBlackTreeNode> node) -> void;
  auto getParent() const -> std::shared_ptr<RedBlackTreeNode>;
  auto setParent(std::shared_ptr<RedBlackTreeNode> node) -> void;
  [[nodiscard]] auto getColor() const -> Color;
  auto setColor(Color c) -> void;

 private:
  T data_;
  std::shared_ptr<RedBlackTreeNode> left_;
  std::shared_ptr<RedBlackTreeNode> right_;
  std::shared_ptr<RedBlackTreeNode> parent_;
  Color color_;
};

template <typename T>
RedBlackTreeNode<T>::RedBlackTreeNode(const T& value)
    : data_(value), color_(Color::Red) {}

template <typename T>
auto RedBlackTreeNode<T>::getData() const -> T {
  return data_;
}

template <typename T>
auto RedBlackTreeNode<T>::setData(const T& value) -> void {
  data_ = value;
}

template <typename T>
auto RedBlackTreeNode<T>::getLeft() const -> std::shared_ptr<RedBlackTreeNode> {
  return left_;
}

template <typename T>
auto RedBlackTreeNode<T>::setLeft(std::shared_ptr<RedBlackTreeNode> node)
    -> void {
  left_ = node;
}

template <typename T>
auto RedBlackTreeNode<T>::getRight() const
    -> std::shared_ptr<RedBlackTreeNode> {
  return right_;
}

template <typename T>
auto RedBlackTreeNode<T>::setRight(std::shared_ptr<RedBlackTreeNode> node)
    -> void {
  right_ = node;
}

template <typename T>
auto RedBlackTreeNode<T>::getParent() const
    -> std::shared_ptr<RedBlackTreeNode> {
  return parent_;
}

template <typename T>
auto RedBlackTreeNode<T>::setParent(std::shared_ptr<RedBlackTreeNode> node)
    -> void {
  parent_ = node;
}

template <typename T>
auto RedBlackTreeNode<T>::getColor() const -> Color {
  return color_;
}

template <typename T>
auto RedBlackTreeNode<T>::setColor(const Color c) -> void {
  color_ = c;
}
}  // namespace common
