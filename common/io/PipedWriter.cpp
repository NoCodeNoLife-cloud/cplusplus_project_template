#include "PipedWriter.hpp"
#include <utility>

namespace common::io
{
    PipedWriter::PipedWriter() = default;

    PipedWriter::PipedWriter(std::shared_ptr<PipedReader> writer): reader_(std::move(writer)) {}

    PipedWriter::~PipedWriter()
    {
        close();
    }

    auto PipedWriter::close() -> void
    {
        if (closed_)
        {
            return;
        }
        flush();
        closed_ = true;
        if (reader_)
        {
            reader_->close();
            reader_.reset();
        }
    }

    auto PipedWriter::flush() -> void
    {
        // no-op
    }

    void PipedWriter::write(const char c)
    {
        std::lock_guard lock(writeMutex_);
        if (closed_)
        {
            throw std::runtime_error("Cannot write to a closed pipe.");
        }
        if (!reader_)
        {
            throw std::runtime_error("Pipe is not connected to a reader.");
        }
        reader_->writeToBuffer(c);
    }

    auto PipedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        std::lock_guard lock(writeMutex_);
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow detected in write.");
        }
        if (closed_)
        {
            throw std::runtime_error("Cannot write to a closed pipe.");
        }
        if (!reader_)
        {
            throw std::runtime_error("Pipe is not connected to a reader.");
        }
        for (size_t i = 0; i < len; ++i)
        {
            reader_->writeToBuffer(cBuf[off + i]);
        }
    }

    auto PipedWriter::toString() const -> std::string
    {
        return "";
    }

    auto PipedWriter::connect(std::shared_ptr<PipedReader> snk) -> void
    {
        if (reader_ || closed_)
        {
            throw std::runtime_error("Pipe already connected or closed.");
        }
        reader_ = std::move(snk);
    }
}
