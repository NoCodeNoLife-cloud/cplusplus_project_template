#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common
{
    class LongBuffer final : public IBuffer
    {
    public:
        explicit LongBuffer(std::size_t capacity);
        auto get() -> int64_t;
        auto put(int64_t value) -> void;

    private:
        std::vector<int64_t> buffer_{};
    };
}
