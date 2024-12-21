#pragma once
#include <vector>
#include <stdexcept>
#include <iterator>
#include "interface/IfaceBuffer.hpp"

namespace common::nio
{
    class FloatBuffer final : public interface::IfaceBuffer
    {
    public:
        explicit FloatBuffer(const size_t capacity): buffer_(capacity, 0.0f)
        {
            limit_ = capacity;
            position_ = 0;
            capacity_ = capacity;
        }

        static auto allocate(const size_t capacity) -> FloatBuffer
        {
            return FloatBuffer(capacity);
        }

        auto put(const float value) -> void
        {
            if (position_ >= limit_)
            {
                throw std::overflow_error("Buffer overflow");
            }
            buffer_[position_++] = value;
        }

        auto put(const std::vector<float>& values) -> void
        {
            if (position_ + values.size() > limit_)
            {
                throw std::overflow_error("Buffer overflow");
            }
            std::ranges::copy(values, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
            position_ += values.size();
        }

        auto get() -> float
        {
            if (position_ >= limit_)
            {
                throw std::underflow_error("Buffer underflow");
            }
            return buffer_[position_++];
        }

        auto get(const size_t length) -> std::vector<float>
        {
            if (position_ + length > limit_)
            {
                throw std::underflow_error("Buffer underflow");
            }
            std::vector result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                               buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
            position_ += length;
            return result;
        }

    private:
        std::vector<float> buffer_{};
    };
}
