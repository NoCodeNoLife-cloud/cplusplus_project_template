#include "src/filesystem/io/reader/CharArrayReader.hpp"

#include <algorithm>
#include <stdexcept>

namespace common
{
    CharArrayReader::CharArrayReader(const std::vector<char>& buffer) : buf_(buffer), count_(buffer.size())
    {
    }

    CharArrayReader::CharArrayReader(const std::vector<char>& buffer, const size_t offset, const size_t length)
    {
        if (offset > buffer.size() || offset + length > buffer.size())
        {
            throw std::invalid_argument("Invalid offset or length");
        }
        buf_.assign(buffer.begin() + static_cast<std::ptrdiff_t>(offset),
                    buffer.begin() + static_cast<std::ptrdiff_t>(offset + length));
        count_ = length;
    }

    CharArrayReader::~CharArrayReader() = default;

    auto CharArrayReader::read() -> int
    {
        if (closed_ || pos_ >= count_)
            return -1;
        return static_cast<unsigned char>(buf_[pos_++]);
    }

    auto CharArrayReader::read(std::vector<char>& b, const size_t off, const size_t len) -> int
    {
        if (off > b.size() || len > b.size() - off)
        {
            throw std::out_of_range("Invalid offset or length for target buffer");
        }

        if (closed_ || pos_ >= count_)
            return -1;

        const size_t toRead = std::min(len, count_ - pos_);
        std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead,
                    b.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += toRead;
        return static_cast<int>(toRead);
    }

    auto CharArrayReader::skip(const size_t n) -> size_t
    {
        if (closed_)
            return 0;

        const size_t skipped = std::min(n, count_ - pos_);
        pos_ += skipped;
        return skipped;
    }

    auto CharArrayReader::ready() const -> bool
    {
        return !closed_ && pos_ < count_;
    }

    auto CharArrayReader::markSupported() const -> bool
    {
        return true;
    }

    auto CharArrayReader::mark(const size_t readAheadLimit) -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }
        marked_pos_ = pos_;
    }

    auto CharArrayReader::reset() -> void
    {
        if (closed_)
        {
            throw std::runtime_error("Stream is closed");
        }
        pos_ = marked_pos_;
    }

    auto CharArrayReader::close() -> void
    {
        closed_ = true;
        buf_.clear();
        pos_ = 0;
        marked_pos_ = 0;
        count_ = 0;
    }

    auto CharArrayReader::isClosed() const -> bool
    {
        return closed_;
    }
}
