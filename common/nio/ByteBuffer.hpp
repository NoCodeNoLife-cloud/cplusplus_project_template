#pragma once
#include <vector>
#include <span>

#include "interface/IBuffer.hpp"

namespace common::nio
{
    class ByteBuffer final : public interface::IBuffer
    {
    public:
        explicit ByteBuffer(size_t capacity);
        void put(const std::vector<std::byte>& src);
        void put(std::byte value);
        auto get() -> std::byte;
        auto get(size_t length) -> std::vector<std::byte>;
    private:
        std::vector<std::byte> buffer_;
    };
}
