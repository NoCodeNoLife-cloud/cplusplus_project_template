#pragma once
#include <sstream>
#include <vector>
#include "AbstractWriter.hpp"
#include "interface/IAppendable.hpp"

namespace common::io
{
    class StringWriter final : public AbstractWriter, public iface::IAppendable<StringWriter>
    {
    public:
        explicit StringWriter(size_t initialSize);
        ~StringWriter() override;
        auto append(char c) -> StringWriter& override;
        auto append(const std::string& csq) -> StringWriter& override;
        auto append(const std::string& csq, size_t start, size_t end) -> StringWriter& override;
        auto close() -> void override;
        auto flush() -> void override;
        [[nodiscard]] auto getBuffer() const -> std::string;
        [[nodiscard]] auto toString() const -> std::string override;
        auto write(char c) -> void override;
        auto write(const std::string& str) -> void override;
        auto write(const std::string& str, size_t off, size_t len) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
    private:
        std::ostringstream buffer_;
    };

    inline StringWriter::StringWriter(const size_t initialSize)
    {
        buffer_.str(std::string(initialSize, '\0'));
        buffer_.seekp(0);
    }

    inline StringWriter::~StringWriter() = default;

    inline StringWriter& StringWriter::append(const char c)
    {
        buffer_.put(c);
        return *this;
    }

    inline StringWriter& StringWriter::append(const std::string& csq)
    {
        buffer_ << csq;
        return *this;
    }

    inline StringWriter& StringWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        if (start > end || end > csq.size())
        {
            throw std::out_of_range("Invalid start or end position");
        }
        buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
        return *this;
    }

    inline auto StringWriter::close() -> void {}

    inline auto StringWriter::flush() -> void
    {
        buffer_.flush();
    }

    inline auto StringWriter::getBuffer() const -> std::string
    {
        return buffer_.str();
    }

    inline auto StringWriter::toString() const -> std::string
    {
        return buffer_.str();
    }

    inline void StringWriter::write(const char c)
    {
        buffer_.put(c);
    }

    inline void StringWriter::write(const std::string& str)
    {
        buffer_ << str;
    }

    inline void StringWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (off > str.size() || off + len > str.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
    }

    inline auto StringWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
    }
}
