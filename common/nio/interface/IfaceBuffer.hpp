#pragma once
namespace common::interface
{
    class IfaceBuffer abstract
    {
    public:
        virtual ~IfaceBuffer() = default;

        [[nodiscard]] virtual auto capacity() const -> size_t
        {
            return capacity_;
        }

        [[nodiscard]] virtual auto position() const -> size_t
        {
            return position_;
        }

        virtual auto position(const size_t newPosition) -> void
        {
            if (newPosition > limit_)
            {
                throw std::out_of_range("Position exceeds the current limit.");
            }
            position_ = newPosition;
        }

        [[nodiscard]] virtual auto limit() const -> size_t
        {
            return limit_;
        }

        virtual auto limit(const size_t newLimit) -> void
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

        virtual void clear()
        {
            position_ = 0;
            limit_ = capacity_;
        }

        virtual void flip()
        {
            limit_ = position_;
            position_ = 0;
        }

        [[nodiscard]] virtual auto remaining() const -> size_t
        {
            return limit_ - position_;
        }

        [[nodiscard]] virtual auto hasRemaining() const -> bool
        {
            return position_ < limit_;
        }

        virtual void rewind()
        {
            position_ = 0;
        }

    protected:
        size_t position_{0};
        size_t limit_{0};
        size_t capacity_{0};
    };
}
