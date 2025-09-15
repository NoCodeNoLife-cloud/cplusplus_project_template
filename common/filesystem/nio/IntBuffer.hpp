#pragma once
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A buffer that stores 32-bit integers.
    /// @details This class provides a way to store and manipulate a sequence of 32-bit integers in a buffer.
    /// It implements the IBuffer interface and provides methods to get and put integers in the buffer.
    class IntBuffer final : public IBuffer
    {
    public:
        explicit IntBuffer(const size_t capacity);

        /// @brief Get the current element and advance the position.
        /// @return The current element.
        auto get() -> int32_t;

        /// @brief Get the element at the specified index.
        /// @param index The index of the element to get.
        /// @return The element at the specified index.
        [[nodiscard]] auto get(const size_t index) const -> int32_t;

        /// @brief Put the specified value at the current position and advance the position.
        /// @param value The value to put.
        auto put(const int32_t value) -> void;

        /// @brief Put the specified value at the specified index.
        /// @param index The index at which to put the value.
        /// @param value The value to put.
        auto put(const size_t index, const int32_t value) -> void;

    private:
        std::vector<int32_t> buffer_{};
    };

    inline IntBuffer::IntBuffer(const size_t capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
        buffer_.resize(capacity);
    }

    inline auto IntBuffer::get() -> int32_t
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    inline auto IntBuffer::get(const size_t index) const -> int32_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return buffer_[index];
    }

    inline auto IntBuffer::put(const int32_t value) -> void
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("Buffer overflow.");
        }
        buffer_[position_++] = value;
    }

    inline auto IntBuffer::put(const size_t index, const int32_t value) -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        buffer_[index] = value;
    }
} // namespace fox
