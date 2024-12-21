#include "IBuffer.hpp"

#include <stdexcept>

namespace common
{
    IBuffer::~IBuffer() = default;

    auto IBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    auto IBuffer::position() const -> size_t
    {
        return position_;
    }

    auto IBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds the current limit.");
        }
        position_ = newPosition;
    }

    auto IBuffer::limit() const -> size_t
    {
        return limit_;
    }

    auto IBuffer::limit(const size_t newLimit) -> void
    {
        if (newLimit > capacity_)
        {
            throw std::out_of_range("Limit exceeds capacity.");
        }
        limit_ = newLimit;
        if (position_ > limit_)
        {
            position_ = limit_;
        }
    }

    void IBuffer::clear()
    {
        position_ = 0;
        limit_ = capacity_;
    }

    void IBuffer::flip()
    {
        limit_ = position_;
        position_ = 0;
    }

    auto IBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    auto IBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    void IBuffer::rewind()
    {
        position_ = 0;
    }
}
