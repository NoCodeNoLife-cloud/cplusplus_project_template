#pragma once
#include <memory>
#include <cstdint>

namespace fox
{
    /// @brief A tree node class that contains a value and pointers to left and right children.
    /// @tparam T The type of the value stored in the node.
    template <typename T>
    class TreeNode
    {
    public:
        explicit TreeNode(T value) noexcept;

        T data;
        std::shared_ptr<TreeNode<T>> left{};
        std::shared_ptr<TreeNode<T>> right{};
        int32_t height{1};
    };

    template <typename T>
    TreeNode<T>::TreeNode(T value) noexcept : data(value)
    {
    }
} // namespace fox
