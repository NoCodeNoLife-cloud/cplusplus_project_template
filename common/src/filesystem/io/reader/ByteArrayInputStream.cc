#include "src/filesystem/io/reader/ByteArrayInputStream.hpp"

#include <stdexcept>

namespace common
{
    ByteArrayInputStream::ByteArrayInputStream(const std::vector<std::byte>& buf) : buffer_(buf)
    {
    }

    auto ByteArrayInputStream::read() -> std::byte
    {
        if (closed_ || pos_ >= buffer_.size())
        {
            return static_cast<std::byte>(-1);
        }
        return buffer_[pos_++];
    }

    auto ByteArrayInputStream::read(std::vector<std::byte>& cBuf, const size_t off, const size_t len) -> size_t
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Offset and length exceed the size of the buffer");
        }

        if (closed_ || pos_ >= buffer_.size())
        {
            return 0;
        }

        const size_t remaining = buffer_.size() - pos_;
        const size_t bytesToRead = std::min(len, remaining);

        std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), bytesToRead,
                    cBuf.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += bytesToRead;
        return bytesToRead;
    }

    auto ByteArrayInputStream::skip(const size_t n) -> size_t
    {
        if (closed_)
        {
            return 0;
        }

        const size_t available = buffer_.size() - pos_;
        const size_t bytesToSkip = std::min(n, available);
        pos_ += bytesToSkip;
        return bytesToSkip;
    }

    auto ByteArrayInputStream::available() -> size_t
    {
        if (closed_)
        {
            return 0;
        }
        return buffer_.size() - pos_;
    }

    auto ByteArrayInputStream::reset() -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }
        pos_ = mark_position_;
    }

    auto ByteArrayInputStream::mark(const int32_t readLimit) -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }
        mark_position_ = pos_;
    }

    auto ByteArrayInputStream::markSupported() const -> bool
    {
        return true;
    }

    auto ByteArrayInputStream::close() -> void
    {
        closed_ = true;
    }

    auto ByteArrayInputStream::isClosed() const -> bool
    {
        return closed_;
    }
}
