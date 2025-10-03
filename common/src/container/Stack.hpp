#pragma once
#include <vector>
#include <iterator>

namespace common
{
    /// @brief A simple stack implementation using a container.
    /// @tparam T The type of elements stored in the stack.
    /// @tparam Container The underlying container type used to store elements. Defaults to std::vector<T>.
    template <typename T, typename Container = std::vector<T>>
    class Stack
    {
    public:
        Stack();

        template <typename Iterator>
        Stack(Iterator begin, Iterator end);

        /// @brief Pushes a copy of the given value onto the stack.
        /// @param value The value to push.
        auto push(const T& value) -> void;

        /// @brief Pushes the given value onto the stack using move semantics.
        /// @param value The value to push.
        auto push(T&& value) -> void;

        /// @brief Constructs an element in-place on top of the stack.
        /// @tparam Args Types of arguments to forward to the constructor.
        /// @param args Arguments to forward to the constructor.
        template <typename... Args>
        auto emplace(Args&&... args) -> void;

        /// @brief Removes the top element from the stack.
        /// @throws std::out_of_range If the stack is empty.
        auto pop() -> void;

        /// @brief Accesses the top element of the stack.
        /// @return A reference to the top element.
        /// @throws std::out_of_range If the stack is empty.
        auto top() -> T&;

        /// @brief Accesses the top element of the stack.
        /// @return A const reference to the top element.
        /// @throws std::out_of_range If the stack is empty.
        auto top() const -> const T&;

        /// @brief Checks whether the stack is empty.
        /// @return True if the stack is empty, false otherwise.
        [[nodiscard]] auto empty() const noexcept -> bool;

        /// @brief Returns the number of elements in the stack.
        /// @return The number of elements in the stack.
        [[nodiscard]] auto size() const noexcept -> size_t;

    private:
        Container data_{};
    };
}
