#pragma once
#include <fstream>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief Buffered character-input stream.
    class BufferedReader final : public AbstractReader
    {
    public:
        explicit BufferedReader(std::unique_ptr<AbstractReader> reader, size_t size = DEFAULT_BUFFER_SIZE);
        ~BufferedReader() override;

        /// @brief Close the stream.
        auto close() -> void override;

        /// @brief Mark the present position in the stream.
        /// @param readAheadLimit The maximum limit of characters that can be read before the mark position becomes invalid.
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Tell whether this stream supports the mark() operation.
        /// @return true if the stream supports mark(), false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reset the stream to the most recent mark.
        auto reset() -> void override;

        /// @brief Read a single character.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
        ///         or -1 if the end of the stream has been reached.
        auto read() -> int override;

        /// @brief Read characters into an array.
        /// @param cBuf The buffer into which characters are read.
        /// @param off The offset at which to start storing characters.
        /// @param len The maximum number of characters to read.
        /// @return The number of characters read, or -1 if the end of the stream has been reached.
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> int override;

        /// @brief Read a line of text.
        /// @return A String containing the next line of text, or empty string if the end of the stream has been reached.
        auto readLine() -> std::string;

        /// @brief Tell whether this stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input, false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Skip characters.
        /// @param n The number of characters to skip.
        /// @return The number of characters actually skipped.
        auto skip(size_t n) -> size_t override;

        /// @brief Checks if this reader has been closed.
        /// @return true if this reader has been closed, false otherwise.
        auto isClosed() const -> bool override;

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        std::vector<char> buffer_;
        std::unique_ptr<AbstractReader> reader_;
        size_t buffer_size_{0};
        size_t pos_{0};
        size_t count_{0};
        size_t mark_limit_{0};
        bool fillBuffer();
    };

    inline BufferedReader::BufferedReader(std::unique_ptr<AbstractReader> reader, const size_t size)
        : reader_(std::move(reader)), buffer_size_(size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than 0");
        }
        buffer_.resize(size);
    }

    inline BufferedReader::~BufferedReader() = default;

    inline auto BufferedReader::close() -> void
    {
        reader_->close();
    }

    inline auto BufferedReader::mark(const size_t readAheadLimit) -> void
    {
        if (readAheadLimit == 0)
        {
            throw std::invalid_argument("Mark limit must be greater than 0");
        }
        reader_->mark(readAheadLimit);
        mark_limit_ = pos_;
    }

    inline bool BufferedReader::markSupported() const
    {
        return true;
    }

    inline auto BufferedReader::reset() -> void
    {
        reader_->reset();
        pos_ = mark_limit_;
    }

    inline int BufferedReader::read()
    {
        if (pos_ >= count_)
        {
            if (!fillBuffer())
            {
                return -1;
            }
        }
        return static_cast<unsigned char>(buffer_[pos_++]);
    }

    inline auto BufferedReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> int
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        if (len == 0)
        {
            return 0;
        }

        size_t totalBytesRead = 0;
        size_t currentOffset = off;
        size_t remainingLen = len;

        while (remainingLen > 0)
        {
            if (pos_ >= count_)
            {
                if (!fillBuffer())
                {
                    break;
                }
            }

            const size_t bytesAvailable = count_ - pos_;
            const size_t bytesToRead = std::min(bytesAvailable, remainingLen);
            std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), bytesToRead,
                        cBuf.begin() + static_cast<std::ptrdiff_t>(currentOffset));
            totalBytesRead += bytesToRead;
            currentOffset += bytesToRead;
            remainingLen -= bytesToRead;
            pos_ += bytesToRead;
        }

        return totalBytesRead > 0 ? static_cast<int>(totalBytesRead) : -1;
    }

    inline auto BufferedReader::readLine() -> std::string
    {
        std::string line;
        while (true)
        {
            if (pos_ >= count_)
            {
                if (!fillBuffer())
                {
                    break;
                }
            }
            const char ch = buffer_[pos_++];
            if (ch == '\n')
            {
                break;
            }
            if (ch != '\r')
            {
                line += ch;
            }
        }
        return line;
    }

    inline bool BufferedReader::ready() const
    {
        return reader_->ready();
    }

    inline auto BufferedReader::skip(const size_t n) -> size_t
    {
        if (n == 0)
        {
            return 0;
        }

        size_t skipped = 0;
        size_t remaining = n;

        while (remaining > 0)
        {
            if (pos_ >= count_)
            {
                if (!fillBuffer())
                {
                    break;
                }
            }

            const size_t bytesToSkip = std::min(count_ - pos_, remaining);
            pos_ += bytesToSkip;
            remaining -= bytesToSkip;
            skipped += bytesToSkip;
        }

        return skipped;
    }

    inline bool BufferedReader::fillBuffer()
    {
        pos_ = 0;
        const int bytesRead = reader_->read(buffer_, 0, buffer_size_);
        count_ = bytesRead > 0 ? static_cast<size_t>(bytesRead) : 0;
        return count_ > 0;
    }

    inline bool BufferedReader::isClosed() const
    {
        return !reader_ || reader_->isClosed();
    }
}
