#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#include "AbstractWriter.hpp"

namespace common::io
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
        std::unique_ptr<AbstractWriter> outputWriter_;
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
        std::string charset_;
        bool closed_;
    };

    inline OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName): outputWriter_(std::move(outputStream)), charset_(charsetName), closed_(false)
    {
        if (charsetName != "UTF-8")
        {
            throw std::invalid_argument("Unsupported encoding: " + charsetName);
        }
    }

    inline OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream): OutputStreamWriter(std::move(outputStream), "UTF-8") {}

    inline OutputStreamWriter::~OutputStreamWriter() = default;

    inline auto OutputStreamWriter::getEncoding() const -> std::string
    {
        return closed_ ? "" : charset_;
    }

    inline void OutputStreamWriter::write(const char c)
    {
        write(std::string(1, c));
    }

    inline auto OutputStreamWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
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

    inline void OutputStreamWriter::write(const std::vector<char>& cBuf)
    {
        write(cBuf, 0, cBuf.size());
    }

    inline void OutputStreamWriter::write(const std::string& str)
    {
        write(std::vector<char>(str.begin(), str.end()));
    }

    inline void OutputStreamWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (off + len > str.size())
        {
            throw std::out_of_range("Offset and length exceed string size");
        }
        write(std::vector(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(off + len)));
    }

    inline auto OutputStreamWriter::flush() -> void
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

    inline auto OutputStreamWriter::close() -> void
    {
        if (closed_)
        {
            return;
        }
        flush();
        closed_ = true;
    }

    inline AbstractWriter& OutputStreamWriter::append(const char c)
    {
        write(c);
        return *this;
    }

    inline AbstractWriter& OutputStreamWriter::append(const std::string& csq)
    {
        write(csq);
        return *this;
    }

    inline AbstractWriter& OutputStreamWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        write(csq, start, end - start);
        return *this;
    }

    inline auto OutputStreamWriter::toString() const -> std::string
    {
        if (closed_)
        {
            throw std::ios_base::failure("Stream is closed");
        }
        return outputWriter_->toString();
    }
}
