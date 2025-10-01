#pragma once
#include <functional>
#include <stdexcept>
#include <vector>

namespace fox
{
    /// @brief A heap data structure implementation.
    /// @tparam T The type of elements stored in the heap.
    /// @tparam Compare The comparison function object type that defines the heap order.
    template <typename T, typename Compare = std::less<T>>
    class Heap
    {
    public:
        Heap();

        template <typename Iterator>
        Heap(Iterator begin, Iterator end);

        /// @brief Pushes a value to the heap.
        /// @param value The value to push.
        auto push(const T& value) -> void;

        /// @brief Pushes a value to the heap.
        /// @param value The value to push.
        auto push(T&& value) -> void;

        /// @brief Constructs an element in-place and pushes it to the heap.
        /// @param args Arguments to forward to the constructor of the element.
        template <typename... Args>
        auto emplace(Args&&... args) -> void;

        /// @brief Removes the top element from the heap.
        /// @throws std::out_of_range If the heap is empty.
        auto pop() -> void;

        /// @brief Accesses the top element of the heap.
        /// @return Const reference to the top element.
        /// @throws std::out_of_range If the heap is empty.
        auto top() const -> const T&;

        /// @brief Accesses the top element of the heap.
        /// @return Reference to the top element.
        /// @throws std::out_of_range If the heap is empty.
        auto top() -> T&;

        /// @brief Returns the number of elements in the heap.
        /// @return The number of elements.
        [[nodiscard]] auto size() const noexcept -> size_t;

        /// @brief Checks if the heap is empty.
        /// @return True if the heap is empty, false otherwise.
        [[nodiscard]] auto empty() const noexcept -> bool;

    private:
        std::vector<T> data_{};
        Compare compare_{};

        /// @brief Heapifies the entire heap to maintain the heap property.
        auto heapify() -> void;

        /// @brief Heapifies up from the given index to maintain the heap property.
        /// @param index The index to start heapifying up from.
        auto heapify_up(size_t index) -> void;

        /// @brief Heapifies down from the given index to maintain the heap property.
        /// @param index The index to start heapifying down from.
        auto heapify_down(size_t index) -> void;
    };
}
