#include "src/filesystem/io/reader/FilterInputStream.hpp"

#include <cstddef>
#include <stdexcept>

namespace common
{
    FilterInputStream::FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream) noexcept
        : input_stream_(std::move(inputStream))
    {
    }

    auto FilterInputStream::available() -> size_t
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::available: Input stream is not available");
        }
        return input_stream_->available();
    }

    auto FilterInputStream::mark(const int32_t readLimit) -> void
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::mark: Input stream is not available");
        }
        input_stream_->mark(readLimit);
    }

    auto FilterInputStream::markSupported() const -> bool
    {
        if (!input_stream_)
        {
            return false;
        }
        return input_stream_->markSupported();
    }

    auto FilterInputStream::read() -> std::byte
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::read: Input stream is not available");
        }
        return input_stream_->read();
    }

    auto FilterInputStream::read(std::vector<std::byte>& buffer) -> size_t
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::read: Input stream is not available");
        }
        return input_stream_->read(buffer);
    }

    auto FilterInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::read: Input stream is not available");
        }
        return input_stream_->read(buffer, offset, len);
    }

    auto FilterInputStream::reset() -> void
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::reset: Input stream is not available");
        }
        input_stream_->reset();
    }

    auto FilterInputStream::skip(const size_t n) -> size_t
    {
        if (!input_stream_)
        {
            throw std::runtime_error("FilterInputStream::skip: Input stream is not available");
        }
        return input_stream_->skip(n);
    }

    auto FilterInputStream::close() -> void
    {
        if (input_stream_)
        {
            input_stream_->close();
        }
    }

    auto FilterInputStream::isClosed() const -> bool
    {
        if (!input_stream_)
        {
            return true;
        }
        return input_stream_->isClosed();
    }
}
