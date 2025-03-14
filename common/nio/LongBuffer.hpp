#pragma once
#include <vector>
#include <stdexcept>
#include <memory>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class LongBuffer final : public interface::IBuffer
    {
    public:
        explicit LongBuffer(std::size_t capacity);
        auto get() -> int64_t;
        auto put(int64_t value) -> void;
    private:
        std::vector<int64_t> buffer_{};
    };

    inline LongBuffer::LongBuffer(const std::size_t capacity): buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    inline auto LongBuffer::get() -> int64_t
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining elements to get");
        }
        return buffer_[position_++];
    }

    inline auto LongBuffer::put(const int64_t value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining space to put");
        }
        buffer_[position_++] = value;
    }
}
