#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common
{
    class IntBuffer final : public IBuffer
    {
    public:
        explicit IntBuffer(size_t capacity);
        auto get() -> int32_t;
        [[nodiscard]] auto get(size_t index) const -> int32_t;
        auto put(int32_t value) -> void;
        auto put(size_t index, int32_t value) -> void;

    private:
        std::vector<int32_t> buffer_{};
    };
}
