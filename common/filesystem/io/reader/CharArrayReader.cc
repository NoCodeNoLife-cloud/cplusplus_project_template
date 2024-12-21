#include "CharArrayReader.hpp"

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

    int32_t CharArrayReader::read()
    {
        if (pos_ >= count_)
            return -1;
        return buf_[pos_++];
    }

    auto CharArrayReader::read(std::vector<char>& b, const size_t off, const size_t len) -> size_t
    {
        if (pos_ >= count_)
            return -1;
        if (off >= b.size() || off + len > b.size())
        {
            throw std::out_of_range("Invalid offset or length for target buffer");
        }
        const size_t toRead = std::min(len, count_ - pos_);
        std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead, b.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += toRead;
        return toRead;
    }

    size_t CharArrayReader::skip(const size_t n)
    {
        const size_t skipped = std::min(n, count_ - pos_);
        pos_ += skipped;
        return skipped;
    }

    bool CharArrayReader::ready() const
    {
        return pos_ < count_;
    }

    bool CharArrayReader::markSupported() const
    {
        return true;
    }

    auto CharArrayReader::mark(const size_t readAheadLimit) -> void
    {
        marked_pos_ = readAheadLimit;
    }

    auto CharArrayReader::reset() -> void
    {
        pos_ = marked_pos_;
    }

    auto CharArrayReader::close() -> void
    {
        buf_.clear();
        pos_ = 0;
        marked_pos_ = 0;
        count_ = 0;
    }
}
