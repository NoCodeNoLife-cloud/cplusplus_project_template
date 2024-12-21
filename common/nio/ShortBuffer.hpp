#pragma once
#include <vector>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include "interface/IfaceBuffer.hpp"

namespace common::nio
{
    class ShortBuffer final : public interface::IfaceBuffer
    {
    public:
        explicit ShortBuffer(const size_t capacity): buffer_(capacity)
        {
            capacity_ = capacity;
            limit_ = capacity;
            position_ = 0;
        }

        static auto wrap(const short* data, const size_t size) -> ShortBuffer
        {
            ShortBuffer sb(size);
            std::memcpy(sb.buffer_.data(), data, size * sizeof(short));
            return sb;
        }

        auto get() -> short
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("Position exceeds limit.");
            }
            return buffer_[position_++];
        }

        [[nodiscard]] auto get(const size_t index) const -> short
        {
            if (index >= limit_)
            {
                throw std::out_of_range("Index exceeds limit.");
            }
            return buffer_[index];
        }

        auto put(const short value) -> void
        {
            if (position_ >= limit_)
            {
                throw std::out_of_range("Position exceeds limit.");
            }
            buffer_[position_++] = value;
        }

        auto put(const size_t index, const short value) -> void
        {
            if (index >= limit_)
            {
                throw std::out_of_range("Index exceeds limit.");
            }
            buffer_[index] = value;
        }

        auto rewind() -> void
        {
            position_ = 0;
        }

        auto data() -> short*
        {
            return buffer_.data();
        }

        [[nodiscard]] auto data() const -> const short*
        {
            return buffer_.data();
        }

    private:
        std::vector<short> buffer_{};
    };
}
