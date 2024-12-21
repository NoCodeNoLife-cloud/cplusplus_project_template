#pragma once
#include <memory>
#include "AbstractReader.hpp"

namespace common::io
{
    class FilterReader : public AbstractReader
    {
    public:
        explicit FilterReader(std::shared_ptr<AbstractReader> reader): in(std::move(reader))
        {
        }

        ~FilterReader() override = default;

        auto close() -> void override
        {
            in->close();
        }

        auto mark(const size_t readAheadLimit) -> void override
        {
            in->mark(readAheadLimit);
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return in->markSupported();
        }

        auto read() -> int override
        {
            return in->read();
        }

        auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override
        {
            if (off + len > cBuf.size())
            {
                throw std::out_of_range("Buffer overflow detected.");
            }
            return in->read(cBuf, off, len);
        }

        auto read(std::vector<char>& cBuf) -> size_t override
        {
            return in->read(cBuf);
        }

        [[nodiscard]] auto ready() const -> bool override
        {
            return in->ready();
        }

        auto reset() -> void override
        {
            in->reset();
        }

        auto skip(const size_t n) -> size_t override
        {
            return in->skip(n);
        }

    protected:
        std::shared_ptr<AbstractReader> in;
    };
}
