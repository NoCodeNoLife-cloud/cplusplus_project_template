#include "src/filesystem/nio/ShortBuffer.hpp"

namespace fox
{
    ShortBuffer::ShortBuffer(const size_t capacity)
        : buffer_(capacity), capacity_(capacity), limit_(capacity)
    {
    }

    auto ShortBuffer::wrap(const int16_t* data, const size_t size) -> ShortBuffer
    {
        ShortBuffer sb(size);
        if (data != nullptr && size > 0)
        {
            std::memcpy(sb.buffer_.data(), data, size * sizeof(int16_t));
        }
        return sb;
    }

    auto ShortBuffer::get() -> int16_t
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("No remaining elements to get");
        }
        return buffer_[position_++];
    }

    auto ShortBuffer::get(const size_t index) const -> int16_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return buffer_[index];
    }

    auto ShortBuffer::put(const int16_t value) -> void
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("No remaining space to put");
        }
        buffer_[position_++] = value;
    }

    auto ShortBuffer::put(const size_t index, const int16_t value) -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds");
        }
        buffer_[index] = value;
    }

    auto ShortBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    auto ShortBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    auto ShortBuffer::position() const -> size_t
    {
        return position_;
    }

    auto ShortBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position out of range");
        }
        position_ = newPosition;
    }

    auto ShortBuffer::limit() const -> size_t
    {
        return limit_;
    }

    auto ShortBuffer::limit(const size_t newLimit) -> void
    {
        if (newLimit > capacity_)
        {
            throw std::out_of_range("Limit exceeds capacity");
        }
        limit_ = newLimit;
        if (position_ > limit_)
        {
            position_ = limit_;
        }
    }

    auto ShortBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    auto ShortBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    auto ShortBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    auto ShortBuffer::rewind() -> void
    {
        position_ = 0;
    }

    auto ShortBuffer::data() -> int16_t*
    {
        return buffer_.data();
    }

    auto ShortBuffer::data() const -> const int16_t*
    {
        return buffer_.data();
    }
}
