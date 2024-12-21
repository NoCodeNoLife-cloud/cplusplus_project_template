#pragma once
namespace common::interface
{
    class IBuffer abstract
    {
    public:
        virtual ~IBuffer();
        [[nodiscard]] virtual auto capacity() const -> size_t;
        [[nodiscard]] virtual auto position() const -> size_t;
        virtual auto position(size_t newPosition) -> void;
        [[nodiscard]] virtual auto limit() const -> size_t;
        virtual auto limit(size_t newLimit) -> void;
        virtual void clear();
        virtual void flip();
        [[nodiscard]] virtual auto remaining() const -> size_t;
        [[nodiscard]] virtual auto hasRemaining() const -> bool;
        virtual void rewind();
    protected:
        size_t position_{0};
        size_t limit_{0};
        size_t capacity_{0};
    };

    inline IBuffer::~IBuffer() = default;

    inline auto IBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto IBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto IBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds the current limit.");
        }
        position_ = newPosition;
    }

    inline auto IBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto IBuffer::limit(const size_t newLimit) -> void
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

    inline void IBuffer::clear()
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline void IBuffer::flip()
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto IBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }

    inline auto IBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline void IBuffer::rewind()
    {
        position_ = 0;
    }
}
