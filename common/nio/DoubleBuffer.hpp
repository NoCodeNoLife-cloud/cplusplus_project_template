#pragma once
#include <vector>
#include <stdexcept>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class DoubleBuffer final : public interface::IBuffer
    {
    public:
        explicit DoubleBuffer(size_t capacity);
        auto put(double value) -> DoubleBuffer&;
        auto put(const std::vector<double>& values) -> DoubleBuffer&;
        auto get() -> double;
    private:
        std::vector<double> buffer_;
    };

    inline DoubleBuffer::DoubleBuffer(const size_t capacity): buffer_(capacity)
    {
        position_ = 0;
        limit_ = capacity;
        capacity_ = capacity;
    }

    inline auto DoubleBuffer::put(const double value) -> DoubleBuffer&
    {
        if (position_ >= limit_)
        {
            throw std::overflow_error("Buffer overflow: Position exceeds limit.");
        }
        buffer_[position_++] = value;
        return *this;
    }

    inline auto DoubleBuffer::put(const std::vector<double>& values) -> DoubleBuffer&
    {
        for (const double value : values)
        {
            put(value);
        }
        return *this;
    }

    inline auto DoubleBuffer::get() -> double
    {
        if (position_ >= limit_)
        {
            throw std::underflow_error("Buffer underflow: Position exceeds limit.");
        }
        return buffer_[position_++];
    }
}
