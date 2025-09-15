#pragma once
#include <memory>

#include "type/data_structure/Color.hpp"

namespace fox
{
    /// \brief A node in a Red-Black Tree
    ///
    /// \tparam T The type of data stored in the node
    template <typename T>
    class RedBlackTreeNode
    {
    public:
        explicit RedBlackTreeNode(const T& value);

        /// @brief Get the data stored in the node
        /// @return The data stored in the node
        auto getData() const -> T;

        /// @brief Set the data stored in the node
        /// @param value The new value to store in the node
        auto setData(const T& value) -> void;

        /// @brief Get the left child node
        /// @return A shared pointer to the left child node
        auto getLeft() const -> std::shared_ptr<RedBlackTreeNode>;

        /// @brief Set the left child node
        /// @param node A shared pointer to the new left child node
        auto setLeft(std::shared_ptr<RedBlackTreeNode> node) -> void;

        /// @brief Get the right child node
        /// @return A shared pointer to the right child node
        auto getRight() const -> std::shared_ptr<RedBlackTreeNode>;

        /// @brief Set the right child node
        /// @param node A shared pointer to the new right child node
        auto setRight(std::shared_ptr<RedBlackTreeNode> node) -> void;

        /// @brief Get the parent node
        /// @return A shared pointer to the parent node
        auto getParent() const -> std::shared_ptr<RedBlackTreeNode>;

        /// @brief Set the parent node
        /// @param node A shared pointer to the new parent node
        auto setParent(std::shared_ptr<RedBlackTreeNode> node) -> void;

        /// @brief Get the color of the node
        /// @return The color of the node
        [[nodiscard]] auto getColor() const -> Color;

        /// @brief Set the color of the node
        /// @param c The new color for the node
        auto setColor(Color c) -> void;

    private:
        T data_;
        std::shared_ptr<RedBlackTreeNode> left_;
        std::shared_ptr<RedBlackTreeNode> right_;
        std::shared_ptr<RedBlackTreeNode> parent_;
        Color color_;
    };

    template <typename T>
    RedBlackTreeNode<T>::RedBlackTreeNode(const T& value) : data_(value), color_(Color::Red)
    {
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getData() const -> T
    {
        return data_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setData(const T& value) -> void
    {
        data_ = value;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getLeft() const -> std::shared_ptr<RedBlackTreeNode>
    {
        return left_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setLeft(std::shared_ptr<RedBlackTreeNode> node) -> void
    {
        left_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getRight() const -> std::shared_ptr<RedBlackTreeNode>
    {
        return right_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setRight(std::shared_ptr<RedBlackTreeNode> node) -> void
    {
        right_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getParent() const -> std::shared_ptr<RedBlackTreeNode>
    {
        return parent_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setParent(std::shared_ptr<RedBlackTreeNode> node) -> void
    {
        parent_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getColor() const -> Color
    {
        return color_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setColor(const Color c) -> void
    {
        color_ = c;
    }
} // namespace fox
