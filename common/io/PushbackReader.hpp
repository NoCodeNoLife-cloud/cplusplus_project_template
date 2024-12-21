#pragma once
#include <stdexcept>
#include "FilterReader.hpp"

namespace common::io
{
    class PushbackReader final : public FilterReader
    {
    public:
        explicit PushbackReader(std::shared_ptr<AbstractReader> reader) : PushbackReader(
            std::move(reader), DEFAULT_BUFFER_SIZE)
        {
        }

        PushbackReader(std::shared_ptr<AbstractReader> reader, const size_t size) : FilterReader(std::move(reader)),
                                                                                    buffer_(size)
        {
            if (size == 0)
            {
                throw std::invalid_argument("Buffer size must be greater than zero.");
            }
        }

        auto close() -> void override
        {
            FilterReader::close();
            buffer_.clear();
        }

        auto mark(size_t readAheadLimit) -> void override
        {
            throw std::runtime_error("mark() not supported.");
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return false;
        }

        auto read() -> int override
        {
            if (bufferPos_ < buffer_.size())
            {
                return buffer_[bufferPos_++];
            }
            return FilterReader::read();
        }

        auto read(std::vector<char>& cBuf, size_t off, const size_t len) -> size_t override
        {
            if (off + len > cBuf.size())
            {
                throw std::out_of_range("Buffer overflow.");
            }
            size_t bytesRead = 0;
            while (bufferPos_ < buffer_.size() && bytesRead < len)
            {
                cBuf[off++] = buffer_[bufferPos_++];
                bytesRead++;
            }
            if (bytesRead < len)
            {
                bytesRead += FilterReader::read(cBuf, off, len - bytesRead);
            }
            return bytesRead;
        }

        [[nodiscard]] auto ready() const -> bool override
        {
            return bufferPos_ < buffer_.size() || FilterReader::ready();
        }

        auto reset() -> void override
        {
            throw std::runtime_error("reset() not supported.");
        }

        auto skip(size_t n) -> size_t override
        {
            size_t skipped = 0;
            if (bufferPos_ < buffer_.size())
            {
                const size_t bufferRemaining = buffer_.size() - bufferPos_;
                skipped = std::min(n, bufferRemaining);
                bufferPos_ += skipped;
                n -= skipped;
            }
            if (n > 0)
            {
                skipped += FilterReader::skip(n);
            }
            return skipped;
        }

        auto unread(const std::vector<char>& cBuf) -> void
        {
            unread(cBuf, 0, cBuf.size());
        }

        auto unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
        {
            if (len > bufferPos_)
            {
                throw std::overflow_error("Pushback buffer overflow.");
            }
            for (size_t i = 0; i < len; ++i)
            {
                buffer_[--bufferPos_] = cBuf[off + len - 1 - i];
            }
        }

        auto unread(const int c) -> void
        {
            if (bufferPos_ == 0)
            {
                throw std::overflow_error("Pushback buffer overflow.");
            }
            buffer_[--bufferPos_] = static_cast<char>(c);
        }

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::vector<char> buffer_;
        size_t bufferPos_{DEFAULT_BUFFER_SIZE};
    };
}
