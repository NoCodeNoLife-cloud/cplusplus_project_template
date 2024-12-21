#pragma once
#include <sstream>
#include <vector>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
    class StringWriter final : public AbstractWriter, public iface::IfaceAppendable<StringWriter>
    {
    public:
        explicit StringWriter(const size_t initialSize)
        {
            buffer_.str(std::string(initialSize, '\0'));
            buffer_.seekp(0);
        }

        ~StringWriter() override = default;

        auto append(const char c) -> StringWriter& override
        {
            buffer_.put(c);
            return *this;
        }

        auto append(const std::string& csq) -> StringWriter& override
        {
            buffer_ << csq;
            return *this;
        }

        auto append(const std::string& csq, const size_t start, const size_t end) -> StringWriter& override
        {
            if (start > end || end > csq.size())
            {
                throw std::out_of_range("Invalid start or end position");
            }
            buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
            return *this;
        }

        auto close() -> void override
        {
        }

        auto flush() -> void override
        {
            buffer_.flush();
        }

        [[nodiscard]] auto getBuffer() const -> std::string
        {
            return buffer_.str();
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return buffer_.str();
        }

        auto write(const char c) -> void override
        {
            buffer_.put(c);
        }

        auto write(const std::string& str) -> void override
        {
            buffer_ << str;
        }

        auto write(const std::string& str, const size_t off, const size_t len) -> void override
        {
            if (off > str.size() || off + len > str.size())
            {
                throw std::out_of_range("Invalid offset or length");
            }
            buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
        }

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
        {
            if (off > cBuf.size() || len > cBuf.size() - off)
            {
                throw std::out_of_range("Invalid offset or length");
            }
            buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
        }

    private:
        std::ostringstream buffer_;
    };
}
