#pragma once
#include <vector>
#include <stdexcept>
#include "interface/IfaceBuffer.hpp"

namespace common::nio
{
    class IntBuffer final : public interface::IfaceBuffer
    {
    public:
        explicit IntBuffer(const size_t capacity) : buffer_(capacity)
        {
            capacity_ = capacity;
            limit_ = capacity;
            position_ = 0;
        }

        auto get() -> int
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("Buffer underflow.");
            }
            return buffer_[position_++];
        }

        [[nodiscard]] auto get(const size_t index) const -> int
        {
            if (index >= limit_)
            {
                throw std::out_of_range("Index out of bounds.");
            }
            return buffer_[index];
        }

        auto put(const int value) -> void
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("Buffer overflow.");
            }
            buffer_[position_++] = value;
        }

        auto put(const size_t index, const int value) -> void
        {
            if (index >= limit_)
            {
                throw std::out_of_range("Index out of bounds.");
            }
            buffer_[index] = value;
        }

    private:
        std::vector<int> buffer_{};
    };
}
