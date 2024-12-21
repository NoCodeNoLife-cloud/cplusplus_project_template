#include "PushbackInputStream.hpp"

#include <stdexcept>

namespace common::io
{
    PushbackInputStream::PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, const size_t bufferSize): FilterInputStream(std::move(inputStream)), pushbackBuffer_(bufferSize), bufferPos_(bufferSize) {}

    PushbackInputStream::~PushbackInputStream() = default;

    size_t PushbackInputStream::available()
    {
        return pushbackBuffer_.size() - bufferPos_ + inputStream_->available();
    }

    std::byte PushbackInputStream::read()
    {
        if (bufferPos_ < pushbackBuffer_.size())
        {
            return pushbackBuffer_[bufferPos_++];
        }
        return inputStream_->read();
    }

    size_t PushbackInputStream::read(std::vector<std::byte>& buffer)
    {
        return read(buffer, 0, buffer.size());
    }

    size_t PushbackInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        size_t bytesRead = 0;
        while (bytesRead < len && bufferPos_ < pushbackBuffer_.size())
        {
            buffer[offset + bytesRead++] = pushbackBuffer_[bufferPos_++];
        }
        if (bytesRead < len)
        {
            bytesRead += inputStream_->read(buffer, offset + bytesRead, len - bytesRead);
        }
        return bytesRead;
    }

    void PushbackInputStream::unread(const std::vector<std::byte>& buffer)
    {
        unread(buffer, 0, buffer.size());
    }

    void PushbackInputStream::unread(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (len > bufferPos_)
        {
            throw std::overflow_error("Pushback buffer overflow");
        }
        for (size_t i = 0; i < len; ++i)
        {
            pushbackBuffer_[--bufferPos_] = buffer[offset + len - i - 1];
        }
    }

    void PushbackInputStream::unread(const std::byte b)
    {
        if (bufferPos_ == 0)
        {
            throw std::overflow_error("Pushback buffer overflow");
        }
        pushbackBuffer_[--bufferPos_] = b;
    }
}
