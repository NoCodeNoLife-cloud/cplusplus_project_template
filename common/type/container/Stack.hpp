#pragma once
#include <stdexcept>
#include <vector>

namespace common {
template <typename T, typename Container = std::vector<T>>
class Stack {
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
  /// @return A const reference to the top element.
  /// @throws std::out_of_range If the stack is empty.
  auto top() const -> const T&;

  /// @brief Accesses the top element of the stack.
  /// @return A reference to the top element.
  /// @throws std::out_of_range If the stack is empty.
  auto top() -> T&;

  /// @brief Checks whether the stack is empty.
  /// @return True if the stack is empty, false otherwise.
  [[nodiscard]] auto empty() const -> bool;

  /// @brief Returns the number of elements in the stack.
  /// @return The number of elements in the stack.
  [[nodiscard]] auto size() const -> size_t;

 private:
  Container data;
};

template <typename T, typename Container>
Stack<T, Container>::Stack() = default;

template <typename T, typename Container>
template <typename Iterator>
Stack<T, Container>::Stack(Iterator begin, Iterator end) {
  for (auto it = begin; it != end; ++it) {
    push(*it);
  }
}

template <typename T, typename Container>
auto Stack<T, Container>::push(const T& value) -> void {
  data.push_back(value);
}

template <typename T, typename Container>
auto Stack<T, Container>::push(T&& value) -> void {
  data.push_back(std::move(value));
}

template <typename T, typename Container>
template <typename... Args>
auto Stack<T, Container>::emplace(Args&&... args) -> void {
  data.emplace_back(std::forward<Args>(args)...);
}

template <typename T, typename Container>
auto Stack<T, Container>::pop() -> void {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  data.pop_back();
}

template <typename T, typename Container>
auto Stack<T, Container>::top() const -> const T& {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data.back();
}

template <typename T, typename Container>
auto Stack<T, Container>::top() -> T& {
  if (data.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return data.back();
}

template <typename T, typename Container>
auto Stack<T, Container>::empty() const -> bool {
  return data.empty();
}

template <typename T, typename Container>
auto Stack<T, Container>::size() const -> size_t {
  return data.size();
}
}  // namespace common
