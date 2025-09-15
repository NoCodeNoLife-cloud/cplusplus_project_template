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
        explicit LongBuffer(const std::size_t capacity)
        {
            capacity_ = capacity;
            limit_ = capacity;
            position_ = 0;
        }

        /// @brief Get the current value from the buffer
        /// @return The current value
        auto get() -> int64_t
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("No remaining elements to get");
            }
            return buffer_[position_++];
        }

        /// @brief Put a value into the buffer
        /// @param value The value to put
        auto put(const int64_t value) -> void
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("No remaining space to put");
            }
            buffer_[position_++] = value;
        }

    private:
        std::vector<int64_t> buffer_{};
    };
} // namespace fox
