#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
    class FilterOutputStream : public AbstractOutputStream
    {
    public:
        explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream): outputStream_(
            std::move(outputStream))
        {
        }

        ~FilterOutputStream() override = default;

        auto write(const std::byte b) -> void override
        {
            if (!outputStream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputStream_->write(b);
        }

        auto write(const std::vector<std::byte>& buffer) -> void override
        {
            if (!outputStream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputStream_->write(buffer);
        }

        auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void override
        {
            if (!outputStream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            if (offset + len > buffer.size())
            {
                throw std::out_of_range("Buffer overflow");
            }
            outputStream_->write(buffer, offset, len);
        }

        auto flush() -> void override
        {
            if (!outputStream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputStream_->flush();
        }

        auto close() -> void override
        {
            if (!outputStream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            flush();
            outputStream_->close();
        }

    protected:
        std::shared_ptr<AbstractOutputStream> outputStream_;
    };
}
