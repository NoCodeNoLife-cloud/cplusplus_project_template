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
        auto pop() -> void;

        /// @brief Accesses the top element of the heap.
        /// @return Const reference to the top element.
        auto top() const -> const T&;

        /// @brief Accesses the top element of the heap.
        /// @return Reference to the top element.
        auto top() -> T&;

        /// @brief Returns the number of elements in the heap.
        /// @return The number of elements.
        [[nodiscard]] auto size() const -> size_t;

        /// @brief Checks if the heap is empty.
        /// @return True if the heap is empty, false otherwise.
        [[nodiscard]] auto empty() const -> bool;

    private:
        std::vector<T> data_;
        Compare compare;

        /// @brief Heapifies the entire heap to maintain the heap property.
        /// @return void
        auto heapify() -> void;

        /// @brief Heapifies up from the given index to maintain the heap property.
        /// @param index The index to start heapifying up from.
        /// @return void
        auto heapify_up(size_t index) -> void;

        /// @brief Heapifies down from the given index to maintain the heap property.
        /// @param index The index to start heapifying down from.
        /// @return void
        auto heapify_down(size_t index) -> void;
    };

    template <typename T, typename Compare>
    Heap<T, Compare>::Heap() = default;

    template <typename T, typename Compare>
    template <typename Iterator>
    Heap<T, Compare>::Heap(Iterator begin, Iterator end) : data_(begin, end)
    {
        heapify();
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::push(const T& value) -> void
    {
        data_.push_back(value);
        heapify_up(data_.size() - 1);
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::push(T&& value) -> void
    {
        data_.push_back(std::move(value));
        heapify_up(data_.size() - 1);
    }

    template <typename T, typename Compare>
    template <typename... Args>
    auto Heap<T, Compare>::emplace(Args&&... args) -> void
    {
        data_.emplace_back(std::forward<Args>(args)...);
        heapify_up(data_.size() - 1);
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::pop() -> void
    {
        if (data_.empty())
        {
            throw std::out_of_range("Heap is empty");
        }
        std::swap(data_[0], data_.back());
        data_.pop_back();
        heapify_down(0);
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::top() const -> const T&
    {
        if (data_.empty())
        {
            throw std::out_of_range("Heap is empty");
        }
        return data_[0];
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::top() -> T&
    {
        if (data_.empty())
        {
            throw std::out_of_range("Heap is empty");
        }
        return data_[0];
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::size() const -> size_t
    {
        return data_.size();
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::empty() const -> bool
    {
        return data_.empty();
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::heapify() -> void
    {
        for (int32_t i = data_.size() / 2 - 1; i >= 0; --i)
        {
            heapify_down(i);
        }
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::heapify_up(size_t index) -> void
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (!compare(data_[parent], data_[index]))
            {
                break;
            }
            std::swap(data_[index], data_[parent]);
            index = parent;
        }
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::heapify_down(size_t index) -> void
    {
        const size_t size = data_.size();
        while (true)
        {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t swap_index = index;

            if (left < size && compare(data_[index], data_[left]))
            {
                swap_index = left;
            }

            if (right < size && compare(data_[index], data_[right]))
            {
                if (compare(data_[right], data_[swap_index]))
                {
                    swap_index = right;
                }
            }

            if (swap_index == index)
            {
                break;
            }

            std::swap(data_[index], data_[swap_index]);
            index = swap_index;
        }
    }
} // namespace fox
