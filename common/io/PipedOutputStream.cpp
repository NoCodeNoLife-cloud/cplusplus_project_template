#include "PipedOutputStream.hpp"

namespace common::io
{
    PipedOutputStream::PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk)
    {
        if (!snk)
        {
            throw std::invalid_argument("PipedInputStream cannot be null");
        }
        snk_ = snk;
        connected_ = true;
        closed_ = false;
    }

    PipedOutputStream::~PipedOutputStream()
    {
        close();
    }

    auto PipedOutputStream::close() -> void
    {
        if (closed_)
        {
            return;
        }
        flush();
        connected_ = false;
        closed_ = true;
        if (snk_)
        {
            snk_->close();
        }
    }

    auto PipedOutputStream::flush() -> void
    {
        if (closed_ || !connected_ || !snk_)
        {
            throw std::runtime_error("PipedOutputStream is not connected");
        }
        // no-op
    }

    auto PipedOutputStream::write(const std::byte b) -> void
    {
        if (closed_ || !connected_ || !snk_)
        {
            throw std::runtime_error("PipedOutputStream is not connected");
        }
        snk_->receive(b);
    }

    auto PipedOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
    {
        if (closed_ || !connected_ || !snk_)
        {
            throw std::runtime_error("PipedOutputStream is not connected");
        }
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        for (size_t i = 0; i < len; ++i)
        {
            snk_->receive(buffer[offset + i]);
        }
    }
}
