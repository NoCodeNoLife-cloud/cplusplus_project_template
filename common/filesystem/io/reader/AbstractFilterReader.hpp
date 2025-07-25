#pragma once
#include <memory>

#include "AbstractReader.hpp"

namespace common
{
    class AbstractFilterReader final : public AbstractReader
    {
    public:
        explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader);
        ~AbstractFilterReader() override;
        auto read() -> int32_t override;
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
}
