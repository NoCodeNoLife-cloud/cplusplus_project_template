#pragma once
#include <memory>
#include "AbstractReader.hpp"

namespace common::io
{
    class FilterReader : public AbstractReader
    {
    public:
        explicit FilterReader(std::shared_ptr<AbstractReader> reader);
        ~FilterReader() override;
        auto close() -> void override;
        auto mark(size_t readAheadLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> int override;
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
        auto read(std::vector<char>& cBuf) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        auto reset() -> void override;
        auto skip(size_t n) -> size_t override;
    protected:
        std::shared_ptr<AbstractReader> in;
    };

    inline FilterReader::FilterReader(std::shared_ptr<AbstractReader> reader): in(std::move(reader)) {}

    inline FilterReader::~FilterReader() = default;

    inline auto FilterReader::close() -> void
    {
        in->close();
    }

    inline auto FilterReader::mark(const size_t readAheadLimit) -> void
    {
        in->mark(readAheadLimit);
    }

    inline bool FilterReader::markSupported() const
    {
        return in->markSupported();
    }

    inline int FilterReader::read()
    {
        return in->read();
    }

    inline auto FilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
    {
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Buffer overflow detected.");
        }
        return in->read(cBuf, off, len);
    }

    inline size_t FilterReader::read(std::vector<char>& cBuf)
    {
        return in->read(cBuf);
    }

    inline bool FilterReader::ready() const
    {
        return in->ready();
    }

    inline auto FilterReader::reset() -> void
    {
        in->reset();
    }

    inline size_t FilterReader::skip(const size_t n)
    {
        return in->skip(n);
    }
}
