#pragma once
#include <memory>

#include "AbstractReader.hpp"

namespace common
{
    class FilterReader : public AbstractReader
    {
    public:
        explicit FilterReader(std::shared_ptr<AbstractReader> reader);
        ~FilterReader() override;
        auto close() -> void override;
        auto mark(size_t readAheadLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> int32_t override;
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
        auto read(std::vector<char>& cBuf) -> size_t override;
        [[nodiscard]] auto ready() const -> bool override;
        auto reset() -> void override;
        auto skip(size_t n) -> size_t override;

    protected:
        std::shared_ptr<AbstractReader> in_;
    };
}
