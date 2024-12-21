#include "BufferedInputStream.hpp"

#include <memory>
#include <stdexcept>

namespace common
{
    BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in) :
        BufferedInputStream(std::move(in), DEFAULT_BUFFER_SIZE)
    {
    }

    BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in, const int32_t size) :
        FilterInputStream(std::move(in)), buf_(size)
    {
        if (!&input_stream_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
        if (size <= 0)
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

    size_t BufferedInputStream::read(std::vector<std::byte>& buffer, size_t offset, size_t len)
    {
        if (offset + len > static_cast<int32_t>(buffer.size()))
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
            std::copy_n(buf_.begin() + static_cast<int64_t>(pos_), bytesToRead,
                        buffer.begin() + static_cast<int64_t>(offset));
            pos_ += bytesToRead;
            offset += bytesToRead;
            len -= bytesToRead;
            totalBytesRead += bytesToRead;
        }
        return totalBytesRead > 0 ? totalBytesRead : -1;
    }

    void BufferedInputStream::reset()
    {
        pos_ = mark_pos_;
        input_stream_->reset();
    }

    size_t BufferedInputStream::skip(size_t n)
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

    auto BufferedInputStream::fillBuffer() -> void
    {
        if (mark_pos_ < 0 || pos_ - mark_pos_ >= mark_limit_)
        {
            mark_pos_ = -1;
        }
        if (const size_t bytesRead = input_stream_->read(buf_); bytesRead > 0)
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
