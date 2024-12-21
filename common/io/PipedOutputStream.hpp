#pragma once
#include "AbstractOutputStream.hpp"
#include "PipedInputStream.hpp"

namespace common::io
{
    class PipedInputStream;

    class PipedOutputStream final : public AbstractOutputStream
    {
    public:
        explicit PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk);
        ~PipedOutputStream() override;
        auto close() -> void override;
        auto flush() -> void override;
        auto write(std::byte b) -> void override;
        void write(const std::vector<std::byte>& buffer, size_t offset, size_t len) override;
    protected:
        std::shared_ptr<PipedInputStream> snk_;
        bool closed_{true};
        bool connected_{false};
    };

    inline PipedOutputStream::PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk)
    {
        if (!snk)
        {
            throw std::invalid_argument("PipedInputStream cannot be null");
        }
        snk_ = snk;
        connected_ = true;
        closed_ = false;
    }

    inline PipedOutputStream::~PipedOutputStream()
    {
        close();
    }

    inline auto PipedOutputStream::close() -> void
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

    inline auto PipedOutputStream::flush() -> void
    {
        if (closed_ || !connected_ || !snk_)
        {
            throw std::runtime_error("PipedOutputStream is not connected");
        }
        // no-op
    }

    inline auto PipedOutputStream::write(const std::byte b) -> void
    {
        if (closed_ || !connected_ || !snk_)
        {
            throw std::runtime_error("PipedOutputStream is not connected");
        }
        snk_->receive(b);
    }

    inline void PipedOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
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
