#include "PipedInputStream.hpp"

namespace common::io
{
    PipedInputStream::PipedInputStream(): PipedInputStream(PIPE_SIZE) {}

    PipedInputStream::PipedInputStream(const size_t pipeSize): buffer_(pipeSize) {}

    PipedInputStream::PipedInputStream(const std::shared_ptr<PipedOutputStream>& src): PipedInputStream(src, PIPE_SIZE) {}

    PipedInputStream::PipedInputStream(const std::shared_ptr<PipedOutputStream>& src, const size_t pipeSize): PipedInputStream(pipeSize)
    {
        connect(src);
    }

    PipedInputStream::~PipedInputStream()
    {
        close();
    }

    auto PipedInputStream::close() -> void
    {
        std::lock_guard lock(mutex_);
        buffer_.clear();
        in_ = out_ = 0;
    }

    auto PipedInputStream::available() -> size_t
    {
        std::lock_guard lock(mutex_);
        return (in_ + buffer_.size() - out_) % buffer_.size();
    }

    auto PipedInputStream::read() -> std::byte
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

    size_t PipedInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
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

    auto PipedInputStream::connect(std::shared_ptr<PipedOutputStream> src) -> void
    {
        std::lock_guard lock(mutex_);
        if (src_)
        {
            throw std::runtime_error("PipedInputStream is already connected");
        }
        src_ = std::move(src);
    }

    auto PipedInputStream::receive(const std::byte b) -> void
    {
        std::lock_guard lock(mutex_);
        if ((in_ + 1) % buffer_.size() == out_)
        {
            throw std::runtime_error("PipedInputStream is overflow");
        }
        buffer_[in_] = b;
        in_ = (in_ + 1) % buffer_.size();
    }
}
