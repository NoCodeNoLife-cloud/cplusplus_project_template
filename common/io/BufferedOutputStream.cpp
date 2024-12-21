#include "BufferedOutputStream.hpp"

namespace common::io
{
    BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out): BufferedOutputStream(std::move(out), DEFAULT_BUFFER_SIZE) {}

    BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, const size_t size): FilterOutputStream(std::move(out)), bufferSize_(size), buffer_(size), bufferPosition_(0)
    {
        if (!&outputStream_)
        {
            throw std::invalid_argument("Output stream cannot be null");
        }
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than 0");
        }
    }

    BufferedOutputStream::~BufferedOutputStream()
    {
        try
        {
            flush();
        }
        catch (...) {}
    }

    void BufferedOutputStream::write(const std::byte b)
    {
        if (bufferPosition_ >= bufferSize_)
        {
            flushBuffer();
        }
        buffer_[bufferPosition_++] = b;
    }

    void BufferedOutputStream::write(const std::vector<std::byte>& data, const size_t offset, const size_t len)
    {
        if (offset + len > data.size())
        {
            throw std::out_of_range("Data offset/length out of range");
        }
        size_t bytesWritten = 0;
        while (bytesWritten < len)
        {
            if (bufferPosition_ == bufferSize_)
            {
                flushBuffer();
            }
            const size_t bytesToCopy = std::min(len - bytesWritten, bufferSize_ - bufferPosition_);
            std::memcpy(&buffer_[bufferPosition_], &data[offset + bytesWritten], bytesToCopy);
            bufferPosition_ += bytesToCopy;
            bytesWritten += bytesToCopy;
        }
    }

    void BufferedOutputStream::flush()
    {
        flushBuffer();
        outputStream_->flush();
    }

    void BufferedOutputStream::close()
    {
        outputStream_->close();
    }

    auto BufferedOutputStream::flushBuffer() -> void
    {
        if (bufferPosition_ > 0)
        {
            outputStream_->write(buffer_, 0, bufferPosition_);
            bufferPosition_ = 0;
        }
    }
}
