#pragma once
#include <fstream>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief Buffered character-input stream.
    class BufferedReader final : public AbstractReader
    {
    public:
        explicit BufferedReader(std::unique_ptr<AbstractReader> reader, int32_t size = DEFAULT_BUFFER_SIZE);
        ~BufferedReader() override;

        /// @brief Close the stream.
        auto close() -> void override;

        /// @brief Mark the present position in the stream.
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Tell whether this stream supports the mark() operation.
        /// @return true if the stream supports mark(), false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reset the stream to the most recent mark.
        auto reset() -> void override;

        /// @brief Read a single character.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
        auto read() -> size_t override;

        /// @brief Read characters into an array.
        /// @param cBuf The buffer into which characters are read.
        /// @param off The offset at which to start storing characters.
        /// @param len The maximum number of characters to read.
        /// @return The number of characters read, or -1 if the end of the stream has been reached.
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;

        /// @brief Read a line of text.
        /// @return A String containing the next line of text, or null if the end of the stream has been reached.
        auto readLine() -> std::string;

        /// @brief Tell whether this stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input, false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Skip characters.
        /// @param n The number of characters to skip.
        /// @return The number of characters actually skipped.
        auto skip(int64_t n) -> int64_t;

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

    inline BufferedReader::BufferedReader(std::unique_ptr<AbstractReader> reader, const int32_t size)
        : reader_(std::move(reader)), buffer_size_(size)
    {
        if (size <= 0)
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
        if (readAheadLimit <= 0)
        {
            throw std::invalid_argument("Mark limit must be greater than 0");
        }
        reader_->mark(readAheadLimit);
        mark_limit_ = readAheadLimit;
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

    inline size_t BufferedReader::read()
    {
        if (pos_ >= count_)
        {
            if (!fillBuffer())
            {
                return -1;
            }
        }
        return buffer_[pos_++];
    }

    inline auto BufferedReader::read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t
    {
        if (off + len > cBuf.size())
        {
            return -1;
        }
        size_t totalBytesRead = 0;
        if (len == 0)
        {
            return 0;
        }
        while (len > 0)
        {
            if (pos_ >= count_)
            {
                if (!fillBuffer())
                {
                    break;
                }
            }
            size_t bytesAvailable = count_ - pos_;
            const size_t bytesToRead = std::min(bytesAvailable, len);
            std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), bytesToRead,
                        cBuf.begin() + static_cast<std::ptrdiff_t>(off));
            totalBytesRead += bytesToRead;
            off += bytesToRead;
            len -= bytesToRead;
            pos_ += bytesToRead;
        }
        return totalBytesRead;
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

    inline auto BufferedReader::skip(const int64_t n) -> int64_t
    {
        if (n <= 0)
        {
            throw std::invalid_argument("Skip value must be positive");
        }
        int64_t skipped = 0;
        while (skipped < n)
        {
            if (pos_ >= count_)
            {
                if (!fillBuffer())
                {
                    break;
                }
            }
            const int64_t bytesToSkip = std::min(static_cast<int64_t>(count_ - pos_), n - skipped);
            pos_ += bytesToSkip;
            skipped += bytesToSkip;
        }
        return skipped;
    }

    inline bool BufferedReader::fillBuffer()
    {
        pos_ = 0;
        count_ = reader_->read(buffer_, 0, buffer_size_);
        return count_ > 0;
    }
} // namespace fox
