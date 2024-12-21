#include "AbstractFilterWriter.hpp"
#include <stdexcept>

namespace common::io
{
    AbstractFilterWriter::AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter): outputWriter_(std::move(outputWriter))
    {
        if (!outputWriter_)
        {
            throw std::invalid_argument("Output writer cannot be null");
        }
    }

    AbstractFilterWriter::~AbstractFilterWriter() = default;

    void AbstractFilterWriter::write(const char c)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(c);
    }

    auto AbstractFilterWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        outputWriter_->write(cBuf, off, len);
    }

    void AbstractFilterWriter::write(const std::vector<char>& cBuf)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(cBuf);
    }

    void AbstractFilterWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (off + len > str.size())
        {
            throw std::out_of_range("String overflow");
        }
        outputWriter_->write(str, off, len);
    }

    void AbstractFilterWriter::write(const std::string& str)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(str);
    }

    auto AbstractFilterWriter::flush() -> void
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->flush();
    }

    auto AbstractFilterWriter::close() -> void
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        outputWriter_->close();
    }
}
