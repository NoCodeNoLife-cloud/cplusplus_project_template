#include "PipedReader.hpp"
#include <utility>

namespace common::io
{
    PipedReader::PipedReader(): PipedReader(DEFAULT_PIPE_SIZE) {}

    PipedReader::PipedReader(const int32_t pipeSize): buffer_(pipeSize), bufferSize_(pipeSize) {}

    PipedReader::PipedReader(const std::shared_ptr<PipedWriter>& src): PipedReader(src, DEFAULT_PIPE_SIZE) {}

    PipedReader::PipedReader(std::shared_ptr<PipedWriter> src, const int32_t pipeSize): src_(std::move(src)), buffer_(pipeSize), bufferSize_(pipeSize) {}

    PipedReader::~PipedReader()
    {
        close();
    }

    auto PipedReader::close() -> void
    {
        src_.reset();
        buffer_.clear();
        readPos_ = writePos_ = 0;
    }

    int32_t PipedReader::read()
    {
        std::lock_guard lock(readMutex_);
        if (!ready())
        {
            return -1;
        }
        return buffer_[readPos_++ % bufferSize_];
    }

    auto PipedReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
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

    bool PipedReader::ready() const
    {
        return readPos_ != writePos_;
    }

    auto PipedReader::connect(std::shared_ptr<PipedWriter> src) -> void
    {
        if (src_)
        {
            throw std::runtime_error("already connected");
        }
        src_ = std::move(src);
    }

    auto PipedReader::mark(size_t readAheadLimit) -> void
    {
        // no-op
    }

    auto PipedReader::reset() -> void
    {
        // no-op
    }

    bool PipedReader::markSupported() const
    {
        return false;
    }

    auto PipedReader::writeToBuffer(const char c) -> void
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
}
