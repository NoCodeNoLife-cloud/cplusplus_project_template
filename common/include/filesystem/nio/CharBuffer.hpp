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
        /// @brief Constructs a CharBuffer with the specified capacity.
        /// @param cap The capacity of the buffer.
        explicit CharBuffer(size_t cap);

        /// @brief Clears the buffer by setting position to 0 and limit to capacity.
        /// @return void
        auto clear() -> void override;

        /// @brief Flips the buffer by setting limit to current position and position to 0.
        /// @return void
        auto flip() -> void override;

        /// @brief Resets the position to 0 while keeping the limit unchanged.
        /// @return void
        auto rewind() -> void override;

        /// @brief Compacts the buffer by removing processed characters.
        /// @return void
        auto compact() -> void;

        /// @brief Puts a single character into the buffer.
        /// @param c The character to put into the buffer.
        /// @return void
        auto put(char c) -> void;

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

        /// @brief Returns the current position in the buffer.
        /// @return The current position.
        [[nodiscard]] auto position() const -> size_t override;

        /// @brief Sets the position in the buffer.
        /// @param newPosition The new position to set.
        /// @return void
        auto position(size_t newPosition) -> void override;

        /// @brief Returns the limit of the buffer.
        /// @return The current limit.
        [[nodiscard]] auto limit() const -> size_t override;

        /// @brief Sets the limit of the buffer.
        /// @param newLimit The new limit to set.
        /// @return void
        auto limit(size_t newLimit) -> void override;

        /// @brief Returns the capacity of the buffer.
        /// @return The buffer capacity.
        [[nodiscard]] auto capacity() const -> size_t override;

        /// @brief Checks if there are remaining elements in the buffer.
        /// @return true if there are remaining elements, false otherwise.
        [[nodiscard]] auto hasRemaining() const -> bool override;

        /// @brief Returns the number of remaining elements in the buffer.
        /// @return The number of remaining elements.
        [[nodiscard]] auto remaining() const -> size_t override;

    private:
        std::string buffer_{};
    };

    inline CharBuffer::CharBuffer(const size_t cap)
        : buffer_(cap, '\0')
    {
        position_ = 0;
        limit_ = cap;
        capacity_ = cap;
    }

    inline auto CharBuffer::clear() -> void
    {
        position_ = 0;
        limit_ = capacity_;
    }

    inline auto CharBuffer::flip() -> void
    {
        limit_ = position_;
        position_ = 0;
    }

    inline auto CharBuffer::rewind() -> void
    {
        position_ = 0;
    }

    inline auto CharBuffer::compact() -> void
    {
        if (position_ > 0)
        {
            std::move(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                      buffer_.begin() + static_cast<std::ptrdiff_t>(limit_),
                      buffer_.begin());
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
        std::ranges::copy(src,
                          buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
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

    inline auto CharBuffer::position() const -> size_t
    {
        return position_;
    }

    inline auto CharBuffer::position(const size_t newPosition) -> void
    {
        if (newPosition > limit_)
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        position_ = newPosition;
    }

    inline auto CharBuffer::limit() const -> size_t
    {
        return limit_;
    }

    inline auto CharBuffer::limit(const size_t newLimit) -> void
    {
        if (newLimit > capacity_)
        {
            throw std::out_of_range("Limit exceeds capacity.");
        }
        if (position_ > newLimit)
        {
            position_ = newLimit;
        }
        limit_ = newLimit;
    }

    inline auto CharBuffer::capacity() const -> size_t
    {
        return capacity_;
    }

    inline auto CharBuffer::hasRemaining() const -> bool
    {
        return position_ < limit_;
    }

    inline auto CharBuffer::remaining() const -> size_t
    {
        return limit_ - position_;
    }
};
