#pragma once
#include <algorithm>
#include <span>
#include <stdexcept>
#include <string>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A character buffer that implements the IBuffer interface.
    /// @details This class provides functionality for managing a buffer of characters,
    ///          including operations such as putting and getting characters, compacting
    ///          the buffer, and retrieving remaining unprocessed characters.
    class CharBuffer final : public IBuffer
    {
    public:
        explicit CharBuffer(const size_t cap);

        /// @brief Compacts the buffer by removing processed characters.
        /// @return void
        auto compact() -> void;

        /// @brief Puts a single character into the buffer.
        /// @param c The character to put into the buffer.
        /// @return void
        auto put(const char c) -> void;

        /// @brief Puts a string into the buffer.
        /// @param src The string to put into the buffer.
        /// @return void
        auto put(const std::string& src) -> void;

        /// @brief Gets a single character from the buffer.
        /// @return The character retrieved from the buffer.
        auto get() -> char;

        /// @brief Gets the remaining unprocessed characters as a string.
        /// @return The remaining characters in the buffer as a string.
        [[nodiscard]] auto getRemaining() const -> std::string;

    private:
        std::string buffer_{};
    };

    inline CharBuffer::CharBuffer(const size_t cap)
    {
        position_ = 0;
        limit_ = cap;
        capacity_ = cap;
        buffer_ = std::string(cap, '\0');
    }

    inline auto CharBuffer::compact() -> void
    {
        if (position_ > 0)
        {
            std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                      buffer_.begin() + static_cast<std::ptrdiff_t>(limit_), buffer_.begin());
            limit_ -= position_;
            position_ = 0;
        }
    }

    inline auto CharBuffer::put(const char c) -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow.");
        }
        buffer_[position_++] = c;
    }

    inline auto CharBuffer::put(const std::string& src) -> void
    {
        if (src.empty())
        {
            return;
        }

        if (position_ + src.size() > limit_)
        {
            throw std::overflow_error("Buffer overflow.");
        }
        std::copy(src.begin(), src.end(), buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
        position_ += src.size();
    }

    inline auto CharBuffer::get() -> char
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow.");
        }
        return buffer_[position_++];
    }

    inline auto CharBuffer::getRemaining() const -> std::string
    {
        if (position_ >= limit_)
        {
            return {};
        }
        return {
            buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
            buffer_.begin() + static_cast<std::ptrdiff_t>(limit_)
        };
    }
};

} // namespace fox
