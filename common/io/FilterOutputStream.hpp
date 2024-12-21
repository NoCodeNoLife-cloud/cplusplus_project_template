#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
    class FilterOutputStream : public AbstractOutputStream
    {
    public:
        explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream);
        ~FilterOutputStream() override;
        auto write(std::byte b) -> void override;
        auto write(const std::vector<std::byte>& buffer) -> void override;
        auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;
        auto flush() -> void override;
        auto close() -> void override;
    protected:
        std::shared_ptr<AbstractOutputStream> outputStream_;
    };

    inline FilterOutputStream::FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream): outputStream_(std::move(outputStream)) {}

    inline FilterOutputStream::~FilterOutputStream() = default;

    inline auto FilterOutputStream::write(const std::byte b) -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->write(b);
    }

    inline void FilterOutputStream::write(const std::vector<std::byte>& buffer)
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->write(buffer);
    }

    inline void FilterOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
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

    inline auto FilterOutputStream::flush() -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->flush();
    }

    inline auto FilterOutputStream::close() -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        outputStream_->close();
    }
}
