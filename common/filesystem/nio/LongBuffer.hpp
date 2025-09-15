#pragma once
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A buffer that stores 64-bit signed integers
    class LongBuffer final : public IBuffer
    {
    public:
        explicit LongBuffer(const std::size_t capacity);

        /// @brief Get the current value from the buffer
        /// @return The current value
        auto get() -> int64_t;

        /// @brief Put a value into the buffer
        /// @param value The value to put
        auto put(const int64_t value) -> void;

    private:
        std::vector<int64_t> buffer_{};
    };

    inline LongBuffer::LongBuffer(const std::size_t capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
        buffer_.resize(capacity);
    }

    inline auto LongBuffer::get() -> int64_t
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("No remaining elements to get");
        }
        return buffer_[position_++];
    }

    inline auto LongBuffer::put(const int64_t value) -> void
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("No remaining space to put");
        }
        buffer_[position_++] = value;
    }
} // namespace fox
