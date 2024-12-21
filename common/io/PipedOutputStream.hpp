#pragma once
#include "AbstractOutputStream.hpp"
#include "PipedInputStream.hpp"

namespace common::io
{
    class PipedInputStream;

    class PipedOutputStream final : public AbstractOutputStream
    {
    public:
        explicit PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk)
        {
            if (!snk)
            {
                throw std::invalid_argument("PipedInputStream cannot be null");
            }
            snk_ = snk;
            connected_ = true;
            closed_ = false;
        }

        ~PipedOutputStream() override
        {
            close();
        }

        auto close() -> void override
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

        auto flush() -> void override
        {
            if (closed_ || !connected_ || !snk_)
            {
                throw std::runtime_error("PipedOutputStream is not connected");
            }
            // no-op
        }

        auto write(const std::byte b) -> void override
        {
            if (closed_ || !connected_ || !snk_)
            {
                throw std::runtime_error("PipedOutputStream is not connected");
            }
            snk_->receive(b);
        }

        void write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) override
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

    protected:
        std::shared_ptr<PipedInputStream> snk_;
        bool closed_{true};
        bool connected_{false};
    };
}
