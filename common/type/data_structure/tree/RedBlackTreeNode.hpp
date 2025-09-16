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
        explicit RedBlackTreeNode(const T& value) noexcept;

        /// @brief Get the data stored in the node
        /// @return The data stored in the node
        [[nodiscard]] auto getData() const noexcept -> T;

        /// @brief Set the data stored in the node
        /// @param value The new value to store in the node
        auto setData(const T& value) noexcept -> void;

        /// @brief Get the left child node
        /// @return A shared pointer to the left child node
        [[nodiscard]] auto getLeft() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>;

        /// @brief Set the left child node
        /// @param node A shared pointer to the new left child node
        auto setLeft(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void;

        /// @brief Get the right child node
        /// @return A shared pointer to the right child node
        [[nodiscard]] auto getRight() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>;

        /// @brief Set the right child node
        /// @param node A shared pointer to the new right child node
        auto setRight(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void;

        /// @brief Get the parent node
        /// @return A shared pointer to the parent node
        [[nodiscard]] auto getParent() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>;

        /// @brief Set the parent node
        /// @param node A shared pointer to the new parent node
        auto setParent(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void;

        /// @brief Get the color of the node
        /// @return The color of the node
        [[nodiscard]] auto getColor() const noexcept -> Color;

        /// @brief Set the color of the node
        /// @param c The new color for the node
        auto setColor(Color c) noexcept -> void;

    private:
        T data_;
        std::shared_ptr<RedBlackTreeNode<T>> left_;
        std::shared_ptr<RedBlackTreeNode<T>> right_;
        std::shared_ptr<RedBlackTreeNode<T>> parent_;
        Color color_;
    };

    template <typename T>
    RedBlackTreeNode<T>::RedBlackTreeNode(const T& value) noexcept : data_(value), color_(Color::Red)
    {
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getData() const noexcept -> T
    {
        return data_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setData(const T& value) noexcept -> void
    {
        data_ = value;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getLeft() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>
    {
        return left_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setLeft(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void
    {
        left_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getRight() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>
    {
        return right_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setRight(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void
    {
        right_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getParent() const noexcept -> std::shared_ptr<RedBlackTreeNode<T>>
    {
        return parent_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setParent(std::shared_ptr<RedBlackTreeNode<T>> node) noexcept -> void
    {
        parent_ = node;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::getColor() const noexcept -> Color
    {
        return color_;
    }

    template <typename T>
    auto RedBlackTreeNode<T>::setColor(const Color c) noexcept -> void
    {
        color_ = c;
    }
} // namespace fox
