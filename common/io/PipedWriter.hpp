#pragma once
#include <memory>
#include <mutex>
#include "AbstractWriter.hpp"
#include "PipedReader.hpp"

namespace common::io
{
    class PipedReader;

    class PipedWriter final : public AbstractWriter
    {
    public:
        PipedWriter();
        explicit PipedWriter(std::shared_ptr<PipedReader> writer);
        ~PipedWriter() override;
        auto close() -> void override;
        auto flush() -> void override;
        auto write(char c) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        [[nodiscard]] auto toString() const -> std::string override;
        auto connect(std::shared_ptr<PipedReader> snk) -> void;
    private:
        std::shared_ptr<PipedReader> reader_;
        bool closed_{false};
        std::mutex writeMutex_;
    };
}
