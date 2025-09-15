#pragma once
#include <stdexcept>

namespace fox
{
    /// @brief Interface for a buffer that manages a sequence of elements
    /// This interface provides methods for managing a buffer's position, limit, and capacity.
    /// The buffer follows the standard buffer semantics where:
    /// - Capacity is the maximum number of elements the buffer can hold
    /// - Limit is the index of the first element that should not be read/written
    /// - Position is the index of the next element to be read/written
    class IBuffer
    {
    public:
        virtual ~IBuffer();

        /// @brief Get the capacity of the buffer
        /// @return The capacity of the buffer
        [[nodiscard]] virtual auto capacity() const -> size_t;

        /// @brief Get the current position of the buffer
        /// @return The current position of the buffer
        [[nodiscard]] virtual auto position() const -> size_t;

        /// @brief Set the position of the buffer
        /// @param newPosition The new position to set
        virtual auto position(const size_t newPosition) -> void;

        /// @brief Get the limit of the buffer
        /// @return The limit of the buffer
        [[nodiscard]] virtual auto limit() const -> size_t;

        /// @brief Set the limit of the buffer
        /// @param newLimit The new limit to set
        virtual auto limit(const size_t newLimit) -> void;

        /// @brief Clear the buffer by resetting position and limit
        virtual void clear();

        /// @brief Flip the buffer by setting limit to current position and resetting position to zero
        virtual void flip();

        /// @brief Get the number of remaining elements in the buffer
        /// @return The number of remaining elements
        [[nodiscard]] virtual auto remaining() const -> size_t;

        /// @brief Check if there are remaining elements in the buffer
        /// @return True if there are remaining elements, false otherwise
        [[nodiscard]] virtual auto hasRemaining() const -> bool;

        /// @brief Rewind the buffer by resetting position to zero
        virtual void rewind();

    protected:
        size_t position_{0};
        size_t limit_{0};
        size_t capacity_{0};
    };

    inline IBuffer::~IBuffer() = default;

    inline auto IBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto IBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto IBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds the current limit.");
        }
        position_ = newPosition;
    }

    inline auto IBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto IBuffer::limit(const size_t newLimit) -> void
    {
        if (newLimit > capacity_)
        {
            throw std::out_of_range("Limit exceeds capacity.");
        }
        limit_ = newLimit;
        if (position_ > limit_)
        {
            position_ = limit_;
        }
    }

    inline void IBuffer::clear()
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline void IBuffer::flip()
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto IBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    inline auto IBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline void IBuffer::rewind()
    {
        position_ = 0;
    }
} // namespace fox
