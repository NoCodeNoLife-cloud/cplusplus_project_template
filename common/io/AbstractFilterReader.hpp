#pragma once
#include <memory>
#include <stdexcept>
#include "AbstractReader.hpp"

namespace common::io
{
    class AbstractFilterReader final : public AbstractReader
    {
    public:
        explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader);
        ~AbstractFilterReader() override;
        auto read() -> int override;
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
        auto skip(size_t n) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto mark(size_t readAheadLimit) -> void override;
        auto reset() -> void override;
        auto close() -> void override;
    protected:
        std::unique_ptr<AbstractReader> reader_;
    };

    inline AbstractFilterReader::AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader)
    {
        if (!reader_)
        {
            throw std::invalid_argument("Input reader cannot be null");
        }
        reader_ = std::move(inputReader);
    }

    inline AbstractFilterReader::~AbstractFilterReader() = default;

    inline int AbstractFilterReader::read()
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->read();
    }

    inline auto AbstractFilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
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

    inline size_t AbstractFilterReader::skip(const size_t n)
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->skip(n);
    }

    inline bool AbstractFilterReader::ready() const
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->ready();
    }

    inline bool AbstractFilterReader::markSupported() const
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->markSupported();
    }

    inline auto AbstractFilterReader::mark(const size_t readAheadLimit) -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->mark(readAheadLimit);
    }

    inline auto AbstractFilterReader::reset() -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->reset();
    }

    inline auto AbstractFilterReader::close() -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->close();
    }
}
