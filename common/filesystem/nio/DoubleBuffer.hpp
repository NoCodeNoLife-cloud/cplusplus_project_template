#pragma once
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A DoubleBuffer class that implements the IBuffer interface for handling double precision floating point
    /// numbers. This class provides functionality to put and get double values from a buffer with a specified capacity.
    class DoubleBuffer final : public IBuffer
    {
    public:
        /// @brief Constructs a DoubleBuffer with the specified capacity.
        /// @param capacity The capacity of the buffer.
        explicit DoubleBuffer(size_t capacity);

        /// @brief Clears the buffer by setting position to 0 and limit to capacity.
        /// @return void
        auto clear() -> void override;

        /// @brief Flips the buffer by setting limit to current position and position to 0.
        /// @return void
        auto flip() -> void override;

        /// @brief Resets the position to 0 while keeping the limit unchanged.
        /// @return void
        auto rewind() -> void override;

        /// @brief Compacts the buffer by removing processed elements.
        /// @return void
        auto compact() -> void;

        /// @brief Puts a single double value into the buffer.
        /// @param value The double value to be put into the buffer.
        /// @return Reference to the current DoubleBuffer object.
        auto put(double value) -> DoubleBuffer&;

        /// @brief Puts a vector of double values into the buffer.
        /// @param values The vector of double values to be put into the buffer.
        /// @return Reference to the current DoubleBuffer object.
        auto put(const std::vector<double>& values) -> DoubleBuffer&;

        /// @brief Gets a single double value from the buffer.
        /// @return The double value retrieved from the buffer.
        auto get() -> double;

        /// @brief Returns the current position in the buffer.
        /// @return The current position.
        [[nodiscard]] auto position() const -> size_t override;

        /// @brief Sets the position in the buffer.
        /// @param newPosition The new position to set.
        /// @return void
        auto position(size_t newPosition) -> void override;

        /// @brief Returns the limit of the buffer.
        /// @return The current limit.
        [[nodiscard]] auto limit() const -> size_t override;

        /// @brief Sets the limit of the buffer.
        /// @param newLimit The new limit to set.
        /// @return void
        auto limit(size_t newLimit) -> void override;

        /// @brief Returns the capacity of the buffer.
        /// @return The buffer capacity.
        [[nodiscard]] auto capacity() const -> size_t override;

        /// @brief Checks if there are remaining elements in the buffer.
        /// @return true if there are remaining elements, false otherwise.
        [[nodiscard]] auto hasRemaining() const -> bool override;

        /// @brief Returns the number of remaining elements in the buffer.
        /// @return The number of remaining elements.
        [[nodiscard]] auto remaining() const -> size_t override;

        /// @brief Gets the remaining unprocessed elements as a vector.
        /// @return The remaining elements in the buffer as a vector.
        [[nodiscard]] auto getRemaining() const -> std::vector<double>;

    private:
        std::vector<double> buffer_{};
    };

    inline DoubleBuffer::DoubleBuffer(const size_t capacity)
    {
        position_ = 0;
        limit_ = capacity;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    inline auto DoubleBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline auto DoubleBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto DoubleBuffer::rewind() -> void
    {
        position_ = 0;
    }

    inline auto DoubleBuffer::compact() -> void
    {
        if (position_ > 0)
        {
            std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                      buffer_.begin() + static_cast<std::ptrdiff_t>(limit_),
                      buffer_.begin());
            limit_ -= position_;
            position_ = 0;
        }
    }

    inline auto DoubleBuffer::put(const double value) -> DoubleBuffer&
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow: Position exceeds limit.");
        }
        buffer_[position_++] = value;
        return *this;
    }

    inline auto DoubleBuffer::put(const std::vector<double>& values) -> DoubleBuffer&
    {
        if (values.empty())
        {
            return *this;
        }

        if (values.size() > remaining())
        {
            throw std::overflow_error("Buffer overflow: Not enough space for all values.");
        }

        for (const double value : values)
        {
            buffer_[position_++] = value;
        }
        return *this;
    }

    inline auto DoubleBuffer::get() -> double
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow: Position exceeds limit.");
        }
        return buffer_[position_++];
    }

    inline auto DoubleBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto DoubleBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    inline auto DoubleBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto DoubleBuffer::limit(const size_t newLimit) -> void
    {
        if (newLimit > capacity_)
        {
            throw std::out_of_range("Limit exceeds capacity.");
        }
        if (position_ > newLimit)
        {
            position_ = newLimit;
        }
        limit_ = newLimit;
    }

    inline auto DoubleBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto DoubleBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline auto DoubleBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    inline auto DoubleBuffer::getRemaining() const -> std::vector<double>
    {
        if (position_ >= limit_)
        {
            return {};
        }
        return std::vector<double>(
            buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
            buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)
        );
    }
}
