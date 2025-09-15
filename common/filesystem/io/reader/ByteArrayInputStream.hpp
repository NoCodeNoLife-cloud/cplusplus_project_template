#pragma once
#include <algorithm>
#include <vector>

#include "AbstractInputStream.hpp"

namespace fox
{
    /// @brief A ByteArrayInputStream contains an internal buffer that contains bytes that may be read from the stream.
    /// ByteArrayInputStream uses a std::vector<std::byte> as the internal buffer.
    class ByteArrayInputStream final : public AbstractInputStream
    {
    public:
        explicit ByteArrayInputStream(const std::vector<std::byte>& buf);

        /// @brief Reads the next byte of data from the input stream.
        /// @return the next byte of data, or -1 if the end of the stream is reached.
        auto read() -> std::byte override;

        /// @brief Reads up to len bytes of data from the input stream into an array of bytes.
        /// @param cBuf the buffer into which the data is read.
        /// @param off the start offset in the destination array cBuf.
        /// @param len the maximum number of bytes to read.
        /// @return the total number of bytes read into the buffer, or 0 if there is no more data because the end of the
        /// stream has been reached.
        auto read(std::vector<std::byte>& cBuf, const size_t off, size_t len) -> size_t override;

        /// @brief Skips over and discards n bytes of data from this input stream.
        /// @param n the number of bytes to be skipped.
        /// @return the total number of bytes skipped.
        auto skip(const size_t n) -> size_t override;

        /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by
        /// the next caller of a method for this input stream.
        /// @return the number of bytes that can be read (or skipped over) from this input stream without blocking.
        auto available() -> size_t override;

        /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
        auto reset() -> void override;

        /// @brief Marks the current position in this input stream.
        /// @param readLimit the maximum limit of bytes that can be read ahead.
        auto mark(const int32_t readLimit) -> void override;

        /// @brief Tests if this input stream supports the mark and reset methods.
        /// @return true if this stream instance supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Closes this input stream and releases any system resources associated with the stream.
        auto close() -> void override;

    protected:
        const std::vector<std::byte> buffer_;
        size_t pos_{0};
        size_t mark_position_{0};
    };

    inline ByteArrayInputStream::ByteArrayInputStream(const std::vector<std::byte>& buf) : buffer_(buf)
    {
    }

    inline auto ByteArrayInputStream::read() -> std::byte
    {
        if (pos_ >= buffer_.size())
        {
            return static_cast<std::byte>(-1);
        }
        return buffer_[pos_++];
    }

    inline size_t ByteArrayInputStream::read(std::vector<std::byte>& cBuf, const size_t off, size_t len)
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Offset and length exceed the size of the buffer");
        }

        if (pos_ >= buffer_.size())
        {
            return 0;
        }

        if (const size_t remaining = buffer_.size() - pos_; len > remaining)
        {
            len = remaining;
        }

        std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), len,
                    cBuf.begin() + static_cast<std::ptrdiff_t>(off));
        pos_ += len;
        return len;
    }

    inline size_t ByteArrayInputStream::skip(const size_t n)
    {
        const size_t available = buffer_.size() - pos_;
        const size_t bytesToSkip = std::min(n, available);
        pos_ += bytesToSkip;
        return bytesToSkip;
    }

    inline auto ByteArrayInputStream::available() -> size_t
    {
        return buffer_.size() - pos_;
    }

    inline void ByteArrayInputStream::reset()
    {
        pos_ = mark_position_;
    }

    inline void ByteArrayInputStream::mark(const int32_t readLimit)
    {
        mark_position_ = std::min(static_cast<size_t>(readLimit), buffer_.size());
    }

    inline bool ByteArrayInputStream::markSupported() const
    {
        return true;
    }

    inline auto ByteArrayInputStream::close() -> void
    {
        // do nothing
    }
} // namespace fox
