#include "src/filesystem/io/reader/AbstractInputStream.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace fox
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
        return read(buffer, 0, buffer.size());
    }

    auto AbstractInputStream::read(std::vector<std::byte>& buffer, const size_t offset,
                                   const size_t len) -> size_t
    {
        // Check for buffer overflow
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        size_t bytesRead = 0;
        for (size_t i = 0; i < len; ++i)
        {
            const std::byte byte = read();
            // Check for end of stream
            if (static_cast<int>(byte) == -1)
            {
                break;
            }
            buffer[offset + i] = byte;
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
        // Prevent potential overflow
        const size_t maxSkip = std::min(n, static_cast<size_t>(std::numeric_limits<int>::max()));

        for (size_t i = 0; i < maxSkip; ++i)
        {
            if (static_cast<int>(read()) == -1)
            {
                break;
            }
            ++skipped;
        }
        return skipped;
    }
}
