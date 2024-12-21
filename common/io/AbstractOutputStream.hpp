#pragma once
#include <format>
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
    class AbstractOutputStream abstract : public iface::IfaceCloseable, public iface::IfaceFlushable
    {
    public:
        ~AbstractOutputStream() override = default;
        virtual auto write(std::byte b) -> void = 0;

        virtual auto write(const std::vector<std::byte>& buffer) -> void
        {
            write(buffer, 0, static_cast<int>(buffer.size()));
        }

        virtual auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
        {
            if (offset + len > buffer.size())
            {
                throw std::out_of_range("Buffer offset/length out of range");
            }
            for (int i = 0; i < len; ++i)
            {
                write(buffer[offset + i]);
            }
        }
    };
}
