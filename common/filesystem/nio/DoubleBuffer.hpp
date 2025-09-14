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
    explicit DoubleBuffer(size_t capacity)
    {
        position_ = 0;
        limit_ = capacity;
        capacity_ = capacity;
        buffer_.resize(capacity);
    }

    /// @brief Puts a single double value into the buffer.
    /// @param value The double value to be put into the buffer.
    /// @return Reference to the current DoubleBuffer object.
    auto put(double value) -> DoubleBuffer &
    {
        if (position_ >= limit_)
        {
            throw std::overflow_error("Buffer overflow: Position exceeds limit.");
        }
        buffer_[position_++] = value;
        return *this;
    }

    /// @brief Puts a vector of double values into the buffer.
    /// @param values The vector of double values to be put into the buffer.
    /// @return Reference to the current DoubleBuffer object.
    auto put(const std::vector<double> &values) -> DoubleBuffer &
    {
        for (const double value : values)
        {
            put(value);
        }
        return *this;
    }

    /// @brief Gets a single double value from the buffer.
    /// @return The double value retrieved from the buffer.
    auto get() -> double
    {
        if (position_ >= limit_)
        {
            throw std::underflow_error("Buffer underflow: Position exceeds limit.");
        }
        return buffer_[position_++];
    }

  private:
    std::vector<double> buffer_;
};
} // namespace fox