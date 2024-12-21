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
        PipedInputStream(): PipedInputStream(PIPE_SIZE)
        {
        }

        explicit PipedInputStream(const size_t pipeSize): buffer_(pipeSize)
        {
        }

        explicit PipedInputStream(const std::shared_ptr<PipedOutputStream>& src) : PipedInputStream(src, PIPE_SIZE)
        {
        }

        PipedInputStream(const std::shared_ptr<PipedOutputStream>& src, const size_t pipeSize): PipedInputStream(
            pipeSize)
        {
            connect(src);
        }

        ~PipedInputStream() override
        {
            close();
        }

        auto close() -> void override
        {
            std::lock_guard lock(mutex_);
            buffer_.clear();
            in_ = out_ = 0;
        }

        auto available() -> size_t override
        {
            std::lock_guard lock(mutex_);
            return (in_ + buffer_.size() - out_) % buffer_.size();
        }

        auto read() -> std::byte override
        {
            std::lock_guard lock(mutex_);
            if (in_ == out_)
            {
                throw std::runtime_error("PipedInputStream is empty");
            }
            const auto result = buffer_[out_];
            out_ = (out_ + 1) % buffer_.size();
            return result;
        }

        size_t read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) override
        {
            std::lock_guard lock(mutex_);
            size_t bytesRead{0};
            while (bytesRead < len && out_ != in_)
            {
                buffer_[offset + bytesRead] = buffer_[out_];
                ++bytesRead;
                out_ = (out_ + 1) % buffer_.size();
            }
            return bytesRead;
        }

        auto connect(std::shared_ptr<PipedOutputStream> src) -> void
        {
            std::lock_guard lock(mutex_);
            if (src_)
            {
                throw std::runtime_error("PipedInputStream is already connected");
            }
            src_ = std::move(src);
        }

        auto receive(const std::byte b) -> void
        {
            std::lock_guard lock(mutex_);
            if ((in_ + 1) % buffer_.size() == out_)
            {
                throw std::runtime_error("PipedInputStream is overflow");
            }
            buffer_[in_] = b;
            in_ = (in_ + 1) % buffer_.size();
        }

    protected:
        std::vector<std::byte> buffer_{};
        size_t in_{0};
        size_t out_{0};
        static constexpr size_t PIPE_SIZE = 1024;
        std::mutex mutex_;
        std::shared_ptr<PipedOutputStream> src_;
    };
}
