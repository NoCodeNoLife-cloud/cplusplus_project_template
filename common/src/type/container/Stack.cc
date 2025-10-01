#include "src/type/container/Stack.hpp"

#include <stdexcept>
#include <utility>
#include <iterator>

namespace fox
{
    template <typename T, typename Container>
    Stack<T, Container>::Stack() = default;

    template <typename T, typename Container>
    template <typename Iterator>
    Stack<T, Container>::Stack(Iterator begin, Iterator end) : data_(begin, end)
    {
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::push(const T& value) -> void
    {
        data_.push_back(value);
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::push(T&& value) -> void
    {
        data_.push_back(std::move(value));
    }

    template <typename T, typename Container>
    template <typename... Args>
    auto Stack<T, Container>::emplace(Args&&... args) -> void
    {
        data_.emplace_back(std::forward<Args>(args)...);
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::pop() -> void
    {
        if (data_.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        data_.pop_back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::top() -> T&
    {
        if (data_.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data_.back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::top() const -> const T&
    {
        if (data_.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data_.back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::empty() const noexcept -> bool
    {
        return data_.empty();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::size() const noexcept -> size_t
    {
        return data_.size();
    }
}
