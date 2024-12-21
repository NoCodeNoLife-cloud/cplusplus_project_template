#include "ByteArrayInputStream.hpp"

#include <stdexcept>

namespace common
{
    ByteArrayInputStream::ByteArrayInputStream(const std::vector<std::byte>& buf) : buffer_(buf)
    {
    }

    auto ByteArrayInputStream::read() -> std::byte
    {
        if (pos_ >= buffer_.size())
        {
            return static_cast<std::byte>(-1);
        }
        return buffer_[pos_++];
    }

    size_t ByteArrayInputStream::skip(const size_t n)
    {
        const size_t available = buffer_.size() - pos_;
        const size_t bytesToSkip = std::min(n, available);
        pos_ += bytesToSkip;
        return bytesToSkip;
    }

    size_t ByteArrayInputStream::read(std::vector<std::byte>& cBuf, const size_t off, size_t len)
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
        std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), len,
                    cBuf.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += len;
        return len;
    }

    size_t ByteArrayInputStream::available()
    {
        return buffer_.size() - pos_;
    }

    void ByteArrayInputStream::reset()
    {
        pos_ = mark_position_;
    }

    void ByteArrayInputStream::mark(const size_t readAheadLimit)
    {
        mark_position_ = std::min(readAheadLimit, buffer_.size());
    }

    bool ByteArrayInputStream::markSupported() const
    {
        return true;
    }

    auto ByteArrayInputStream::close() -> void
    {
        // do nothing
    }
}
