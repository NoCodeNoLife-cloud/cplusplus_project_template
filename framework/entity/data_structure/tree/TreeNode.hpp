#pragma once
#include <memory>

namespace framework::entity::data_structure::tree {

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

}  // namespace framework::entity::data_structure::tree
