#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#include "AbstractWriter.hpp"

namespace common::io
{
    class OutputStreamWriter final : public AbstractWriter
    {
    public:
        OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName):
            outputWriter_(std::move(outputStream)), charset_(charsetName), closed_(false)
        {
            if (charsetName != "UTF-8")
            {
                throw std::invalid_argument("Unsupported encoding: " + charsetName);
            }
        }

        explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream): OutputStreamWriter(
            std::move(outputStream), "UTF-8")
        {
        }

        ~OutputStreamWriter() override = default;

        auto getEncoding() const -> std::string
        {
            return closed_ ? "" : charset_;
        }

        auto write(const char c) -> void override
        {
            write(std::string(1, c));
        }

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
        {
            if (closed_)
            {
                throw std::ios_base::failure("Stream is closed");
            }
            if (off + len > cBuf.size())
            {
                throw std::out_of_range("Offset and length exceed buffer size");
            }
            outputWriter_->write(cBuf, off, len);
            if (!outputWriter_)
            {
                throw std::ios_base::failure("Failed to write to stream");
            }
        }

        auto write(const std::vector<char>& cBuf) -> void override
        {
            write(cBuf, 0, cBuf.size());
        }

        auto write(const std::string& str) -> void override
        {
            write(std::vector<char>(str.begin(), str.end()));
        }

        auto write(const std::string& str, const size_t off, const size_t len) -> void override
        {
            if (off + len > str.size())
            {
                throw std::out_of_range("Offset and length exceed string size");
            }
            write(std::vector(str.begin() + static_cast<std::string::difference_type>(off),
                              str.begin() + static_cast<std::string::difference_type>(off + len)));
        }

        auto flush() -> void override
        {
            if (closed_)
            {
                throw std::ios_base::failure("Stream is closed");
            }
            outputWriter_->flush();
            if (!outputWriter_)
            {
                throw std::ios_base::failure("Failed to flush stream");
            }
        }

        auto close() -> void override
        {
            if (closed_)
            {
                return;
            }
            flush();
            closed_ = true;
        }

        auto append(const char c) -> AbstractWriter& override
        {
            write(c);
            return *this;
        }

        auto append(const std::string& csq) -> AbstractWriter& override
        {
            write(csq);
            return *this;
        }

        auto append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter& override
        {
            write(csq, start, end - start);
            return *this;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            if (closed_)
            {
                throw std::ios_base::failure("Stream is closed");
            }
            return outputWriter_->toString();
        }

    private:
        std::unique_ptr<AbstractWriter> outputWriter_;
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
        std::string charset_;
        bool closed_;
    };
}
