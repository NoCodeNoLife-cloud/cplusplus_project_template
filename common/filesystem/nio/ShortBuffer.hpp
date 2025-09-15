#pragma once
#include <cstring>
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A buffer for short integer (int16_t) data.
    /// ShortBuffer provides a way to store, read, and write short integer data in a
    /// sequential manner. It implements the IBuffer interface and supports operations
    /// like get, put, and rewind.
    class ShortBuffer final : public IBuffer
    {
    public:
        explicit ShortBuffer(const size_t capacity);

        /// @brief Wraps an existing array of int16_t data into a ShortBuffer.
        /// @param data Pointer to the data to wrap.
        /// @param size Size of the data array.
        /// @return A new ShortBuffer instance wrapping the provided data.
        static auto wrap(const int16_t* data, const size_t size) -> ShortBuffer;

        /// @brief Reads the next int16_t value from the buffer.
        /// @return The next int16_t value.
        auto get() -> int16_t;

        /// @brief Reads an int16_t value at the specified index.
        /// @param index Index of the value to read.
        /// @return The int16_t value at the specified index.
        [[nodiscard]] auto get(const size_t index) const -> int16_t;

        /// @brief Writes an int16_t value to the buffer at the current position.
        /// @param value The value to write.
        auto put(const int16_t value) -> void;

        /// @brief Writes an int16_t value to the buffer at the specified index.
        /// @param index Index where the value should be written.
        /// @param value The value to write.
        auto put(const size_t index, const int16_t value) -> void;

        /// @brief Resets the position of the buffer to zero.
        auto rewind() -> void override;

        /// @brief Returns a pointer to the underlying data array.
        /// @return Pointer to the data array.
        auto data() -> int16_t*;

        /// @brief Returns a const pointer to the underlying data array.
        /// @return Const pointer to the data array.
        [[nodiscard]] auto data() const -> const int16_t*;

    private:
        std::vector<int16_t> buffer_{};
    };

    inline ShortBuffer::ShortBuffer(const size_t capacity) : buffer_(capacity)
    {
        capacity_ = capacity;
        limit_ = capacity;
        position_ = 0;
    }

    inline auto ShortBuffer::wrap(const int16_t* data, const size_t size) -> ShortBuffer
    {
        ShortBuffer sb(size);
        if (data != nullptr && size > 0)
        {
            std::memcpy(sb.buffer_.data(), data, size * sizeof(int16_t));
        }
        return sb;
    }

    inline auto ShortBuffer::get() -> int16_t
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        return buffer_[position_++];
    }

    inline auto ShortBuffer::get(const size_t index) const -> int16_t
    {
        if (index >= limit_)
        {
            throw std::out_of_range("Index exceeds limit.");
        }
        return buffer_[index];
    }

    inline auto ShortBuffer::put(const int16_t value) -> void
    {
        if (!hasRemaining())
        {
            throw std::out_of_range("Position exceeds limit.");
        }
        buffer_[position_++] = value;
    }

    inline auto ShortBuffer::put(const size_t index, const int16_t value) -> void
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

    inline auto ShortBuffer::data() -> int16_t*
    {
        return buffer_.data();
    }

    inline auto ShortBuffer::data() const -> const int16_t*
    {
        return buffer_.data();
    }
} // namespace fox
