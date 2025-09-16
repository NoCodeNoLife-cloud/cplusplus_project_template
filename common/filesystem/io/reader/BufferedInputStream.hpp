#pragma once
#include <memory>
#include <vector>

#include "FilterInputStream.hpp"

namespace fox
{
    /// @brief BufferedInputStream is a wrapper around another input stream that provides buffering functionality.
    /// It reads data from the underlying stream in chunks and stores it in an internal buffer to improve performance.
    class BufferedInputStream final : public FilterInputStream
    {
    public:
        explicit BufferedInputStream(std::unique_ptr<AbstractInputStream> in);
        BufferedInputStream(std::unique_ptr<AbstractInputStream> in, int32_t size);

        /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking.
        /// @return the number of bytes that can be read (or skipped over) from this input stream without blocking.
        [[nodiscard]] auto available() const -> size_t;

        /// @brief Closes this input stream and releases any system resources associated with the stream.
        auto close() -> void override;

        /// @brief Marks the current position in this input stream.
        auto mark(int32_t readLimit) -> void override;

        /// @brief Tests if this input stream supports the mark and reset methods.
        /// @return true if this stream instance supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reads the next byte of data from this input stream.
        /// @return the next byte of data, or -1 if the end of the stream is reached.
        auto read() -> std::byte override;

        /// @brief Reads up to len bytes of data from this input stream into an array of bytes.
        /// @param buffer the buffer into which the data is read.
        /// @param offset the start offset in the destination array buffer.
        /// @param len the maximum number of bytes to read.
        /// @return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;

        /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
        auto reset() -> void override;

        /// @brief Skips over and discards n bytes of data from this input stream.
        auto skip(size_t n) -> size_t override;

    protected:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        std::vector<std::byte> buf_;
        size_t count_{0};
        size_t mark_limit_{0};
        size_t mark_pos_{0};
        size_t pos_{0};
        auto fillBuffer() -> void;
    };

    inline BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in)
        : BufferedInputStream(std::move(in), DEFAULT_BUFFER_SIZE)
    {
    }

    inline BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in, const int32_t size)
        : FilterInputStream(std::move(in)), buf_(size)
    {
        if (!input_stream_)
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
        return count_ - pos_ + input_stream_->available();
    }

    inline void BufferedInputStream::close()
    {
        input_stream_->close();
        buf_.clear();
    }

    inline void BufferedInputStream::mark(const int32_t readLimit)
    {
        mark_limit_ = readLimit;
        input_stream_->mark(readLimit);
        mark_pos_ = pos_;
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

    inline void BufferedInputStream::reset()
    {
        pos_ = mark_pos_;
        input_stream_->reset();
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
} // namespace fox
