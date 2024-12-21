#pragma once
#include <vector>
#include <stdexcept>
#include <memory>
#include "interface/IfaceBuffer.hpp"

namespace common::nio
{
    class LongBuffer final : public interface::IfaceBuffer
    {
    public:
        explicit LongBuffer(const std::size_t capacity): buffer_(capacity)
        {
            capacity_ = capacity;
            limit_ = capacity;
            position_ = 0;
        }

        auto get() -> long long
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("No remaining elements to get");
            }
            return buffer_[position_++];
        }

        auto put(const long long value) -> void
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("No remaining space to put");
            }
            buffer_[position_++] = value;
        }

    private:
        std::vector<long long> buffer_{};
    };
}
