#include "src/filesystem/nio/IntBuffer.hpp"

#include <algorithm>

namespace common
{
    IntBuffer::IntBuffer(const size_t capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
        buffer_.resize(capacity);
    }

    auto IntBuffer::clear()
        -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    auto IntBuffer::flip()
        -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    auto IntBuffer::rewind()
        -> void
    {
        position_ = 0;
    }

    auto IntBuffer::compact()
        -> void
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

    auto IntBuffer::get()
        -> int32_t
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    auto IntBuffer::get(const size_t index) const
        -> int32_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return buffer_[index];
    }

    auto IntBuffer::put(const int32_t value)
        -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow.");
        }
        buffer_[position_++] = value;
    }

    auto IntBuffer::put(const size_t index,
                        const int32_t value)
        -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        buffer_[index] = value;
    }

    auto IntBuffer::getRemaining() const
        -> std::vector<int32_t>
    {
        if (position_ >= limit_)
        {
            return {};
        }
        return {
            buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
            buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)
        };
    }

    auto IntBuffer::position() const
        -> size_t
    {
        return position_;
    }

    auto IntBuffer::position(const size_t newPosition)
        -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    auto IntBuffer::limit() const
        -> size_t
    {
        return limit_;
    }

    auto IntBuffer::limit(const size_t newLimit)
        -> void
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

    auto IntBuffer::capacity() const
        -> size_t
    {
        return capacity_;
    }

    auto IntBuffer::hasRemaining() const
        -> bool
    {
        return position_ < limit_;
    }

    auto IntBuffer::remaining() const
        -> size_t
    {
        return limit_ - position_;
    }
}
