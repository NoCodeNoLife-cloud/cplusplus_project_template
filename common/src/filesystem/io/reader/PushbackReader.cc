#include "src/filesystem/io/reader/PushbackReader.hpp"

#include <stdexcept>

namespace common
{
    PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader)
        : PushbackReader(std::move(reader), DEFAULT_BUFFER_SIZE)
    {
    }

    PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader, const size_t size)
        : FilterReader(std::move(reader)), buffer_(size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than zero.");
        }
    }

    auto PushbackReader::close() -> void
    {
        closed_ = true;
        FilterReader::close();
        buffer_.clear();
    }

    auto PushbackReader::mark(const size_t readAheadLimit) -> void
    {
        static_cast<void>(readAheadLimit); // Unused parameter
        throw std::runtime_error("mark() not supported.");
    }

    auto PushbackReader::markSupported() const -> bool
    {
        return false;
    }

    auto PushbackReader::read() -> int
    {
        if (closed_ || !in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        if (buffer_pos_ < buffer_.size())
        {
            return static_cast<unsigned char>(buffer_[buffer_pos_++]);
        }
        return FilterReader::read();
    }

    auto PushbackReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> int
    {
        if (closed_ || !in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer overflow.");
        }

        size_t bytesRead = 0;
        while (buffer_pos_ < buffer_.size() && bytesRead < len)
        {
            cBuf[off + bytesRead] = buffer_[buffer_pos_++];
            bytesRead++;
        }
        if (bytesRead < len)
        {
            const int underlyingBytesRead = FilterReader::read(cBuf, off + bytesRead, len - bytesRead);
            if (underlyingBytesRead == -1)
            {
                return bytesRead > 0 ? static_cast<int>(bytesRead) : -1;
            }
            bytesRead += static_cast<size_t>(underlyingBytesRead);
        }
        return static_cast<int>(bytesRead);
    }

    auto PushbackReader::ready() const -> bool
    {
        if (closed_ || !in_)
        {
            return false;
        }
        return buffer_pos_ < buffer_.size() || FilterReader::ready();
    }

    auto PushbackReader::reset() -> void
    {
        throw std::runtime_error("reset() not supported.");
    }

    auto PushbackReader::skip(const size_t n) -> size_t
    {
        if (closed_ || !in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        size_t skipped = 0;
        if (buffer_pos_ < buffer_.size())
        {
            const size_t bufferRemaining = buffer_.size() - buffer_pos_;
            skipped = std::min(n, bufferRemaining);
            buffer_pos_ += skipped;
        }
        if (n > skipped)
        {
            skipped += FilterReader::skip(n - skipped);
        }
        return skipped;
    }

    auto PushbackReader::unread(const std::vector<char>& cbuf) -> void
    {
        unread(cbuf, 0, cbuf.size());
    }

    auto PushbackReader::unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        if (len > buffer_pos_)
        {
            throw std::overflow_error("Pushback buffer overflow.");
        }

        for (size_t i = 0; i < len; ++i)
        {
            buffer_[--buffer_pos_] = cBuf[off + len - 1 - i];
        }
    }

    auto PushbackReader::unread(const int32_t c) -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }

        if (buffer_pos_ == 0)
        {
            throw std::overflow_error("Pushback buffer overflow.");
        }
        buffer_[--buffer_pos_] = static_cast<char>(c);
    }

    auto PushbackReader::isClosed() const -> bool
    {
        return closed_ || !in_ || in_->isClosed();
    }
}
