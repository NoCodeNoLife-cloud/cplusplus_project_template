#include "src/filesystem/nio/CharBuffer.hpp"

#include <algorithm>
#include <stdexcept>

namespace fox
{
    CharBuffer::CharBuffer(const size_t cap)
        : buffer_(cap, '\0')
    {
        position_ = 0;
        limit_ = cap;
        capacity_ = cap;
    }

    auto CharBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    auto CharBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    auto CharBuffer::rewind() -> void
    {
        position_ = 0;
    }

    auto CharBuffer::compact() -> void
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

    auto CharBuffer::put(const char c) -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow.");
        }
        buffer_[position_++] = c;
    }

    auto CharBuffer::put(const std::string& src) -> void
    {
        if (src.empty())
        {
            return;
        }

        if (position_ + src.size() > limit_)
        {
            throw std::overflow_error("Buffer overflow.");
        }
        std::ranges::copy(src,
                          buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
        position_ += src.size();
    }

    auto CharBuffer::get() -> char
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    auto CharBuffer::getRemaining() const -> std::string
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

    auto CharBuffer::position() const -> size_t
    {
        return position_;
    }

    auto CharBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    auto CharBuffer::limit() const -> size_t
    {
        return limit_;
    }

    auto CharBuffer::limit(const size_t newLimit) -> void
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

    auto CharBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    auto CharBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    auto CharBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }
}
