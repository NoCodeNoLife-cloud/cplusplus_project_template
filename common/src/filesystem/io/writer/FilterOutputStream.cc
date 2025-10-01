#include "src/filesystem/io/writer/FilterOutputStream.hpp"

namespace fox
{
    FilterOutputStream::FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream)
        : output_stream_(std::move(outputStream))
    {
    }

    auto FilterOutputStream::write(const std::byte b) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->write(b);
    }

    auto FilterOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->write(buffer);
    }

    auto FilterOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        output_stream_->write(buffer, offset, len);
    }

    auto FilterOutputStream::write(const std::byte* buffer, const size_t length) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (!buffer)
        {
            throw std::invalid_argument("Buffer cannot be null");
        }
        output_stream_->write(buffer, length);
    }

    auto FilterOutputStream::flush() -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->flush();
    }

    auto FilterOutputStream::close() -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        output_stream_->close();
    }

    auto FilterOutputStream::isClosed() const -> bool
    {
        // A filter stream is considered closed if the underlying stream is not available
        // or if the underlying stream reports being closed
        return !output_stream_ || output_stream_->isClosed();
    }
}
