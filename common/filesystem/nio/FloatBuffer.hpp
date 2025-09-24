#pragma once
#include <ranges>
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A buffer that stores float values.
    /// @details This class provides methods to put and get float values from a buffer.
    /// It is designed to be used in a network I/O context.
    class FloatBuffer final : public IBuffer
    {
    public:
        explicit FloatBuffer(size_t capacity);

        /// @brief Allocates a new FloatBuffer with the specified capacity.
        /// @param capacity The capacity of the buffer.
        /// @return A new FloatBuffer instance.
        static auto allocate(size_t capacity) -> FloatBuffer;

        /// @brief Puts a single float value into the buffer.
        /// @param value The float value to put.
        auto put(float value) -> void;

        /// @brief Puts a vector of float values into the buffer.
        /// @param values The vector of float values to put.
        auto put(const std::vector<float>& values) -> void;

        /// @brief Gets a single float value from the buffer.
        /// @return The float value retrieved.
        auto get() -> float;

        /// @brief Gets a vector of float values from the buffer.
        /// @param length The number of elements to retrieve.
        /// @return A vector containing the retrieved float values.
        auto get(size_t length) -> std::vector<float>;

    private:
        std::vector<float> buffer_{};
    };

    inline FloatBuffer::FloatBuffer(const size_t capacity)
    {
        limit_ = capacity;
        position_ = 0;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    inline auto FloatBuffer::allocate(const size_t capacity) -> FloatBuffer
    {
        return FloatBuffer(capacity);
    }

    inline auto FloatBuffer::put(const float value) -> void
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow");
        }
        buffer_[position_++] = value;
    }

    inline auto FloatBuffer::put(const std::vector<float>& values) -> void
    {
        if (values.empty())
        {
            return;
        }

        if (position_ + values.size() > limit_)
        {
            throw std::overflow_error("Buffer overflow");
        }
        std::ranges::copy(values, buffer_.begin() + static_cast<std::ptrdiff_t>(position_));
        position_ += values.size();
    }

    inline auto FloatBuffer::get() -> float
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow");
        }
        return buffer_[position_++];
    }

    inline auto FloatBuffer::get(const size_t length) -> std::vector<float>
    {
        if (length == 0)
        {
            return {};
        }

        if (position_ + length > limit_)
        {
            throw std::underflow_error("Buffer underflow");
        }
        std::vector<float> result(buffer_.begin() + static_cast<std::ptrdiff_t>(position_),
                                  buffer_.begin() + static_cast<std::ptrdiff_t>(position_ + length));
        position_ += length;
        return result;
    }
}
