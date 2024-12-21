#include "AbstractFilterWriter.hpp"

#include <stdexcept>

namespace common
{
    AbstractFilterWriter::AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter) :
        output_writer_(std::move(outputWriter))
    {
        if (!output_writer_)
        {
            throw std::invalid_argument("Output writer cannot be null");
        }
    }

    AbstractFilterWriter::~AbstractFilterWriter() = default;

    void AbstractFilterWriter::write(const char c)
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_writer_->write(c);
    }

    auto AbstractFilterWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        output_writer_->write(cBuf, off, len);
    }

    void AbstractFilterWriter::write(const std::vector<char>& cBuf)
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_writer_->write(cBuf);
    }

    void AbstractFilterWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (off + len > str.size())
        {
            throw std::out_of_range("String overflow");
        }
        output_writer_->write(str, off, len);
    }

    void AbstractFilterWriter::write(const std::string& str)
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_writer_->write(str);
    }

    auto AbstractFilterWriter::flush() -> void
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_writer_->flush();
    }

    auto AbstractFilterWriter::close() -> void
    {
        if (!output_writer_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        output_writer_->close();
    }
}
