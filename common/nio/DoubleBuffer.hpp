#pragma once
#include <vector>
#include <stdexcept>
#include "interface/IfaceBuffer.hpp"

namespace common::nio
{
    class DoubleBuffer final : public interface::IfaceBuffer
    {
    public:
        explicit DoubleBuffer(const size_t capacity): buffer_(capacity)
        {
            position_ = 0;
            limit_ = capacity;
            capacity_ = capacity;
        }

        auto put(const double value) -> DoubleBuffer&
        {
            if (position_ >= limit_)
            {
                throw std::overflow_error("Buffer overflow: Position exceeds limit.");
            }
            buffer_[position_++] = value;
            return *this;
        }

        auto put(const std::vector<double>& values) -> DoubleBuffer&
        {
            for (const double value : values)
            {
                put(value);
            }
            return *this;
        }

        auto get() -> double
        {
            if (position_ >= limit_)
            {
                throw std::underflow_error("Buffer underflow: Position exceeds limit.");
            }
            return buffer_[position_++];
        }

    private:
        std::vector<double> buffer_;
    };
}
