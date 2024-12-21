#include "IntBuffer.hpp"

#include <stdexcept>

namespace common
{
    IntBuffer::IntBuffer(const size_t capacity) : buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    auto IntBuffer::get() -> int32_t
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    auto IntBuffer::get(const size_t index) const -> int32_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return buffer_[index];
    }

    auto IntBuffer::put(const int32_t value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Buffer overflow.");
        }
        buffer_[position_++] = value;
    }

    auto IntBuffer::put(const size_t index, const int32_t value) -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        buffer_[index] = value;
    }
}
