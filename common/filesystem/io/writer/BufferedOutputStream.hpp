#pragma once
#include <vector>

#include "FilterOutputStream.hpp"


namespace common
{
    class BufferedOutputStream final : public FilterOutputStream
    {
    public:
        explicit BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out);
        BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, size_t size);
        ~BufferedOutputStream() override;
        auto write(std::byte b) -> void override;
        auto write(const std::vector<std::byte>& data, size_t offset, size_t len) -> void override;
        auto flush() -> void override;
        auto close() -> void override;

    protected:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        size_t bufferSize_;
        std::vector<std::byte> buffer_;
        size_t buffer_position_;
        auto flushBuffer() -> void;
    };
}
