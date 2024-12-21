#pragma once
#include <memory>
#include <stdexcept>

#include "AbstractReader.hpp"

namespace common::io
{
    class AbstractFilterReader final : public AbstractReader
    {
    public:
        explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader)
        {
            if (!reader_)
            {
                throw std::invalid_argument("Input reader cannot be null");
            }
        }

        ~AbstractFilterReader() override = default;

        auto read() -> int override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return reader_->read();
        }

        auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            if (off + len > cBuf.size())
            {
                return -1;
            }
            return reader_->read(cBuf, off, len);
        }

        auto skip(const size_t n) -> size_t override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return reader_->skip(n);
        }

        [[nodiscard]] auto ready() const -> bool override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return reader_->ready();
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return reader_->markSupported();
        }

        auto mark(const size_t readAheadLimit) -> void override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            reader_->mark(readAheadLimit);
        }

        auto reset() -> void override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            reader_->reset();
        }

        auto close() -> void override
        {
            if (!reader_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            reader_->close();
        }

    protected:
        std::unique_ptr<AbstractReader> reader_;
    };
}
