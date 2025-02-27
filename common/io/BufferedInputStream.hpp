#pragma once
#include <vector>
#include "FilterInputStream.hpp"

namespace common::io
{
    class BufferedInputStream final : public FilterInputStream
    {
    public:
        explicit BufferedInputStream(std::unique_ptr<AbstractInputStream> in);
        BufferedInputStream(std::unique_ptr<AbstractInputStream> in, int size);
        [[nodiscard]] auto available() const -> size_t;
        auto close() -> void override;
        auto mark(int readLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> std::byte override;
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
        auto reset() -> void override;
        auto skip(size_t n) -> size_t override;
    protected:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        std::vector<std::byte> buf_;
        size_t count_{0};
        size_t markLimit_{0};
        size_t markPos_{0};
        size_t pos_{0};
        auto fillBuffer() -> void;
    };

    inline BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in): BufferedInputStream(std::move(in), DEFAULT_BUFFER_SIZE) {}

    inline BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in, const int size): FilterInputStream(std::move(in)), buf_(size)
    {
        if (!&inputStream_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
        if (size <= 0)
        {
            throw std::invalid_argument("Buffer size must be greater than zero");
        }
    }

    inline auto BufferedInputStream::available() const -> size_t
    {
        return count_ - pos_ + inputStream_->available();
    }

    inline void BufferedInputStream::close()
    {
        inputStream_->close();
        buf_.clear();
    }

    inline void BufferedInputStream::mark(const int readLimit)
    {
        markLimit_ = readLimit;
        inputStream_->mark(readLimit);
        markPos_ = pos_;
    }

    inline bool BufferedInputStream::markSupported() const
    {
        return true;
    }

    inline std::byte BufferedInputStream::read()
    {
        if (pos_ >= count_)
        {
            fillBuffer();
            if (pos_ >= count_)
            {
                return static_cast<std::byte>(-1);
            }
        }
        return buf_[pos_++];
    }

    inline size_t BufferedInputStream::read(std::vector<std::byte>& buffer, size_t offset, size_t len)
    {
        if (offset + len > static_cast<int>(buffer.size()))
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }
        size_t totalBytesRead = 0;
        while (len > 0)
        {
            size_t bytesAvailable = count_ - pos_;
            if (bytesAvailable <= 0)
            {
                fillBuffer();
                bytesAvailable = count_ - pos_;
                if (bytesAvailable <= 0)
                {
                    break;
                }
            }
            const size_t bytesToRead = std::min(len, bytesAvailable);
            std::copy_n(buf_.begin() + static_cast<long long>(pos_), bytesToRead, buffer.begin() + static_cast<long long>(offset));
            pos_ += bytesToRead;
            offset += bytesToRead;
            len -= bytesToRead;
            totalBytesRead += bytesToRead;
        }
        return totalBytesRead > 0 ? totalBytesRead : -1;
    }

    inline void BufferedInputStream::reset()
    {
        pos_ = markPos_;
        inputStream_->reset();
    }

    inline size_t BufferedInputStream::skip(size_t n)
    {
        if (n <= 0)
        {
            return 0;
        }
        size_t skipped = 0;
        while (n > 0)
        {
            size_t bytesAvailable = count_ - pos_;
            if (bytesAvailable <= 0)
            {
                fillBuffer();
                bytesAvailable = count_ - pos_;
                if (bytesAvailable <= 0)
                {
                    break;
                }
            }
            const auto bytesToSkip = std::min(bytesAvailable, n);
            pos_ += bytesToSkip;
            n -= bytesToSkip;
            skipped += bytesToSkip;
        }
        return skipped;
    }

    inline auto BufferedInputStream::fillBuffer() -> void
    {
        if (markPos_ < 0 || pos_ - markPos_ >= markLimit_)
        {
            markPos_ = -1;
        }
        if (const size_t bytesRead = inputStream_->read(buf_); bytesRead > 0)
        {
            pos_ = 0;
            count_ = bytesRead;
        }
        else
        {
            count_ = 0;
        }
    }
}
