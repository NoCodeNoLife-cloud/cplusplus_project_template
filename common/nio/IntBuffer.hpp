#pragma once
#include <vector>
#include <stdexcept>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class IntBuffer final : public interface::IBuffer
    {
    public:
        explicit IntBuffer(size_t capacity);
        auto get() -> int32_t;
        [[nodiscard]] auto get(size_t index) const -> int32_t;
        auto put(int32_t value) -> void;
        auto put(size_t index, int32_t value) -> void;
    private:
        std::vector<int32_t> buffer_{};
    };

    inline IntBuffer::IntBuffer(const size_t capacity): buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    inline auto IntBuffer::get() -> int32_t
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    inline auto IntBuffer::get(const size_t index) const -> int32_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return buffer_[index];
    }

    inline auto IntBuffer::put(const int32_t value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Buffer overflow.");
        }
        buffer_[position_++] = value;
    }

    inline auto IntBuffer::put(const size_t index, const int32_t value) -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        buffer_[index] = value;
    }
}
