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
        auto get() -> long long;
        auto put(long long value) -> void;
    private:
        std::vector<long long> buffer_{};
    };

    inline LongBuffer::LongBuffer(const std::size_t capacity): buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    inline auto LongBuffer::get() -> long long
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining elements to get");
        }
        return buffer_[position_++];
    }

    inline auto LongBuffer::put(const long long value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("No remaining space to put");
        }
        buffer_[position_++] = value;
    }
}
