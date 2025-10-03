#include "src/filesystem/io/reader/BufferedInputStream.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>

#include "src/filesystem/io/reader/AbstractInputStream.hpp"
#include "src/filesystem/io/reader/BufferedReader.hpp"
#include "src/filesystem/io/reader/FilterInputStream.hpp"

namespace common
{
    BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in)
        : BufferedInputStream(std::move(in), DEFAULT_BUFFER_SIZE)
    {
    }

    BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in, const size_t size)
        : FilterInputStream(std::move(in)), buf_(size)
    {
        if (!input_stream_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than zero");
        }
    }

    auto BufferedInputStream::available() const -> size_t
    {
        return count_ - pos_ + input_stream_->available();
    }

    void BufferedInputStream::close()
    {
        input_stream_->close();
        buf_.clear();
    }

    void BufferedInputStream::mark(const int32_t readLimit)
    {
        mark_limit_ = readLimit;
        input_stream_->mark(readLimit);
        mark_pos_ = pos_;
    }

    bool BufferedInputStream::markSupported() const
    {
        return true;
    }

    std::byte BufferedInputStream::read()
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

    size_t BufferedInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        if (len == 0)
        {
            return 0;
        }

        size_t totalBytesRead = 0;
        size_t currentOffset = offset;
        size_t remainingLen = len;

        while (remainingLen > 0)
        {
            if (const size_t bytesAvailable = count_ - pos_; bytesAvailable == 0)
            {
                fillBuffer();
                if (count_ - pos_ == 0)
                {
                    break;
                }
            }

            const size_t bytesToRead = std::min(remainingLen, count_ - pos_);
            std::copy_n(buf_.begin() + static_cast<std::ptrdiff_t>(pos_), bytesToRead,
                        buffer.begin() + static_cast<std::ptrdiff_t>(currentOffset));
            pos_ += bytesToRead;
            currentOffset += bytesToRead;
            remainingLen -= bytesToRead;
            totalBytesRead += bytesToRead;
        }

        return totalBytesRead;
    }

    void BufferedInputStream::reset()
    {
        pos_ = mark_pos_;
        input_stream_->reset();
    }

    size_t BufferedInputStream::skip(const size_t n)
    {
        if (n == 0)
        {
            return 0;
        }

        size_t skipped = 0;
        size_t remaining = n;

        while (remaining > 0)
        {
            if (const size_t bytesAvailable = count_ - pos_; bytesAvailable == 0)
            {
                fillBuffer();
                if (count_ - pos_ == 0)
                {
                    break;
                }
            }

            const size_t bytesToSkip = std::min(remaining, count_ - pos_);
            pos_ += bytesToSkip;
            remaining -= bytesToSkip;
            skipped += bytesToSkip;
        }

        return skipped;
    }

    bool BufferedInputStream::isClosed() const
    {
        return !input_stream_ || input_stream_->isClosed();
    }

    void BufferedInputStream::fillBuffer()
    {
        // Implementation would go here
        // This is a placeholder since the original implementation wasn't provided
    }
}
