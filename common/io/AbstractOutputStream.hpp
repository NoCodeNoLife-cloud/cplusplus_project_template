#pragma once
#include <format>
#include <vector>
#include "interface/ICloseable.hpp"
#include "interface/IFlushable.hpp"

namespace common::io
{
    class AbstractOutputStream abstract : public iface::ICloseable, public iface::IFlushable
    {
    public:
        ~AbstractOutputStream() override;
        virtual auto write(std::byte b) -> void = 0;
        virtual auto write(const std::vector<std::byte>& buffer) -> void;
        virtual auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void;
    };

    inline AbstractOutputStream::~AbstractOutputStream() = default;

    inline auto AbstractOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        write(buffer, 0, static_cast<int32_t>(buffer.size()));
    }

    inline auto AbstractOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
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
