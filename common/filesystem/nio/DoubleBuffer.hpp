#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common
{
    class DoubleBuffer final : public IBuffer
    {
    public:
        explicit DoubleBuffer(size_t capacity);
        auto put(double value) -> DoubleBuffer&;
        auto put(const std::vector<double>& values) -> DoubleBuffer&;
        auto get() -> double;

    private:
        std::vector<double> buffer_;
    };
}
