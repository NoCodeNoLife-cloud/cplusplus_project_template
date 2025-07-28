#pragma once
#include <functional>
#include <stdexcept>

namespace common {
template <typename T, typename Compare = std::less<T>>
class Heap {
 public:
  Heap();
  template <typename Iterator>
  Heap(Iterator begin, Iterator end);

  auto push(const T& value) -> void;
  auto push(T&& value) -> void;

  template <typename... Args>
  auto emplace(Args&&... args) -> void;

  auto pop() -> void;

  auto top() const -> const T&;
  auto top() -> T&;

  [[nodiscard]] auto size() const -> size_t;
  [[nodiscard]] auto empty() const -> bool;

 private:
  std::vector<T> data_;
  Compare compare;

  auto heapify() -> void;
  auto heapify_up(size_t index) -> void;
  auto heapify_down(size_t index) -> void;
};

template <typename T, typename Compare>
Heap<T, Compare>::Heap() = default;

template <typename T, typename Compare>
template <typename Iterator>
Heap<T, Compare>::Heap(Iterator begin, Iterator end) : data_(begin, end) {
  heapify();
}

template <typename T, typename Compare>
auto Heap<T, Compare>::push(const T& value) -> void {
  data_.push_back(value);
  heapify_up(data_.size() - 1);
}

template <typename T, typename Compare>
auto Heap<T, Compare>::push(T&& value) -> void {
  data_.push_back(std::move(value));
  heapify_up(data_.size() - 1);
}

template <typename T, typename Compare>
template <typename... Args>
auto Heap<T, Compare>::emplace(Args&&... args) -> void {
  data_.emplace_back(std::forward<Args>(args)...);
  heapify_up(data_.size() - 1);
}

template <typename T, typename Compare>
auto Heap<T, Compare>::pop() -> void {
  if (data_.empty()) {
    throw std::out_of_range("Heap is empty");
  }
  std::swap(data_[0], data_.back());
  data_.pop_back();
  heapify_down(0);
}

template <typename T, typename Compare>
auto Heap<T, Compare>::top() const -> const T& {
  if (data_.empty()) {
    throw std::out_of_range("Heap is empty");
  }
  return data_[0];
}

template <typename T, typename Compare>
auto Heap<T, Compare>::top() -> T& {
  if (data_.empty()) {
    throw std::out_of_range("Heap is empty");
  }
  return data_[0];
}

template <typename T, typename Compare>
auto Heap<T, Compare>::size() const -> size_t {
  return data_.size();
}

template <typename T, typename Compare>
auto Heap<T, Compare>::empty() const -> bool {
  return data_.empty();
}

template <typename T, typename Compare>
auto Heap<T, Compare>::heapify() -> void {
  for (int i = data_.size() / 2 - 1; i >= 0; --i) {
    heapify_down(i);
  }
}

template <typename T, typename Compare>
auto Heap<T, Compare>::heapify_up(size_t index) -> void {
  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (!compare(data_[parent], data_[index])) {
      break;
    }
    std::swap(data_[index], data_[parent]);
    index = parent;
  }
}

template <typename T, typename Compare>
auto Heap<T, Compare>::heapify_down(size_t index) -> void {
  size_t size = data_.size();
  while (true) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t swap_index = index;

    if (left < size && compare(data_[index], data_[left])) {
      swap_index = left;
    }

    if (right < size && compare(data_[index], data_[right])) {
      if (compare(data_[right], data_[swap_index])) {
        swap_index = right;
      }
    }

    if (swap_index == index) {
      break;
    }

    std::swap(data_[index], data_[swap_index]);
    index = swap_index;
  }
}
}  // namespace common
