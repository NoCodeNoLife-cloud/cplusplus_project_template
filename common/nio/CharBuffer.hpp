#pragma once
#include <string>
#include <stdexcept>
#include <span>
#include <algorithm>
#include "interface/IBuffer.hpp"

namespace common::nio
{
    class CharBuffer final : public interface::IBuffer
    {
    public:
        explicit CharBuffer(size_t cap);
        auto compact() -> void;
        auto put(char c) -> void;
        auto put(const std::u16string& src) -> void;
        auto get() -> char16_t;
        [[nodiscard]] auto getRemaining() const -> std::string;
    private:
        std::string buffer_{};
    };

    inline CharBuffer::CharBuffer(const size_t cap): buffer_(cap, u'\0')
    {
        position_ = 0;
        limit_ = cap;
        capacity_ = cap;
    }

    inline auto CharBuffer::compact() -> void
    {
        if (position_ > 0)
        {
            std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_), buffer_.begin());
            limit_ -= position_;
            position_ = 0;
        }
    }

    inline auto CharBuffer::put(const char c) -> void
    {
        if (position_ >= limit_)
        {
            throw std::overflow_error("Buffer overflow.");
        }
        buffer_[position_++] = c;
    }

    inline auto CharBuffer::put(const std::u16string& src) -> void
    {
        if (position_ + src.size() > limit_)
        {
            throw std::overflow_error("Buffer overflow.");
        }
        std::ranges::copy(src, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
        position_ += src.size();
    }

    inline auto CharBuffer::get() -> char16_t
    {
        if (position_ >= limit_)
        {
            throw std::underflow_error("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    inline auto CharBuffer::getRemaining() const -> std::string
    {
        return {buffer_.begin() + static_cast<std::ptrdiff_t>(position_), buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)};
    }
}
