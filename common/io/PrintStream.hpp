#pragma once
#include "File.hpp"
#include "FilterOutputStream.hpp"
#include "interface/IAppendable.hpp"

namespace common::io
{
    class PrintStream final : public FilterOutputStream, public iface::IAppendable<PrintStream>
    {
    public:
        PrintStream(std::shared_ptr<AbstractOutputStream> outStream, bool autoFlush, const std::locale& loc);
        ~PrintStream() override = delete;
        auto append(char c) -> PrintStream& override;
        auto append(const std::string& str) -> PrintStream& override;
        auto append(const std::string& str, size_t start, size_t end) -> PrintStream& override;
        auto print(bool b) const -> void;
        auto print(char c) const -> void;
        auto print(int32_t i) const -> void;
        auto print(int64_t l) const -> void;
        auto print(float f) const -> void;
        auto print(double d) const -> void;
        auto print(const char* s) const -> void;
        auto print(const std::string& s) const -> void;
        auto print(const std::vector<char>& v) const -> void;
        auto println(bool b) const -> void;
        auto println(char c) const -> void;
        auto println(int32_t i) const -> void;
        auto println(int64_t l) const -> void;
        auto println(float f) const -> void;
        auto println(double d) const -> void;
        auto println(const char* s) const -> void;
        auto println(const std::string& s) const -> void;
        auto println(const std::vector<char>& v) const -> void;
        auto flush() -> void override;
        auto close() -> void override;
    protected:
        bool autoFlush_{false};
        bool errorState_{false};
        std::locale locale_;
        auto flushIfNeeded() const -> void;
    };

    inline PrintStream::PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc): FilterOutputStream(std::move(outStream)), autoFlush_(autoFlush), locale_(loc) {}

    inline auto PrintStream::append(char c) -> PrintStream&
    {
        write(static_cast<std::byte>(c));
        flushIfNeeded();
        return *this;
    }

    inline auto PrintStream::append(const std::string& str) -> PrintStream&
    {
        for (char c : str)
        {
            write(static_cast<std::byte>(c));
        }
        flushIfNeeded();
        return *this;
    }

    inline auto PrintStream::append(const std::string& str, const size_t start, const size_t end) -> PrintStream&
    {
        for (size_t i = start; i < end; i++)
        {
            write(static_cast<std::byte>(str[i]));
        }
        flushIfNeeded();
        return *this;
    }

    inline auto PrintStream::print(const bool b) const -> void
    {
        if (outputStream_)
        {
            outputStream_->write(static_cast<std::byte>(b ? 1 : 0));
        }
        flushIfNeeded();
    }

    inline auto PrintStream::print(char c) const -> void
    {
        if (outputStream_)
        {
            outputStream_->write(static_cast<std::byte>(c));
            flushIfNeeded();
        }
    }

    inline auto PrintStream::print(const int32_t i) const -> void
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

    inline auto PrintStream::print(const int64_t l) const -> void
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

    inline auto PrintStream::print(const float f) const -> void
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

    inline auto PrintStream::print(const double d) const -> void
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

    inline auto PrintStream::print(const char* s) const -> void
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

    inline auto PrintStream::print(const std::string& s) const -> void
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

    inline auto PrintStream::print(const std::vector<char>& v) const -> void
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

    inline auto PrintStream::println(const bool b) const -> void
    {
        print(b);
        print('\n');
    }

    inline auto PrintStream::println(const char c) const -> void
    {
        print(c);
        print('\n');
    }

    inline auto PrintStream::println(const int32_t i) const -> void
    {
        print(i);
        print('\n');
    }

    inline auto PrintStream::println(const int64_t l) const -> void
    {
        print(l);
        print('\n');
    }

    inline auto PrintStream::println(const float f) const -> void
    {
        print(f);
        print('\n');
    }

    inline auto PrintStream::println(const double d) const -> void
    {
        print(d);
        print('\n');
    }

    inline auto PrintStream::println(const char* s) const -> void
    {
        print(s);
        print('\n');
    }

    inline auto PrintStream::println(const std::string& s) const -> void
    {
        print(s);
        print('\n');
    }

    inline auto PrintStream::println(const std::vector<char>& v) const -> void
    {
        print(v);
        print('\n');
    }

    inline void PrintStream::flush()
    {
        if (outputStream_)
        {
            outputStream_->flush();
        }
    }

    inline void PrintStream::close()
    {
        if (outputStream_)
        {
            outputStream_->close();
        }
    }

    inline auto PrintStream::flushIfNeeded() const -> void
    {
        if (autoFlush_ && outputStream_)
        {
            outputStream_->flush();
        }
    }
}
