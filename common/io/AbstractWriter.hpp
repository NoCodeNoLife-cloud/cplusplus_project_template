#pragma once
#include <vector>
#include "interface/IAppendable.hpp"
#include "interface/ICloseable.hpp"
#include "interface/IFlushable.hpp"

namespace common::io
{
    class AbstractWriter : public iface::ICloseable, public iface::IFlushable, iface::IAppendable<AbstractWriter>
    {
    public:
        AbstractWriter();
        ~AbstractWriter() override;
        auto append(char c) -> AbstractWriter& override;
        auto append(const std::string& csq) -> AbstractWriter& override;
        auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;
        virtual auto write(char c) -> void;
        virtual auto write(const std::vector<char>& cBuf) -> void;
        virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;
        virtual auto write(const std::string& str) -> void;
        virtual auto write(const std::string& str, size_t off, size_t len) -> void;
        [[nodiscard]] virtual auto toString() const -> std::string = 0;
    };

    inline AbstractWriter::AbstractWriter() = default;
    inline AbstractWriter::~AbstractWriter() = default;

    inline auto AbstractWriter::append(const char c) -> AbstractWriter&
    {
        write(c);
        return *this;
    }

    inline auto AbstractWriter::append(const std::string& csq) -> AbstractWriter&
    {
        write(csq);
        return *this;
    }

    inline auto AbstractWriter::append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter&
    {
        write(csq, start, end);
        return *this;
    }

    inline auto AbstractWriter::write(const char c) -> void
    {
        const std::vector buf(1, c);
        write(buf, 0, 1);
    }

    inline auto AbstractWriter::write(const std::vector<char>& cBuf) -> void
    {
        write(cBuf, 0, cBuf.size());
    }

    inline auto AbstractWriter::write(const std::string& str) -> void
    {
        write(str, 0, str.size());
    }

    inline auto AbstractWriter::write(const std::string& str, const size_t off, const size_t len) -> void
    {
        if (off < str.size())
        {
            const size_t end = off + len < str.size() ? off + len : str.size();
            const std::vector buf(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(end));
            write(buf, 0, buf.size());
        }
    }
}
