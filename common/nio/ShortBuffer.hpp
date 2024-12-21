#pragma once
#include <vector>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class ShortBuffer final : public interface::IBuffer
    {
    public:
        explicit ShortBuffer(size_t capacity);
        static auto wrap(const short* data, size_t size) -> ShortBuffer;
        auto get() -> short;
        [[nodiscard]] auto get(size_t index) const -> short;
        auto put(short value) -> void;
        auto put(size_t index, short value) -> void;
        auto rewind() -> void override;
        auto data() -> short*;
        [[nodiscard]] auto data() const -> const short*;
    private:
        std::vector<short> buffer_{};
    };

    inline ShortBuffer::ShortBuffer(const size_t capacity): buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    inline auto ShortBuffer::wrap(const short* data, const size_t size) -> ShortBuffer
    {
        ShortBuffer sb(size);
        std::memcpy(sb.buffer_.data(), data, size * sizeof(short));
        return sb;
    }

    inline auto ShortBuffer::get() -> short
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        return buffer_[position_++];
    }

    inline auto ShortBuffer::get(const size_t index) const -> short
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index exceeds limit.");
        }
        return buffer_[index];
    }

    inline auto ShortBuffer::put(const short value) -> void
    {
        if (position_ >= limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        buffer_[position_++] = value;
    }

    inline auto ShortBuffer::put(const size_t index, const short value) -> void
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index exceeds limit.");
        }
        buffer_[index] = value;
    }

    inline void ShortBuffer::rewind()
    {
        position_ = 0;
    }

    inline auto ShortBuffer::data() -> short*
    {
        return buffer_.data();
    }

    inline auto ShortBuffer::data() const -> const short*
    {
        return buffer_.data();
    }
}
