#pragma once
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceReadable.hpp"

namespace common::io
{
    class AbstractReader abstract : public iface::IfaceCloseable, public iface::IfaceReadable
    {
    public:
        ~AbstractReader() override = default;

        auto read() -> int override
        {
            std::vector<char> buffer(1);
            if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1)
            {
                return -1;
            }
            return buffer[0];
        }

        virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;

        virtual auto read(std::vector<char>& cBuf) -> size_t
        {
            return read(cBuf, 0, static_cast<int>(cBuf.size()));
        }

        [[nodiscard]] virtual auto markSupported() const -> bool
        {
            return false;
        }

        virtual auto mark(size_t readAheadLimit) -> void = 0;
        virtual auto reset() -> void = 0;

        [[nodiscard]] virtual auto ready() const -> bool
        {
            return true;
        }

        virtual auto skip(const size_t n) -> size_t
        {
            size_t skipped = 0;
            while (skipped < n)
            {
                std::vector<char> buffer(1024);
                const size_t toRead = std::min(n - skipped, buffer.size());
                const size_t readCount = read(buffer, 0, static_cast<int>(toRead));
                if (readCount == -1) break;
                skipped += readCount;
            }
            return skipped;
        }
    };
}
