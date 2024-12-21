#pragma once
#include <stdexcept>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
    class ByteArrayInputStream final : public AbstractInputStream
    {
    public:
        explicit ByteArrayInputStream(const std::vector<std::byte>& buf): buffer_(buf)
        {
        }

        auto read() -> std::byte override
        {
            if (pos_ >= buffer_.size())
            {
                return static_cast<std::byte>(-1);
            }
            return buffer_[pos_++];
        }

        auto skip(const size_t n) -> size_t override
        {
            const size_t available = buffer_.size() - pos_;
            const size_t bytesToSkip = std::min(n, available);
            pos_ += bytesToSkip;
            return bytesToSkip;
        }

        auto read(std::vector<std::byte>& cBuf, const size_t off, size_t len) -> size_t override
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

        size_t available() override
        {
            return buffer_.size() - pos_;
        }

        void reset() override
        {
            pos_ = markPosition_;
        }

        void mark(const size_t readAheadLimit)
        {
            markPosition_ = std::min(readAheadLimit, buffer_.size());
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return true;
        }

        auto close() -> void override
        {
            // do nothing
        }

    protected:
        const std::vector<std::byte> buffer_;
        size_t pos_{0};
        size_t markPosition_{0};
    };
}
