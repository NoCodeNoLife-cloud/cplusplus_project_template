#include "FilterInputStream.hpp"

#include <memory>
#include <stdexcept>

namespace common::io
{
    FilterInputStream::FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream): inputStream_(std::move(inputStream)) {}

    FilterInputStream::~FilterInputStream() = default;

    auto FilterInputStream::available() -> size_t
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->available();
    }

    void FilterInputStream::mark(const int32_t readLimit)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        inputStream_->mark(readLimit);
    }

    bool FilterInputStream::markSupported() const
    {
        if (!inputStream_)
        {
            return false;
        }
        return inputStream_->markSupported();
    }

    auto FilterInputStream::read() -> std::byte
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read();
    }

    size_t FilterInputStream::read(std::vector<std::byte>& buffer)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read(buffer);
    }

    size_t FilterInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read(buffer, offset, len);
    }

    void FilterInputStream::reset()
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        inputStream_->reset();
    }

    size_t FilterInputStream::skip(const size_t n)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->skip(n);
    }

    auto FilterInputStream::close() -> void
    {
        inputStream_->close();
    }
}
