#pragma once
#include <stdexcept>
#include "FilterReader.hpp"

namespace common::io
{
    class PushbackReader final : public FilterReader
    {
    public:
        explicit PushbackReader(std::shared_ptr<AbstractReader> reader);
        PushbackReader(std::shared_ptr<AbstractReader> reader, size_t size);
        auto close() -> void override;
        auto mark(size_t readAheadLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> int32_t override;
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        auto reset() -> void override;
        auto skip(size_t n) -> size_t override;
        auto unread(const std::vector<char>& cBuf) -> void;
        auto unread(const std::vector<char>& cBuf, size_t off, size_t len) -> void;
        auto unread(int32_t c) -> void;
    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::vector<char> buffer_;
        size_t bufferPos_{DEFAULT_BUFFER_SIZE};
    };

    inline PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader): PushbackReader(std::move(reader), DEFAULT_BUFFER_SIZE) {}

    inline PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader, const size_t size): FilterReader(std::move(reader)), buffer_(size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than zero.");
        }
    }

    inline void PushbackReader::close()
    {
        FilterReader::close();
        buffer_.clear();
    }

    inline void PushbackReader::mark(size_t readAheadLimit)
    {
        throw std::runtime_error("mark() not supported.");
    }

    inline bool PushbackReader::markSupported() const
    {
        return false;
    }

    inline int32_t PushbackReader::read()
    {
        if (bufferPos_ < buffer_.size())
        {
            return buffer_[bufferPos_++];
        }
        return FilterReader::read();
    }

    inline size_t PushbackReader::read(std::vector<char>& cBuf, size_t off, const size_t len)
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

    inline bool PushbackReader::ready() const
    {
        return bufferPos_ < buffer_.size() || FilterReader::ready();
    }

    inline void PushbackReader::reset()
    {
        throw std::runtime_error("reset() not supported.");
    }

    inline size_t PushbackReader::skip(size_t n)
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

    inline auto PushbackReader::unread(const std::vector<char>& cBuf) -> void
    {
        unread(cBuf, 0, cBuf.size());
    }

    inline auto PushbackReader::unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
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

    inline auto PushbackReader::unread(const int32_t c) -> void
    {
        if (bufferPos_ == 0)
        {
            throw std::overflow_error("Pushback buffer overflow.");
        }
        buffer_[--bufferPos_] = static_cast<char>(c);
    }
}
