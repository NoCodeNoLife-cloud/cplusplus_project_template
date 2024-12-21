#include "AbstractInputStream.hpp"

#include <fstream>

namespace common
{
    AbstractInputStream::~AbstractInputStream() = default;

    auto AbstractInputStream::mark(int32_t readLimit) -> void
    {
        throw std::runtime_error("mark not supported");
    }

    auto AbstractInputStream::markSupported() const -> bool
    {
        return false;
    }

    auto AbstractInputStream::read(std::vector<std::byte>& buffer) -> size_t
    {
        return read(buffer, 0, static_cast<int32_t>(buffer.size()));
    }

    auto AbstractInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }
        size_t bytesRead = 0;
        for (int32_t i = 0; i < len; ++i)
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

    auto AbstractInputStream::reset() -> void
    {
        throw std::runtime_error("reset not supported");
    }

    auto AbstractInputStream::skip(const size_t n) -> size_t
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
