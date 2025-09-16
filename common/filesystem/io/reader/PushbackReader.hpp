#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "FilterReader.hpp"

namespace fox
{
    /// @brief Provides a buffering wrapper around another reader, allowing characters to be "pushed back" into the stream.
    /// @details The PushbackReader class allows characters to be pushed back into the stream after they have been read.
    /// This is useful for situations where a program needs to look ahead in the input stream and then return to the
    /// original position. The class maintains an internal buffer to store the pushed-back characters. When reading, it
    /// first checks this buffer before reading from the underlying reader.
    class PushbackReader final : public FilterReader
    {
    public:
        explicit PushbackReader(std::shared_ptr<AbstractReader> reader);

        PushbackReader(std::shared_ptr<AbstractReader> reader, size_t size);

        /// @brief Closes this pushback reader and releases any system resources associated with it.
        /// @details Once the stream has been closed, further read(), unread(), ready(), mark(),
        /// reset(), or skip() invocations will throw an IOException.
        /// Closing a previously closed stream has no effect.
        auto close() -> void override;

        /// @brief Marks the current position in this stream.
        /// @details A subsequent call to the reset() method repositions this stream at the last marked position so that
        /// subsequent reads re-read the same bytes. The readAheadLimit argument tells this stream to allow that many bytes
        /// to be read before the mark position gets invalidated.
        /// @param readAheadLimit the maximum limit of bytes that can be read before the mark position becomes invalid
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Tests if this stream supports the mark() and reset() methods.
        /// @details Whether mark() and reset() are supported is an invariant property of a particular stream instance.
        /// The markSupported() method of FilterReader returns true.
        /// @return true if this stream supports the mark() and reset() methods; false otherwise
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reads a single character.
        /// @details This method will block until a character is available, an I/O error occurs, or the end of the stream is
        /// reached. If the pushback buffer is not empty, a character from the pushback buffer is returned. Otherwise, a
        /// character from the underlying input stream is returned.
        /// @return The character read, or -1 if the end of the stream has been reached
        auto read() -> size_t override;

        /// @brief Reads up to len characters of data from this stream into an array of characters.
        /// @details This method will block until some input is available, an I/O error occurs, or the end of the stream is
        /// reached. If the pushback buffer is not empty, characters from the pushback buffer are returned. Otherwise,
        /// characters from the underlying input stream are returned.
        /// @param cBuf the buffer into which the data is read
        /// @param off the start offset in the destination array cBuf
        /// @param len the maximum number of characters read
        /// @return the total number of characters read into the buffer, or -1 if there is no more data because the end of
        /// the stream has been reached
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

        /// @brief Tells whether this stream is ready to be read.
        /// @details A stream is ready to be read if there are characters available in the pushback buffer,
        /// or if the underlying input stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input, false otherwise.
        /// Note that returning false does not guarantee that the next read() will block.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Repositions this stream to the position at the time the mark() method was last called on this stream.
        /// @details This method will block until a character is available, an I/O error occurs, or the end of the stream is
        /// reached. If the pushback buffer is not empty, a character from the pushback buffer is returned. Otherwise, a
        /// character from the underlying input stream is returned.
        auto reset() -> void override;

        /// @brief Skips n characters from the input stream.
        /// @details This method will block until n characters are available, an I/O error occurs, or the end of the stream
        /// is reached. Characters in the pushback buffer are skipped first, then characters from the underlying input
        /// stream are skipped.
        /// @param n the number of characters to skip
        /// @return the actual number of characters skipped
        auto skip(size_t n) -> size_t override;

        /// @brief Pushes back all characters of the given array into the pushback buffer.
        /// @details This method pushes back all characters of the given array into the pushback buffer.
        /// The characters are pushed back in reverse order, so that the next read operation will read
        /// the characters in the same order as they appear in the array.
        /// @param cbuf the array of characters to push back
        auto unread(const std::vector<char>& cbuf) -> void;

        /// @brief Pushes back a portion of the given character array into the pushback buffer.
        /// @details This method pushes back len characters from the given array starting at offset off
        /// into the pushback buffer. The characters are pushed back in reverse order, so that the next
        /// read operation will read the characters in the same order as they appear in the array.
        /// @param cBuf the array of characters to push back
        /// @param off the start offset in the array
        /// @param len the number of characters to push back
        auto unread(const std::vector<char>& cBuf, size_t off, size_t len) -> void;

        /// @brief Pushes back a single character into the pushback buffer.
        /// @details This method pushes back a single character into the pushback buffer.
        /// The character is pushed back so that the next read operation will read this character.
        /// @param c the character to push back
        auto unread(int32_t c) -> void;

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::vector<char> buffer_;
        size_t buffer_pos_{DEFAULT_BUFFER_SIZE};
    };

    inline PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader)
        : PushbackReader(std::move(reader), DEFAULT_BUFFER_SIZE)
    {
    }

    inline PushbackReader::PushbackReader(std::shared_ptr<AbstractReader> reader, const size_t size)
        : FilterReader(std::move(reader)), buffer_(size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than zero.");
        }
    }

    inline void PushbackReader::close()
    {
        FilterReader::close();
        buffer_.clear();
    }

    inline void PushbackReader::mark(size_t readAheadLimit)
    {
        throw std::runtime_error("mark() not supported.");
    }

    inline bool PushbackReader::markSupported() const
    {
        return false;
    }

    inline size_t PushbackReader::read()
    {
        if (!in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        if (buffer_pos_ < buffer_.size())
        {
            return static_cast<unsigned char>(buffer_[buffer_pos_++]);
        }
        return FilterReader::read();
    }

    inline size_t PushbackReader::read(std::vector<char>& cBuf, size_t off, const size_t len)
    {
        if (!in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer overflow.");
        }

        size_t bytesRead = 0;
        while (buffer_pos_ < buffer_.size() && bytesRead < len)
        {
            cBuf[off++] = buffer_[buffer_pos_++];
            bytesRead++;
        }
        if (bytesRead < len)
        {
            bytesRead += FilterReader::read(cBuf, off, len - bytesRead);
        }
        return bytesRead;
    }

    inline bool PushbackReader::ready() const
    {
        if (!in_)
        {
            return false;
        }
        return buffer_pos_ < buffer_.size() || FilterReader::ready();
    }

    inline void PushbackReader::reset()
    {
        throw std::runtime_error("reset() not supported.");
    }

    inline size_t PushbackReader::skip(size_t n)
    {
        if (!in_)
        {
            throw std::runtime_error("Underlying reader is not available");
        }

        size_t skipped = 0;
        if (buffer_pos_ < buffer_.size())
        {
            const size_t bufferRemaining = buffer_.size() - buffer_pos_;
            skipped = std::min(n, bufferRemaining);
            buffer_pos_ += skipped;
            n -= skipped;
        }
        if (n > 0)
        {
            skipped += FilterReader::skip(n);
        }
        return skipped;
    }

    inline auto PushbackReader::unread(const std::vector<char>& cbuf) -> void
    {
        unread(cbuf, 0, cbuf.size());
    }

    inline auto PushbackReader::unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        if (len > buffer_pos_)
        {
            throw std::overflow_error("Pushback buffer overflow.");
        }

        for (size_t i = 0; i < len; ++i)
        {
            buffer_[--buffer_pos_] = cBuf[off + len - 1 - i];
        }
    }

    inline auto PushbackReader::unread(const int32_t c) -> void
    {
        if (buffer_pos_ == 0)
        {
            throw std::overflow_error("Pushback buffer overflow.");
        }
        buffer_[--buffer_pos_] = static_cast<char>(c);
    }
} // namespace fox
