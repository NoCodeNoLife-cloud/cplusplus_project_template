#pragma once
#include <fstream>
#include "AbstractReader.hpp"

namespace common::io
{
    class BufferedReader final : public AbstractReader
    {
    public:
        explicit BufferedReader(std::unique_ptr<AbstractReader> reader,
                                const int size = DEFAULT_BUFFER_SIZE): reader_(std::move(reader)), bufferSize_(size)
        {
            if (size <= 0)
            {
                throw std::invalid_argument("Buffer size must be greater than 0");
            }
            buffer_.resize(size);
        }

        ~BufferedReader() override = default;

        auto close() -> void override
        {
            reader_->close();
        }

        auto mark(const size_t readAheadLimit) -> void override
        {
            if (readAheadLimit <= 0)
            {
                throw std::invalid_argument("Mark limit must be greater than 0");
            }
            reader_->mark(readAheadLimit);
            markLimit_ = readAheadLimit;
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return true;
        }

        auto reset() -> void override
        {
            reader_->reset();
            pos_ = markLimit_;
        }

        auto read() -> int override
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

        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override
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

        auto readLine() -> std::string
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

        [[nodiscard]] auto ready() const -> bool
        {
            return reader_->ready();
        }

        auto skip(const long n) -> long
        {
            if (n <= 0)
            {
                throw std::invalid_argument("Skip value must be positive");
            }
            long skipped = 0;
            while (skipped < n)
            {
                if (pos_ >= count_)
                {
                    if (!fillBuffer())
                    {
                        break;
                    }
                }
                const long bytesToSkip = std::min(static_cast<long>(count_ - pos_), n - skipped);
                pos_ += bytesToSkip;
                skipped += bytesToSkip;
            }
            return skipped;
        }

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        std::vector<char> buffer_;
        std::unique_ptr<AbstractReader> reader_;
        size_t bufferSize_{0};
        size_t pos_{0};
        size_t count_{0};
        size_t markLimit_{0};

        bool fillBuffer()
        {
            pos_ = 0;
            count_ = reader_->read(buffer_, 0, bufferSize_);
            return count_ > 0;
        }
    };
}
