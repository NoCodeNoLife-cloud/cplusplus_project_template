#pragma once
#include <memory>

namespace fox {
/// @brief A tree node class that contains a value and pointers to left and right children.
/// @tparam T The type of the value stored in the node.
template <typename T>
class TreeNode {
 public:
  explicit TreeNode(T value);
  T data;
  std::shared_ptr<TreeNode> left{};
  std::shared_ptr<TreeNode> right{};
  int32_t height{1};
};

template <typename T>
TreeNode<T>::TreeNode(T value) : data(value) {}
}  // namespace fox
