#pragma once
#include "FilterInputStream.hpp"

namespace common::io
{
    class PushbackInputStream final : public FilterInputStream
    {
    public:
        PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, size_t bufferSize):
            FilterInputStream(std::move(inputStream)), pushbackBuffer_(bufferSize), bufferPos_(bufferSize)
        {
        }

        ~PushbackInputStream() override = default;

        auto available() -> size_t override
        {
            return pushbackBuffer_.size() - bufferPos_ + inputStream_->available();
        }

        auto read() -> std::byte override
        {
            if (bufferPos_ < pushbackBuffer_.size())
            {
                return pushbackBuffer_[bufferPos_++];
            }
            return inputStream_->read();
        }

        auto read(std::vector<std::byte>& buffer) -> size_t override
        {
            return read(buffer, 0, buffer.size());
        }

        auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t override
        {
            if (offset + len > buffer.size())
            {
                throw std::out_of_range("Buffer overflow");
            }
            size_t bytesRead = 0;
            while (bytesRead < len && bufferPos_ < pushbackBuffer_.size())
            {
                buffer[offset + bytesRead++] = pushbackBuffer_[bufferPos_++];
            }
            if (bytesRead < len)
            {
                bytesRead += inputStream_->read(buffer, offset + bytesRead, len - bytesRead);
            }
            return bytesRead;
        }

        void unread(const std::vector<std::byte>& buffer)
        {
            unread(buffer, 0, buffer.size());
        }

        void unread(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
        {
            if (len > bufferPos_)
            {
                throw std::overflow_error("Pushback buffer overflow");
            }
            for (size_t i = 0; i < len; ++i)
            {
                pushbackBuffer_[--bufferPos_] = buffer[offset + len - i - 1];
            }
        }

        void unread(const std::byte b)
        {
            if (bufferPos_ == 0)
            {
                throw std::overflow_error("Pushback buffer overflow");
            }
            pushbackBuffer_[--bufferPos_] = b;
        }

    private:
        std::vector<std::byte> pushbackBuffer_;
        size_t bufferPos_{0};
    };
}
