#pragma once
#include <vector>
#include <span>
#include <cstring>
#include <stdexcept>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class ByteBuffer final : public interface::IBuffer
    {
    public:
        explicit ByteBuffer(size_t capacity);
        void put(const std::vector<std::byte>& src);
        void put(std::byte value);
        auto get() -> std::byte;
        auto get(size_t length) -> std::vector<std::byte>;
    private:
        std::vector<std::byte> buffer_;
    };

    inline ByteBuffer::ByteBuffer(const size_t capacity): buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
    }

    inline void ByteBuffer::put(const std::vector<std::byte>& src)
    {
        if (src.size() > remaining())
        {
            throw std::overflow_error("Insufficient space in buffer");
        }
        std::memcpy(buffer_.data() + position_, src.data(), src.size());
        position_ += src.size();
    }

    inline void ByteBuffer::put(const std::byte value)
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow");
        }
        buffer_[position_++] = value;
    }

    inline auto ByteBuffer::get() -> std::byte
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow");
        }
        return buffer_[position_++];
    }

    inline auto ByteBuffer::get(const size_t length) -> std::vector<std::byte>
    {
        if (length > remaining())
        {
            throw std::underflow_error("Insufficient data in buffer");
        }
        std::vector<std::byte> result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
        position_ += length;
        return result;
    }
}
