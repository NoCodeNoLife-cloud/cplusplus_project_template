#include "StringWriter.hpp"

namespace common
{
    StringWriter::StringWriter(const size_t initialSize)
    {
        buffer_.str(std::string(initialSize, '\0'));
        buffer_.seekp(0);
    }

    StringWriter::~StringWriter() = default;

    StringWriter& StringWriter::append(const char c)
    {
        buffer_.put(c);
        return *this;
    }

    StringWriter& StringWriter::append(const std::string& csq)
    {
        buffer_ << csq;
        return *this;
    }

    StringWriter& StringWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        if (start > end || end > csq.size())
        {
            throw std::out_of_range("Invalid start or end position");
        }
        buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
        return *this;
    }

    auto StringWriter::close() -> void
    {
    }

    auto StringWriter::flush() -> void
    {
        buffer_.flush();
    }

    auto StringWriter::getBuffer() const -> std::string
    {
        return buffer_.str();
    }

    auto StringWriter::toString() const -> std::string
    {
        return buffer_.str();
    }

    void StringWriter::write(const char c)
    {
        buffer_.put(c);
    }

    void StringWriter::write(const std::string& str)
    {
        buffer_ << str;
    }

    void StringWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (off > str.size() || off + len > str.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
    }

    auto StringWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
    }
}
