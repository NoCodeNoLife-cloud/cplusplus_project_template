#pragma once
#include <memory>
#include <entity/data_structure/Color.hpp>

namespace framework::entity::data_structure::tree {
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
    T data;
    std::shared_ptr<RedBlackTreeNode> left;
    std::shared_ptr<RedBlackTreeNode> right;
    std::shared_ptr<RedBlackTreeNode> parent;
    Color color;
  };

  template <typename T>
  RedBlackTreeNode<T>::RedBlackTreeNode(const T& value) : data(value), color(Color::Red) {}

  template <typename T>
  auto RedBlackTreeNode<T>::getData() const -> T {
    return data;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::setData(const T& value) -> void {
    data = value;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::getLeft() const -> std::shared_ptr<RedBlackTreeNode> {
    return left;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::setLeft(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
    left = node;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::getRight() const -> std::shared_ptr<RedBlackTreeNode> {
    return right;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::setRight(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
    right = node;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::getParent() const -> std::shared_ptr<RedBlackTreeNode> {
    return parent;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::setParent(std::shared_ptr<RedBlackTreeNode<T>> node) -> void {
    parent = node;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::getColor() const -> Color {
    return color;
  }

  template <typename T>
  auto RedBlackTreeNode<T>::setColor(const Color c) -> void {
    color = c;
  }
}
