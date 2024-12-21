#pragma once
#include <mutex>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
    class PipedOutputStream;

    class PipedInputStream final : public AbstractInputStream
    {
    public:
        PipedInputStream();
        explicit PipedInputStream(size_t pipeSize);
        explicit PipedInputStream(const std::shared_ptr<PipedOutputStream>& src);
        PipedInputStream(const std::shared_ptr<PipedOutputStream>& src, size_t pipeSize);
        ~PipedInputStream() override;
        auto close() -> void override;
        auto available() -> size_t override;
        auto read() -> std::byte override;
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
        auto connect(std::shared_ptr<PipedOutputStream> src) -> void;
        auto receive(std::byte b) -> void;
    protected:
        std::vector<std::byte> buffer_{};
        size_t in_{0};
        size_t out_{0};
        static constexpr size_t PIPE_SIZE = 1024;
        std::mutex mutex_;
        std::shared_ptr<PipedOutputStream> src_;
    };
}
