#pragma once
#include <fstream>
#include <vector>
#include "interface/IfaceCloseable.hpp"

namespace common::io
{
    class AbstractInputStream abstract : public iface::IfaceCloseable
    {
    public:
        ~AbstractInputStream() override = default;
        [[nodiscard]] virtual auto available() -> size_t = 0;

        virtual auto mark(int readLimit) -> void
        {
            throw std::runtime_error("mark not supported");
        }

        [[nodiscard]] virtual auto markSupported() const -> bool
        {
            return false;
        }

        virtual auto read() -> std::byte = 0;

        virtual auto read(std::vector<std::byte>& buffer) -> size_t
        {
            return read(buffer, 0, static_cast<int>(buffer.size()));
        }

        virtual auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t
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

        virtual auto reset() -> void
        {
            throw std::runtime_error("reset not supported");
        }

        virtual auto skip(const size_t n) -> size_t
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
    };
}
