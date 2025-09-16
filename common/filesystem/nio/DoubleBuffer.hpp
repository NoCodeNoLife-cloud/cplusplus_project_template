#pragma once
#include <stdexcept>
#include <vector>

#include "interface/IBuffer.hpp"

namespace fox
{
    /// @brief A DoubleBuffer class that implements the IBuffer interface for handling double precision floating point
    /// numbers. This class provides functionality to put and get double values from a buffer with a specified capacity.
    class DoubleBuffer final : public IBuffer
    {
    public:
        explicit DoubleBuffer(size_t capacity);

        /// @brief Puts a single double value into the buffer.
        /// @param value The double value to be put into the buffer.
        /// @return Reference to the current DoubleBuffer object.
        auto put(double value) -> DoubleBuffer&;

        /// @brief Puts a vector of double values into the buffer.
        /// @param values The vector of double values to be put into the buffer.
        /// @return Reference to the current DoubleBuffer object.
        auto put(const std::vector<double>& values) -> DoubleBuffer&;

        /// @brief Gets a single double value from the buffer.
        /// @return The double value retrieved from the buffer.
        auto get() -> double;

    private:
        std::vector<double> buffer_;
    };

    inline DoubleBuffer::DoubleBuffer(const size_t capacity)
    {
        position_ = 0;
        limit_ = capacity;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    inline auto DoubleBuffer::put(const double value) -> DoubleBuffer&
    {
        if (!hasRemaining())
        {
            throw std::overflow_error("Buffer overflow: Position exceeds limit.");
        }
        buffer_[position_++] = value;
        return *this;
    }

    inline auto DoubleBuffer::put(const std::vector<double>& values) -> DoubleBuffer&
    {
        if (values.empty())
        {
            return *this;
        }

        if (values.size() > remaining())
        {
            throw std::overflow_error("Buffer overflow: Not enough space for all values.");
        }

        for (const double value : values)
        {
            buffer_[position_++] = value;
        }
        return *this;
    }

    inline auto DoubleBuffer::get() -> double
    {
        if (!hasRemaining())
        {
            throw std::underflow_error("Buffer underflow: Position exceeds limit.");
        }
        return buffer_[position_++];
    }
} // namespace fox
