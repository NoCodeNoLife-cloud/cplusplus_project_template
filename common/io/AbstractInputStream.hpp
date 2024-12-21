#pragma once
#include <fstream>
#include <vector>
#include "interface/ICloseable.hpp"

namespace common::io
{
    class AbstractInputStream abstract : public iface::ICloseable
    {
    public:
        ~AbstractInputStream() override;
        [[nodiscard]] virtual auto available() -> size_t = 0;
        virtual auto mark(int readLimit) -> void;
        [[nodiscard]] virtual auto markSupported() const -> bool;
        virtual auto read() -> std::byte = 0;
        virtual auto read(std::vector<std::byte>& buffer) -> size_t;
        virtual auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t;
        virtual auto reset() -> void;
        virtual auto skip(size_t n) -> size_t;
    };

    inline AbstractInputStream::~AbstractInputStream() = default;

    inline auto AbstractInputStream::mark(int readLimit) -> void
    {
        throw std::runtime_error("mark not supported");
    }

    inline auto AbstractInputStream::markSupported() const -> bool
    {
        return false;
    }

    inline auto AbstractInputStream::read(std::vector<std::byte>& buffer) -> size_t
    {
        return read(buffer, 0, static_cast<int>(buffer.size()));
    }

    inline auto AbstractInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }
        size_t bytesRead = 0;
        for (int i = 0; i < len; ++i)
        {
            const std::byte byte = read();
            if (byte == static_cast<std::byte>(-1))
            {
                break;
            }
            buffer[offset + i] = static_cast<std::byte>(byte);
            ++bytesRead;
        }
        return bytesRead;
    }

    inline auto AbstractInputStream::reset() -> void
    {
        throw std::runtime_error("reset not supported");
    }

    inline auto AbstractInputStream::skip(const size_t n) -> size_t
    {
        size_t skipped = 0;
        for (size_t i = 0; i < n; ++i)
        {
            if (read() == static_cast<std::byte>(-1))
            {
                break;
            }
            ++skipped;
        }
        return skipped;
    }
}
