#pragma once
#include <vector>
#include "interface/ICloseable.hpp"
#include "interface/IReadable.hpp"

namespace common::io
{
    class AbstractReader abstract : public iface::ICloseable, public iface::IReadable
    {
    public:
        ~AbstractReader() override;
        auto read() -> int32_t override;
        virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;
        virtual auto read(std::vector<char>& cBuf) -> size_t;
        [[nodiscard]] virtual auto markSupported() const -> bool;
        virtual auto mark(size_t readAheadLimit) -> void = 0;
        virtual auto reset() -> void = 0;
        [[nodiscard]] virtual auto ready() const -> bool;
        virtual auto skip(size_t n) -> size_t;
    };

    inline AbstractReader::~AbstractReader() = default;

    inline auto AbstractReader::read() -> int32_t
    {
        std::vector<char> buffer(1);
        if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1)
        {
            return -1;
        }
        return buffer[0];
    }

    inline auto AbstractReader::read(std::vector<char>& cBuf) -> size_t
    {
        return read(cBuf, 0, static_cast<int32_t>(cBuf.size()));
    }

    inline auto AbstractReader::markSupported() const -> bool
    {
        return false;
    }

    inline auto AbstractReader::ready() const -> bool
    {
        return true;
    }

    inline auto AbstractReader::skip(const size_t n) -> size_t
    {
        size_t skipped = 0;
        while (skipped < n)
        {
            std::vector<char> buffer(1024);
            const size_t toRead = std::min(n - skipped, buffer.size());
            const size_t readCount = read(buffer, 0, static_cast<int32_t>(toRead));
            if (readCount == -1) break;
            skipped += readCount;
        }
        return skipped;
    }
}
