#pragma once
#include <vector>
#include "interface/IfaceAppendable.hpp"
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
    class AbstractWriter : public iface::IfaceCloseable, public iface::IfaceFlushable,
                           iface::IfaceAppendable<AbstractWriter>
    {
    public:
        AbstractWriter() = default;
        ~AbstractWriter() override = default;

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
            write(csq, start, end);
            return *this;
        }

        virtual auto write(const char c) -> void
        {
            const std::vector buf(1, c);
            write(buf, 0, 1);
        }

        virtual auto write(const std::vector<char>& cBuf) -> void
        {
            write(cBuf, 0, cBuf.size());
        }

        virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;

        virtual auto write(const std::string& str) -> void
        {
            write(str, 0, str.size());
        }

        virtual auto write(const std::string& str, const size_t off, const size_t len) -> void
        {
            if (off < str.size())
            {
                const size_t end = off + len < str.size() ? off + len : str.size();
                const std::vector buf(str.begin() + static_cast<std::string::difference_type>(off),
                                      str.begin() + static_cast<std::string::difference_type>(end));
                write(buf, 0, buf.size());
            }
        }

        [[nodiscard]] virtual auto toString() const -> std::string = 0;
    };
}
