#include "AbstractOutputStream.hpp"

namespace common
{
    AbstractOutputStream::~AbstractOutputStream() = default;

    auto AbstractOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        write(buffer, 0, static_cast<int32_t>(buffer.size()));
    }

    auto AbstractOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
        -> void
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }
        for (int32_t i = 0; i < len; ++i)
        {
            write(buffer[offset + i]);
        }
    }
}
