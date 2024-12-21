#pragma once
#include <stdexcept>
#include "AbstractReader.hpp"

namespace common::io
{
    class CharArrayReader final : public AbstractReader
    {
    public:
        explicit CharArrayReader(const std::vector<char>& buffer): buf_(buffer), count_(buffer.size())
        {
        }

        CharArrayReader(const std::vector<char>& buffer, const size_t offset, const size_t length)
        {
            if (offset > buffer.size() || offset + length > buffer.size())
            {
                throw std::invalid_argument("Invalid offset or length");
            }
            buf_.assign(buffer.begin() + static_cast<std::ptrdiff_t>(offset),
                        buffer.begin() + static_cast<std::ptrdiff_t>(offset + length));
            count_ = length;
        }

        ~CharArrayReader() override = default;

        auto read() -> int override
        {
            if (pos_ >= count_) return -1;
            return buf_[pos_++];
        }

        auto read(std::vector<char>& b, const size_t off, const size_t len) -> size_t override
        {
            if (pos_ >= count_) return -1;
            if (off >= b.size() || off + len > b.size())
            {
                throw std::out_of_range("Invalid offset or length for target buffer");
            }
            const size_t toRead = std::min(len, count_ - pos_);
            std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), toRead,
                        b.begin() + static_cast<std::ptrdiff_t>(off));
            pos_ += toRead;
            return toRead;
        }

        auto skip(const size_t n) -> size_t override
        {
            const size_t skipped = std::min(n, count_ - pos_);
            pos_ += skipped;
            return skipped;
        }

        [[nodiscard]] auto ready() const -> bool
        {
            return pos_ < count_;
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return true;
        }

        auto mark(const size_t readAheadLimit) -> void override
        {
            markedPos_ = readAheadLimit;
        }

        auto reset() -> void override
        {
            pos_ = markedPos_;
        }

        auto close() -> void override
        {
            buf_.clear();
            pos_ = 0;
            markedPos_ = 0;
            count_ = 0;
        }

    private:
        std::vector<char> buf_;
        size_t pos_{0};
        size_t markedPos_{0};
        size_t count_{0};
    };
}
