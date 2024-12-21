#pragma once
#include "FilterInputStream.hpp"

namespace common::io
{
    class PushbackInputStream final : public FilterInputStream
    {
    public:
        PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, size_t bufferSize);
        ~PushbackInputStream() override;
        auto available() -> size_t override;
        auto read() -> std::byte override;
        auto read(std::vector<std::byte>& buffer) -> size_t override;
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
        void unread(const std::vector<std::byte>& buffer);
        void unread(const std::vector<std::byte>& buffer, size_t offset, size_t len);
        void unread(std::byte b);
    private:
        std::vector<std::byte> pushbackBuffer_;
        size_t bufferPos_{0};
    };
}
