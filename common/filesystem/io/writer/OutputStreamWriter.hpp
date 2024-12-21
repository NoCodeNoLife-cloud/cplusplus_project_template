#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <codecvt>

#include "AbstractWriter.hpp"

namespace common
{
    class OutputStreamWriter final : public AbstractWriter
    {
    public:
        OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName);
        explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream);
        ~OutputStreamWriter() override;
        [[nodiscard]] auto getEncoding() const -> std::string;
        auto write(char c) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        auto write(const std::vector<char>& cBuf) -> void override;
        auto write(const std::string& str) -> void override;
        auto write(const std::string& str, size_t off, size_t len) -> void override;
        auto flush() -> void override;
        auto close() -> void override;
        auto append(char c) -> AbstractWriter& override;
        auto append(const std::string& csq) -> AbstractWriter& override;
        auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;
        [[nodiscard]] auto toString() const -> std::string override;

    private:
        std::unique_ptr<AbstractWriter> output_writer_;
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
        std::string charset_;
        bool closed_;
    };
}
