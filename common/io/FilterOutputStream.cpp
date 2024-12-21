#include "FilterOutputStream.hpp"

namespace common::io
{
    FilterOutputStream::FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream): outputStream_(std::move(outputStream)) {}

    FilterOutputStream::~FilterOutputStream() = default;

    auto FilterOutputStream::write(const std::byte b) -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->write(b);
    }

    void FilterOutputStream::write(const std::vector<std::byte>& buffer)
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->write(buffer);
    }

    void FilterOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
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

    auto FilterOutputStream::flush() -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputStream_->flush();
    }

    auto FilterOutputStream::close() -> void
    {
        if (!outputStream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        outputStream_->close();
    }
}
