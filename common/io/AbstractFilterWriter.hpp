#pragma once
#include <memory>
#include <stdexcept>
#include "AbstractWriter.hpp"

namespace common::io
{
    class AbstractFilterWriter abstract : public AbstractWriter
    {
    public:
        explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter) : outputWriter_(std::move(outputWriter))
        {
            if (!outputWriter_)
            {
                throw std::invalid_argument("Output writer cannot be null");
            }
        }

        ~AbstractFilterWriter() override = default;

        auto write(const char c) -> void override
        {
            if (!outputWriter_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputWriter_->write(c);
        }

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
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

        auto write(const std::vector<char>& cBuf) -> void override
        {
            if (!outputWriter_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputWriter_->write(cBuf);
        }

        auto write(const std::string& str, const size_t off, const size_t len) -> void override
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

        auto write(const std::string& str) -> void override
        {
            if (!outputWriter_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputWriter_->write(str);
        }

        auto flush() -> void override
        {
            if (!outputWriter_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            outputWriter_->flush();
        }

        auto close() -> void override
        {
            if (!outputWriter_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            flush();
            outputWriter_->close();
        }

    protected:
        std::unique_ptr<AbstractWriter> outputWriter_;
    };
}
