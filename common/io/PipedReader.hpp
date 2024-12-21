#pragma once
#include <mutex>
#include <utility>
#include "AbstractReader.hpp"
#include "PipedWriter.hpp"

namespace common::io
{
    class PipedWriter;

    class PipedReader final : public AbstractReader
    {
    public:
        PipedReader(): PipedReader(DEFAULT_PIPE_SIZE)
        {
        }

        explicit PipedReader(int pipeSize) : buffer_(pipeSize), bufferSize_(pipeSize)
        {
        }

        explicit PipedReader(const std::shared_ptr<PipedWriter>& src) : PipedReader(src, DEFAULT_PIPE_SIZE)
        {
        }

        PipedReader(std::shared_ptr<PipedWriter> src, const int pipeSize) : src_(std::move(src)), buffer_(pipeSize),
                                                                            bufferSize_(pipeSize)
        {
        }

        ~PipedReader() override
        {
            close();
        }

        auto close() -> void override
        {
            src_.reset();
            buffer_.clear();
            readPos_ = writePos_ = 0;
        }

        auto read() -> int override
        {
            std::lock_guard lock(readMutex_);
            if (!ready())
            {
                return -1;
            }
            return buffer_[readPos_++ % bufferSize_];
        }

        auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override
        {
            std::lock_guard lock(readMutex_);
            if (off + len > cBuf.size())
            {
                throw std::out_of_range("index out of range");
            }
            size_t bytesRead = 0;
            while (bytesRead < len && ready())
            {
                cBuf[off + bytesRead] = buffer_[readPos_++ % bufferSize_];
                ++bytesRead;
            }
            return bytesRead;
        }

        [[nodiscard]] auto ready() const -> bool override
        {
            return readPos_ != writePos_;
        }

        auto connect(std::shared_ptr<PipedWriter> src) -> void
        {
            if (src_)
            {
                throw std::runtime_error("already connected");
            }
            src_ = std::move(src);
        }

        auto mark(size_t readAheadLimit) -> void override
        {
            // no-op
        }

        auto reset() -> void override
        {
            // no-op
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return false;
        }

        auto writeToBuffer(char c) -> void
        {
            if (bufferSize_ == 0)
            {
                throw std::runtime_error("Buffer not initialized or closed.");
            }
            const size_t nextWritePos = (writePos_ + 1) % bufferSize_;
            if (nextWritePos == readPos_)
            {
                throw std::runtime_error("Pipe buffer overflow: Reader has not consumed data.");
            }
            buffer_[writePos_] = c;
            writePos_ = nextWritePos;
        }

    private:
        static constexpr int DEFAULT_PIPE_SIZE = 1024;
        std::shared_ptr<PipedWriter> src_;
        std::vector<char> buffer_;
        size_t bufferSize_{0};
        size_t readPos_{0};
        size_t writePos_{0};
        std::mutex readMutex_;
    };
}
