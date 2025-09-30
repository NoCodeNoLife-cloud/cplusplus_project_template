#pragma once
#include <ranges>
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A buffer that stores float values.
    /// @details This class provides methods to put and get float values from a buffer.
    /// It is designed to be used in a network I/O context.
    class FloatBuffer final : public IBuffer
    {
    public:
        /// @brief Constructs a FloatBuffer with the specified capacity.
        /// @param capacity The capacity of the buffer.
        explicit FloatBuffer(size_t capacity);

        /// @brief Allocates a new FloatBuffer with the specified capacity.
        /// @param capacity The capacity of the buffer.
        /// @return A new FloatBuffer instance.
        static auto allocate(size_t capacity) -> FloatBuffer;

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

        /// @brief Puts a single float value into the buffer.
        /// @param value The float value to put.
        /// @return void
        auto put(float value) -> void;

        /// @brief Puts a vector of float values into the buffer.
        /// @param values The vector of float values to put.
        /// @return void
        auto put(const std::vector<float>& values) -> void;

        /// @brief Gets a single float value from the buffer.
        /// @return The float value retrieved.
        auto get() -> float;

        /// @brief Gets a vector of float values from the buffer.
        /// @param length The number of elements to retrieve.
        /// @return A vector containing the retrieved float values.
        auto get(size_t length) -> std::vector<float>;

        /// @brief Gets the remaining unprocessed elements as a vector.
        /// @return The remaining elements in the buffer as a vector.
        [[nodiscard]] auto getRemaining() const -> std::vector<float>;

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

    private:
        std::vector<float> buffer_{};
    };

    inline FloatBuffer::FloatBuffer(const size_t capacity)
    {
        limit_ = capacity;
        position_ = 0;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    inline auto FloatBuffer::allocate(const size_t capacity) -> FloatBuffer
    {
        return FloatBuffer(capacity);
    }

    inline auto FloatBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline auto FloatBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto FloatBuffer::rewind() -> void
    {
        position_ = 0;
    }

    inline auto FloatBuffer::compact() -> void
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

    inline auto FloatBuffer::put(const float value) -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow");
        }
        buffer_[position_++] = value;
    }

    inline auto FloatBuffer::put(const std::vector<float>& values) -> void
    {
        if (values.empty())
        {
            return;
        }

        if (position_ + values.size() > limit_)
        {
            throw std::overflow_error("Buffer overflow");
        }
        std::ranges::copy(values, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
        position_ += values.size();
    }

    inline auto FloatBuffer::get() -> float
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow");
        }
        return buffer_[position_++];
    }

    inline auto FloatBuffer::get(const size_t length) -> std::vector<float>
    {
        if (length == 0)
        {
            return {};
        }

        if (position_ + length > limit_)
        {
            throw std::underflow_error("Buffer underflow");
        }
        std::vector<float> result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                                  buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
        position_ += length;
        return result;
    }

    inline auto FloatBuffer::getRemaining() const -> std::vector<float>
    {
        if (position_ >= limit_)
        {
            return {};
        }
        return std::vector<float>(
            buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
            buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)
        );
    }

    inline auto FloatBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto FloatBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    inline auto FloatBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto FloatBuffer::limit(const size_t newLimit) -> void
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

    inline auto FloatBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto FloatBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline auto FloatBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }
}
