#pragma once
#include <stdexcept>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
    class ByteArrayInputStream final : public AbstractInputStream
    {
    public:
        explicit ByteArrayInputStream(const std::vector<std::byte>& buf);
        auto read() -> std::byte override;
        auto skip(size_t n) -> size_t override;
        auto read(std::vector<std::byte>& cBuf, size_t off, size_t len) -> size_t override;
        size_t available() override;
        void reset() override;
        void mark(size_t readAheadLimit);
        [[nodiscard]] auto markSupported() const -> bool override;
        auto close() -> void override;
    protected:
        const std::vector<std::byte> buffer_;
        size_t pos_{0};
        size_t markPosition_{0};
    };

    inline ByteArrayInputStream::ByteArrayInputStream(const std::vector<std::byte>& buf): buffer_(buf) {}

    inline auto ByteArrayInputStream::read() -> std::byte
    {
        if (pos_ >= buffer_.size())
        {
            return static_cast<std::byte>(-1);
        }
        return buffer_[pos_++];
    }

    inline size_t ByteArrayInputStream::skip(const size_t n)
    {
        const size_t available = buffer_.size() - pos_;
        const size_t bytesToSkip = std::min(n, available);
        pos_ += bytesToSkip;
        return bytesToSkip;
    }

    inline size_t ByteArrayInputStream::read(std::vector<std::byte>& cBuf, const size_t off, size_t len)
    {
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Offset and length exceed the size of the buffer");
        }
        if (const size_t remaining = buffer_.size() - pos_; len > remaining)
        {
            len = remaining;
        }
        if (pos_ >= buffer_.size())
        {
            return 0;
        }
        std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), len, cBuf.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += len;
        return len;
    }

    inline size_t ByteArrayInputStream::available()
    {
        return buffer_.size() - pos_;
    }

    inline void ByteArrayInputStream::reset()
    {
        pos_ = markPosition_;
    }

    inline void ByteArrayInputStream::mark(const size_t readAheadLimit)
    {
        markPosition_ = std::min(readAheadLimit, buffer_.size());
    }

    inline bool ByteArrayInputStream::markSupported() const
    {
        return true;
    }

    inline auto ByteArrayInputStream::close() -> void
    {
        // do nothing
    }
}
