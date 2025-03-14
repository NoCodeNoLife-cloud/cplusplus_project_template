#pragma once
#include <stdexcept>
#include "AbstractReader.hpp"

namespace common::io
{
    class CharArrayReader final : public AbstractReader
    {
    public:
        explicit CharArrayReader(const std::vector<char>& buffer);
        CharArrayReader(const std::vector<char>& buffer, size_t offset, size_t length);
        ~CharArrayReader() override;
        auto read() -> int32_t override;
        auto read(std::vector<char>& b, size_t off, size_t len) -> size_t override;
        auto skip(size_t n) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto mark(size_t readAheadLimit) -> void override;
        auto reset() -> void override;
        auto close() -> void override;
    private:
        std::vector<char> buf_;
        size_t pos_{0};
        size_t markedPos_{0};
        size_t count_{0};
    };

    inline CharArrayReader::CharArrayReader(const std::vector<char>& buffer): buf_(buffer), count_(buffer.size()) {}

    inline CharArrayReader::CharArrayReader(const std::vector<char>& buffer, const size_t offset, const size_t length)
    {
        if (offset > buffer.size() || offset + length > buffer.size())
        {
            throw std::invalid_argument("Invalid offset or length");
        }
        buf_.assign(buffer.begin() + static_cast<std::ptrdiff_t>(offset), buffer.begin() + static_cast<std::ptrdiff_t>(offset + length));
        count_ = length;
    }

    inline CharArrayReader::~CharArrayReader() = default;

    inline int32_t CharArrayReader::read()
    {
        if (pos_ >= count_) return -1;
        return buf_[pos_++];
    }

    inline auto CharArrayReader::read(std::vector<char>& b, const size_t off, const size_t len) -> size_t
    {
        if (pos_ >= count_) return -1;
        if (off >= b.size() || off + len > b.size())
        {
            throw std::out_of_range("Invalid offset or length for target buffer");
        }
        const size_t toRead = std::min(len, count_ - pos_);
        std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead, b.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += toRead;
        return toRead;
    }

    inline size_t CharArrayReader::skip(const size_t n)
    {
        const size_t skipped = std::min(n, count_ - pos_);
        pos_ += skipped;
        return skipped;
    }

    inline bool CharArrayReader::ready() const
    {
        return pos_ < count_;
    }

    inline bool CharArrayReader::markSupported() const
    {
        return true;
    }

    inline auto CharArrayReader::mark(const size_t readAheadLimit) -> void
    {
        markedPos_ = readAheadLimit;
    }

    inline auto CharArrayReader::reset() -> void
    {
        pos_ = markedPos_;
    }

    inline auto CharArrayReader::close() -> void
    {
        buf_.clear();
        pos_ = 0;
        markedPos_ = 0;
        count_ = 0;
    }
}
