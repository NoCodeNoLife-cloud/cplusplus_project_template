#include "src/filesystem/nio/FloatBuffer.hpp"

#include <algorithm>

namespace common
{
    FloatBuffer::FloatBuffer(const size_t capacity)
    {
        limit_ = capacity;
        position_ = 0;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    auto FloatBuffer::allocate(const size_t capacity)
        -> FloatBuffer
    {
        return FloatBuffer(capacity);
    }

    auto FloatBuffer::clear()
        -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    auto FloatBuffer::flip()
        -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    auto FloatBuffer::rewind()
        -> void
    {
        position_ = 0;
    }

    auto FloatBuffer::compact()
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

    auto FloatBuffer::put(const float value)
        -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow");
        }
        buffer_[position_++] = value;
    }

    auto FloatBuffer::put(const std::vector<float>& values)
        -> void
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

    auto FloatBuffer::get()
        -> float
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow");
        }
        return buffer_[position_++];
    }

    auto FloatBuffer::get(const size_t length)
        -> std::vector<float>
    {
        if (length == 0)
        {
            return {};
        }

        if (position_ + length > limit_)
        {
            throw std::underflow_error("Buffer underflow");
        }
        std::vector result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                           buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
        position_ += length;
        return result;
    }

    auto FloatBuffer::getRemaining() const
        -> std::vector<float>
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

    auto FloatBuffer::position() const
        -> size_t
    {
        return position_;
    }

    auto FloatBuffer::position(const size_t newPosition)
        -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    auto FloatBuffer::limit() const
        -> size_t
    {
        return limit_;
    }

    auto FloatBuffer::limit(const size_t newLimit)
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

    auto FloatBuffer::capacity() const
        -> size_t
    {
        return capacity_;
    }

    auto FloatBuffer::hasRemaining() const
        -> bool
    {
        return position_ < limit_;
    }

    auto FloatBuffer::remaining() const
        -> size_t
    {
        return limit_ - position_;
    }
}
