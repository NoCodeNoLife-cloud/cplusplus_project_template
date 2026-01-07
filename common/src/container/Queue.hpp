#pragma once
#include <memory>

namespace common
{
    /// @brief A queue data structure implementation using linked nodes with smart pointers
    /// @tparam T The type of elements stored in the queue
    template <typename T>
    class Queue
    {
    public:
        Queue();

        Queue(const Queue& other);

        Queue(Queue&& other) noexcept;

        /// @brief Copy assignment operator
        /// @param other The queue to copy from
        /// @return Reference to this queue
        auto operator=(const Queue& other) -> Queue&;

        /// @brief Move assignment operator
        /// @param other The queue to move from
        /// @return Reference to this queue
        auto operator=(Queue&& other) noexcept -> Queue&;

        /// @brief Add an element to the back of the queue
        /// @param value The value to add
        auto push(const T& value) -> void;

        /// @brief Remove the element from the front of the queue
        /// @throws std::out_of_range If the queue is empty
        auto pop() -> void;

        /// @brief Get a reference to the front element
        /// @return Reference to the front element
        /// @throws std::out_of_range If the queue is empty
        auto front() -> T&;

        /// @brief Get a const reference to the front element
        /// @return Const reference to the front element
        /// @throws std::out_of_range If the queue is empty
        auto front() const -> const T&;

        /// @brief Get a reference to the back element
        /// @return Reference to the back element
        /// @throws std::out_of_range If the queue is empty
        auto back() -> T&;

        /// @brief Get a const reference to the back element
        /// @return Const reference to the back element
        /// @throws std::out_of_range If the queue is empty
        auto back() const -> const T&;

        /// @brief Check if the queue is empty
        /// @return True if the queue is empty, false otherwise
        [[nodiscard]] auto empty() const noexcept -> bool;

        /// @brief Get the number of elements in the queue
        /// @return The number of elements in the queue
        [[nodiscard]] auto size() const noexcept -> size_t;

        /// @brief Swap the contents of this queue with another
        /// @param other The queue to swap with
        auto swap(Queue& other) noexcept -> void;

    private:
        struct Node
        {
            T data_{};
            std::unique_ptr<Node> next_{};

            explicit Node(T value);
        };

        std::unique_ptr<Node> head_{};
        Node* tail_{nullptr};
        size_t queue_size_{0};
    };
}
