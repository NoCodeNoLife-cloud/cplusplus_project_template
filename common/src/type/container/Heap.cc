#include "src/type/container/Heap.hpp"

#include <functional>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <utility>

namespace fox
{
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
        if (!data_.empty())
        {
            heapify_down(0);
        }
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
    auto Heap<T, Compare>::size() const noexcept -> size_t
    {
        return data_.size();
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::empty() const noexcept -> bool
    {
        return data_.empty();
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::heapify() -> void
    {
        for (std::int32_t i = static_cast<std::int32_t>(data_.size()) / 2 - 1; i >= 0; --i)
        {
            heapify_down(static_cast<size_t>(i));
        }
    }

    template <typename T, typename Compare>
    auto Heap<T, Compare>::heapify_up(size_t index) -> void
    {
        while (index > 0)
        {
            const size_t parent = (index - 1) / 2;
            if (!compare_(data_[parent], data_[index]))
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
            const size_t left = 2 * index + 1;
            const size_t right = 2 * index + 2;
            size_t swap_index = index;

            if (left < size && compare_(data_[swap_index], data_[left]))
            {
                swap_index = left;
            }

            if (right < size && compare_(data_[swap_index], data_[right]))
            {
                if (compare_(data_[right], data_[swap_index]))
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
}
