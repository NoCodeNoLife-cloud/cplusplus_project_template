#include "LongBuffer.hpp"

#include <stdexcept>

namespace common
{
    LongBuffer::LongBuffer(const std::size_t capacity) : buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    auto LongBuffer::get() -> int64_t
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining elements to get");
        }
        return buffer_[position_++];
    }

    auto LongBuffer::put(const int64_t value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining space to put");
        }
        buffer_[position_++] = value;
    }
}
