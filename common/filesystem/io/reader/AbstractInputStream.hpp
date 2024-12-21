#pragma once
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"


namespace common
{
    class AbstractInputStream abstract : public ICloseable
    {
    public:
        ~AbstractInputStream() override;
        [[nodiscard]] virtual auto available() -> size_t = 0;
        virtual auto mark(int32_t readLimit) -> void;
        [[nodiscard]] virtual auto markSupported() const -> bool;
        virtual auto read() -> std::byte = 0;
        virtual auto read(std::vector<std::byte>& buffer) -> size_t;
        virtual auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t;
        virtual auto reset() -> void;
        virtual auto skip(size_t n) -> size_t;
    };
}
