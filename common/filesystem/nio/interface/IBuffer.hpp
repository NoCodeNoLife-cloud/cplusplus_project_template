#pragma once
#include <stdexcept>

namespace fox {
/// @brief Interface for a buffer that manages a sequence of elements
/// This interface provides methods for managing a buffer's position, limit, and capacity.
/// The buffer follows the standard buffer semantics where:
/// - Capacity is the maximum number of elements the buffer can hold
/// - Limit is the index of the first element that should not be read/written
/// - Position is the index of the next element to be read/written
class IBuffer {
 public:
  virtual ~IBuffer() = default;

  /// @brief Get the capacity of the buffer
  /// @return The capacity of the buffer
  [[nodiscard]] virtual auto capacity() const -> size_t { return capacity_; }

  /// @brief Get the current position of the buffer
  /// @return The current position of the buffer
  [[nodiscard]] virtual auto position() const -> size_t { return position_; }

  /// @brief Set the position of the buffer
  /// @param newPosition The new position to set
  virtual auto position(size_t newPosition) -> void {
    if (newPosition > limit_) {
      throw std::out_of_range("Position exceeds the current limit.");
    }
    position_ = newPosition;
  }

  /// @brief Get the limit of the buffer
  /// @return The limit of the buffer
  [[nodiscard]] virtual auto limit() const -> size_t { return limit_; }

  /// @brief Set the limit of the buffer
  /// @param newLimit The new limit to set
  virtual auto limit(size_t newLimit) -> void {
    if (newLimit > capacity_) {
      throw std::out_of_range("Limit exceeds capacity.");
    }
    limit_ = newLimit;
    if (position_ > limit_) {
      position_ = limit_;
    }
  }

  /// @brief Clear the buffer by resetting position and limit
  virtual void clear() {
    position_ = 0;
    limit_ = capacity_;
  }

  /// @brief Flip the buffer by setting limit to current position and resetting position to zero
  virtual void flip() {
    limit_ = position_;
    position_ = 0;
  }

  /// @brief Get the number of remaining elements in the buffer
  /// @return The number of remaining elements
  [[nodiscard]] virtual auto remaining() const -> size_t { return limit_ - position_; }

  /// @brief Check if there are remaining elements in the buffer
  /// @return True if there are remaining elements, false otherwise
  [[nodiscard]] virtual auto hasRemaining() const -> bool { return position_ < limit_; }

  /// @brief Rewind the buffer by resetting position to zero
  virtual void rewind() { position_ = 0; }

 protected:
  size_t position_{0};
  size_t limit_{0};
  size_t capacity_{0};
};
}  // namespace fox