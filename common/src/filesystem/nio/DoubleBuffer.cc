#include "src/filesystem/nio/DoubleBuffer.hpp"

#include <algorithm>

namespace common
{
    DoubleBuffer::DoubleBuffer(const size_t capacity)
    {
        position_ = 0;
        limit_ = capacity;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    auto DoubleBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    auto DoubleBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    auto DoubleBuffer::rewind() -> void
    {
        position_ = 0;
    }

    auto DoubleBuffer::compact() -> void
    {
        if (position_ > 0)
        {
            std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_), buffer_.begin());
            limit_ -= position_;
            position_ = 0;
        }
    }

    auto DoubleBuffer::put(const double value) -> DoubleBuffer&
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow: Position exceeds limit.");
        }
        buffer_[position_++] = value;
        return *this;
    }

    auto DoubleBuffer::put(const std::vector<double>& values) -> DoubleBuffer&
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

    auto DoubleBuffer::get() -> double
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow: Position exceeds limit.");
        }
        return buffer_[position_++];
    }

    auto DoubleBuffer::position() const -> size_t
    {
        return position_;
    }

    auto DoubleBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    auto DoubleBuffer::limit() const -> size_t
    {
        return limit_;
    }

    auto DoubleBuffer::limit(const size_t newLimit) -> void
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

    auto DoubleBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    auto DoubleBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    auto DoubleBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    auto DoubleBuffer::getRemaining() const -> std::vector<double>
    {
        if (position_ >= limit_)
        {
            return {};
        }
        return {buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)};
    }
}
