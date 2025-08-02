#pragma once
#include <memory>
#include <stdexcept>

namespace common {
template <typename T>
class Queue {
 public:
  Queue();
  Queue(const Queue& other);
  Queue(Queue&& other) noexcept;

  auto operator=(const Queue& other) -> Queue&;
  auto operator=(Queue&& other) noexcept -> Queue&;

  auto swap(Queue& other) noexcept -> void;

  auto push(const T& value) -> void;
  auto pop() -> void;

  auto front() -> T&;
  auto front() const -> const T&;

  auto back() -> T&;
  auto back() const -> const T&;

  [[nodiscard]] auto empty() const -> bool;
  [[nodiscard]] auto size() const -> size_t;

 private:
  struct Node {
    T data_;
    std::unique_ptr<Node> next_;

    explicit Node(T value);
  };

  std::unique_ptr<Node> head_;
  Node* tail_{nullptr};
  size_t queue_size_{0};
};

template <typename T>
Queue<T>::Queue() = default;

template <typename T>
Queue<T>::Queue(const Queue& other) : head_(nullptr), tail_(nullptr) {
  if (!other.empty()) {
    head_ = std::make_unique<Node>(other.head_->data_);
    Node* current_new = head_.get();
    Node* current_other = other.head_.get();
    while (current_other->next_) {
      current_new->next_ = std::make_unique<Node>(current_other->next_->data_);
      current_new = current_new->next_.get();
      current_other = current_other->next_.get();
    }
    tail_ = current_new;
    queue_size_ = other.queue_size_;
  }
}

template <typename T>
Queue<T>::Queue(Queue&& other) noexcept : head_(std::move(other.head_)), tail_(other.tail_), queue_size_(other.queue_size_) {
  other.tail_ = nullptr;
  other.queue_size_ = 0;
}

template <typename T>
auto Queue<T>::operator=(const Queue& other) -> Queue& {
  if (this != &other) {
    Queue copy(other);
    swap(copy);
  }
  return *this;
}

template <typename T>
auto Queue<T>::operator=(Queue&& other) noexcept -> Queue& {
  if (this != &other) {
    head_ = std::move(other.head_);
    tail_ = other.tail_;
    queue_size_ = other.queue_size_;
    other.tail_ = nullptr;
    other.queue_size_ = 0;
  }
  return *this;
}

template <typename T>
auto Queue<T>::swap(Queue& other) noexcept -> void {
  using std::swap;
  head_.swap(other.head_);
  swap(tail_, other.tail_);
  swap(queue_size_, other.queue_size_);
}

template <typename T>
auto Queue<T>::push(const T& value) -> void {
  auto new_node = std::make_unique<Node>(value);
  if (tail_) {
    tail_->next_ = std::move(new_node);
    tail_ = tail_->next_.get();
  } else {
    head_ = std::move(new_node);
    tail_ = head_.get();
  }
  ++queue_size_;
}

template <typename T>
auto Queue<T>::pop() -> void {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  head_ = std::move(head_->next_);
  if (!head_) {
    tail_ = nullptr;
  }
  --queue_size_;
}

template <typename T>
auto Queue<T>::front() -> T& {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->data_;
}

template <typename T>
auto Queue<T>::back() -> T& {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return tail_->data_;
}

template <typename T>
auto Queue<T>::front() const -> const T& {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->data_;
}

template <typename T>
auto Queue<T>::back() const -> const T& {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return tail_->data_;
}

template <typename T>
auto Queue<T>::empty() const -> bool {
  return queue_size_ == 0;
}

template <typename T>
auto Queue<T>::size() const -> size_t {
  return queue_size_;
}

template <typename T>
Queue<T>::Node::Node(T value) : data_(value), next_(nullptr) {}
}  // namespace common
