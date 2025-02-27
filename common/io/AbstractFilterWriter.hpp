#pragma once
#include <memory>
#include <stdexcept>
#include "AbstractWriter.hpp"

namespace common::io
{
    class AbstractFilterWriter abstract : public AbstractWriter
    {
    public:
        explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter);
        ~AbstractFilterWriter() override;
        auto write(char c) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        auto write(const std::vector<char>& cBuf) -> void override;
        auto write(const std::string& str, size_t off, size_t len) -> void override;
        auto write(const std::string& str) -> void override;
        auto flush() -> void override;
        auto close() -> void override;
    protected:
        std::unique_ptr<AbstractWriter> outputWriter_;
    };

    inline AbstractFilterWriter::AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter): outputWriter_(std::move(outputWriter))
    {
        if (!outputWriter_)
        {
            throw std::invalid_argument("Output writer cannot be null");
        }
    }

    inline AbstractFilterWriter::~AbstractFilterWriter() = default;

    inline void AbstractFilterWriter::write(const char c)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(c);
    }

    inline auto AbstractFilterWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
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

    inline void AbstractFilterWriter::write(const std::vector<char>& cBuf)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(cBuf);
    }

    inline void AbstractFilterWriter::write(const std::string& str, const size_t off, const size_t len)
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

    inline void AbstractFilterWriter::write(const std::string& str)
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->write(str);
    }

    inline auto AbstractFilterWriter::flush() -> void
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        outputWriter_->flush();
    }

    inline auto AbstractFilterWriter::close() -> void
    {
        if (!outputWriter_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        outputWriter_->close();
    }
}
