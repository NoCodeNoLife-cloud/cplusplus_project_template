#pragma once
#include "File.hpp"
#include "FilterOutputStream.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
    class PrintStream final : public FilterOutputStream, public iface::IfaceAppendable<PrintStream>
    {
    public:
        PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc):
            FilterOutputStream(std::move(outStream)), autoFlush_(autoFlush), locale_(loc)
        {
        }

        ~PrintStream() override = delete;

        auto append(char c) -> PrintStream& override
        {
            write(static_cast<std::byte>(c));
            flushIfNeeded();
            return *this;
        }

        auto append(const std::string& str) -> PrintStream& override
        {
            for (char c : str)
            {
                write(static_cast<std::byte>(c));
            }
            flushIfNeeded();
            return *this;
        }

        auto append(const std::string& str, size_t start, size_t end) -> PrintStream& override
        {
            for (size_t i = start; i < end; i++)
            {
                write(static_cast<std::byte>(str[i]));
            }
            flushIfNeeded();
            return *this;
        }

        auto print(const bool b) const -> void
        {
            if (outputStream_)
            {
                outputStream_->write(static_cast<std::byte>(b ? 1 : 0));
            }
            flushIfNeeded();
        }

        auto print(char c) const -> void
        {
            if (outputStream_)
            {
                outputStream_->write(static_cast<std::byte>(c));
                flushIfNeeded();
            }
        }

        auto print(const int i) const -> void
        {
            if (outputStream_)
            {
                for (const auto buffer = std::to_string(i); char c : buffer)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto print(const long l) const -> void
        {
            if (outputStream_)
            {
                for (const auto buffer = std::to_string(l); char c : buffer)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto print(const float f) const -> void
        {
            if (outputStream_)
            {
                for (const auto buffer = std::to_string(f); char c : buffer)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto print(const double d) const -> void
        {
            if (outputStream_)
            {
                for (const auto buffer = std::to_string(d); char c : buffer)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto print(const char* s) const -> void
        {
            if (outputStream_ && s)
            {
                while (*s)
                {
                    outputStream_->write(static_cast<std::byte>(*s++));
                }
                flushIfNeeded();
            }
        }

        auto print(const std::string& s) const -> void
        {
            if (outputStream_)
            {
                for (char c : s)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto print(const std::vector<char>& v) const -> void
        {
            if (outputStream_)
            {
                for (char c : v)
                {
                    outputStream_->write(static_cast<std::byte>(c));
                }
                flushIfNeeded();
            }
        }

        auto println(const bool b) const -> void
        {
            print(b);
            print('\n');
        }

        auto println(const char c) const -> void
        {
            print(c);
            print('\n');
        }

        auto println(const int i) const -> void
        {
            print(i);
            print('\n');
        }

        auto println(long l) const -> void
        {
            print(l);
            print('\n');
        }

        auto println(float f) const -> void
        {
            print(f);
            print('\n');
        }

        auto println(double d) const -> void
        {
            print(d);
            print('\n');
        }

        auto println(const char* s) const -> void
        {
            print(s);
            print('\n');
        }

        auto println(const std::string& s) const -> void
        {
            print(s);
            print('\n');
        }

        auto println(const std::vector<char>& v) const -> void
        {
            print(v);
            print('\n');
        }

        auto flush() -> void override
        {
            if (outputStream_)
            {
                outputStream_->flush();
            }
        }

        auto close() -> void override
        {
            if (outputStream_)
            {
                outputStream_->close();
            }
        }

    protected:
        bool autoFlush_{false};
        bool errorState_{false};
        std::locale locale_;

        auto flushIfNeeded() const -> void
        {
            if (autoFlush_ && outputStream_)
            {
                outputStream_->flush();
            }
        }
    };
}
