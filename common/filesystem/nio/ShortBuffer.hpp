#pragma once
#include <vector>

#include "interface/IBuffer.hpp"

namespace common
{
    class ShortBuffer final : public IBuffer
    {
    public:
        explicit ShortBuffer(size_t capacity);
        static auto wrap(const int16_t* data, size_t size) -> ShortBuffer;
        auto get() -> int16_t;
        [[nodiscard]] auto get(size_t index) const -> int16_t;
        auto put(int16_t value) -> void;
        auto put(size_t index, int16_t value) -> void;
        auto rewind() -> void override;
        auto data() -> int16_t*;
        [[nodiscard]] auto data() const -> const int16_t*;

    private:
        std::vector<int16_t> buffer_{};
    };
}
