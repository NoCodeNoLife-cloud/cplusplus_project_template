#pragma once
#include <span>
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A byte buffer implementation that manages a fixed-size buffer of bytes.
    /// This class provides methods for putting and getting bytes, supporting both
    /// single-byte operations and bulk operations with vectors of bytes.
    class ByteBuffer final : public IBuffer
    {
    public:
        explicit ByteBuffer(const size_t capacity)
        {
            capacity_ = capacity;
            limit_ = capacity;
            buffer_.resize(capacity);
        }

        /// @brief Puts bytes from a vector into the buffer
        /// @param src The source vector of bytes to put into the buffer
        void put(const std::vector<std::byte>& src)
        {
            if (src.size() > remaining())
            {
                throw std::overflow_error("Insufficient space in buffer");
            }
            std::memcpy(buffer_.data() + position_, src.data(), src.size());
            position_ += src.size();
        }

        /// @brief Puts a single byte into the buffer
        /// @param value The byte value to put into the buffer
        void put(const std::byte value)
        {
            if (!hasRemaining())
            {
                throw std::overflow_error("Buffer overflow");
            }
            buffer_[position_++] = value;
        }

        /// @brief Gets a single byte from the buffer
        /// @return The byte retrieved from the buffer
        auto get() -> std::byte
        {
            if (!hasRemaining())
            {
                throw std::underflow_error("Buffer underflow");
            }
            return buffer_[position_++];
        }

        /// @brief Gets a specified number of bytes from the buffer
        /// @param length The number of bytes to retrieve
        /// @return A vector containing the retrieved bytes
        auto get(const size_t length) -> std::vector<std::byte>
        {
            if (length > remaining())
            {
                throw std::underflow_error("Insufficient data in buffer");
            }
            std::vector result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                               buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
            position_ += length;
            return result;
        }

    private:
        std::vector<std::byte> buffer_;
    };
} // namespace fox
