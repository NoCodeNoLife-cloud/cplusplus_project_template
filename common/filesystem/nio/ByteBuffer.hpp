#pragma once
#include <span>
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A byte buffer implementation that manages a fixed-size buffer of bytes.
    /// This class provides methods for putting and getting bytes, supporting both
    /// single-byte operations and bulk operations with vectors of bytes.
    class ByteBuffer final : public IBuffer
    {
    public:
        explicit ByteBuffer(size_t capacity);

        /// @brief Get the capacity of the buffer
        /// @return The capacity of the buffer
        [[nodiscard]] auto capacity() const -> size_t override;

        /// @brief Get the current position of the buffer
        /// @return The current position of the buffer
        [[nodiscard]] auto position() const -> size_t override;

        /// @brief Set the position of the buffer
        /// @param newPosition The new position to set
        /// @throws std::out_of_range If newPosition exceeds the current limit
        auto position(size_t newPosition) -> void override;

        /// @brief Get the limit of the buffer
        /// @return The limit of the buffer
        [[nodiscard]] auto limit() const -> size_t override;

        /// @brief Set the limit of the buffer
        /// @param newLimit The new limit to set
        /// @throws std::out_of_range If newLimit exceeds capacity
        auto limit(size_t newLimit) -> void override;

        /// @brief Clear the buffer by resetting position and limit
        auto clear() -> void override;

        /// @brief Flip the buffer by setting limit to current position and resetting position to zero
        auto flip() -> void override;

        /// @brief Rewind the buffer by resetting position to zero
        auto rewind() -> void override;

        /// @brief Get the number of remaining elements in the buffer
        /// @return The number of remaining elements
        [[nodiscard]] auto remaining() const -> size_t override;

        /// @brief Check if there are remaining elements in the buffer
        /// @return True if there are remaining elements, false otherwise
        [[nodiscard]] auto hasRemaining() const -> bool override;

        /// @brief Puts a single byte into the buffer
        /// @param value The byte value to put into the buffer
        /// @throws std::overflow_error If buffer has no remaining space
        auto put(std::byte value) -> void;

        /// @brief Puts bytes from a vector into the buffer
        /// @param src The source vector of bytes to put into the buffer
        /// @throws std::overflow_error If buffer has insufficient space
        auto put(const std::vector<std::byte>& src) -> void;

        /// @brief Gets a single byte from the buffer
        /// @return The byte retrieved from the buffer
        /// @throws std::underflow_error If buffer has no remaining data
        auto get() -> std::byte;

        /// @brief Gets a specified number of bytes from the buffer
        /// @param length The number of bytes to retrieve
        /// @return A vector containing the retrieved bytes
        /// @throws std::underflow_error If buffer has insufficient data
        auto get(size_t length) -> std::vector<std::byte>;

    private:
        std::vector<std::byte> buffer_;
    };

    inline ByteBuffer::ByteBuffer(const size_t capacity)
        : buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
    }

    inline auto ByteBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto ByteBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto ByteBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds the current limit.");
        }
        position_ = newPosition;
    }

    inline auto ByteBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto ByteBuffer::limit(const size_t newLimit) -> void
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

    inline auto ByteBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline auto ByteBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto ByteBuffer::rewind() -> void
    {
        position_ = 0;
    }

    inline auto ByteBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    inline auto ByteBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline auto ByteBuffer::put(const std::byte value) -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow");
        }
        buffer_[position_++] = value;
    }

    inline auto ByteBuffer::put(const std::vector<std::byte>& src) -> void
    {
        if (src.empty())
        {
            return;
        }

        if (src.size() > remaining())
        {
            throw std::overflow_error("Insufficient space in buffer");
        }

        std::memcpy(buffer_.data() + position_, src.data(), src.size());
        position_ += src.size();
    }

    inline auto ByteBuffer::get() -> std::byte
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow");
        }
        return buffer_[position_++];
    }

    inline auto ByteBuffer::get(const size_t length) -> std::vector<std::byte>
    {
        if (length == 0)
        {
            return {};
        }

        if (length > remaining())
        {
            throw std::underflow_error("Insufficient data in buffer");
        }

        std::vector<std::byte> result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                                      buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
        position_ += length;
        return result;
    }
}
