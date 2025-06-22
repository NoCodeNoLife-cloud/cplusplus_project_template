#pragma once
#include <stdexcept>
#include <vector>

namespace common
{
    template <typename T, typename Container = std::vector<T>>
    class Stack
    {
    public:
        Stack();

        template <typename Iterator>
        Stack(Iterator begin, Iterator end);

        auto push(const T& value) -> void;
        auto push(T&& value) -> void;

        template <typename... Args>
        auto emplace(Args&&... args) -> void;

        auto pop() -> void;

        auto top() const -> const T&;
        auto top() -> T&;

        [[nodiscard]] auto empty() const -> bool;
        [[nodiscard]] auto size() const -> size_t;

    private:
        Container data;
    };

    template <typename T, typename Container>
    Stack<T, Container>::Stack() = default;

    template <typename T, typename Container>
    template <typename Iterator>
    Stack<T, Container>::Stack(Iterator begin, Iterator end)
    {
        for (auto it = begin; it != end; ++it)
        {
            push(*it);
        }
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::push(const T& value) -> void
    {
        data.push_back(value);
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::push(T&& value) -> void
    {
        data.push_back(std::move(value));
    }

    template <typename T, typename Container>
    template <typename... Args>
    auto Stack<T, Container>::emplace(Args&&... args) -> void
    {
        data.emplace_back(std::forward<Args>(args)...);
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::pop() -> void
    {
        if (data.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::top() const -> const T&
    {
        if (data.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::top() -> T&
    {
        if (data.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::empty() const -> bool
    {
        return data.empty();
    }

    template <typename T, typename Container>
    auto Stack<T, Container>::size() const -> size_t
    {
        return data.size();
    }
}
