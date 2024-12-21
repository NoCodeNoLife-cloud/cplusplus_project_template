#include "PrintStream.hpp"

namespace common::io
{
    PrintStream::PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc): FilterOutputStream(std::move(outStream)), autoFlush_(autoFlush), locale_(loc) {}

    auto PrintStream::append(char c) -> PrintStream&
    {
        write(static_cast<std::byte>(c));
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::append(const std::string& str) -> PrintStream&
    {
        for (char c : str)
        {
            write(static_cast<std::byte>(c));
        }
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::append(const std::string& str, const size_t start, const size_t end) -> PrintStream&
    {
        for (size_t i = start; i < end; i++)
        {
            write(static_cast<std::byte>(str[i]));
        }
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::print(const bool b) const -> void
    {
        if (outputStream_)
        {
            outputStream_->write(static_cast<std::byte>(b ? 1 : 0));
        }
        flushIfNeeded();
    }

    auto PrintStream::print(char c) const -> void
    {
        if (outputStream_)
        {
            outputStream_->write(static_cast<std::byte>(c));
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const int32_t i) const -> void
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

    auto PrintStream::print(const int64_t l) const -> void
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

    auto PrintStream::print(const float f) const -> void
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

    auto PrintStream::print(const double d) const -> void
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

    auto PrintStream::print(const char* s) const -> void
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

    auto PrintStream::print(const std::string& s) const -> void
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

    auto PrintStream::print(const std::vector<char>& v) const -> void
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

    auto PrintStream::println(const bool b) const -> void
    {
        print(b);
        print('\n');
    }

    auto PrintStream::println(const char c) const -> void
    {
        print(c);
        print('\n');
    }

    auto PrintStream::println(const int32_t i) const -> void
    {
        print(i);
        print('\n');
    }

    auto PrintStream::println(const int64_t l) const -> void
    {
        print(l);
        print('\n');
    }

    auto PrintStream::println(const float f) const -> void
    {
        print(f);
        print('\n');
    }

    auto PrintStream::println(const double d) const -> void
    {
        print(d);
        print('\n');
    }

    auto PrintStream::println(const char* s) const -> void
    {
        print(s);
        print('\n');
    }

    auto PrintStream::println(const std::string& s) const -> void
    {
        print(s);
        print('\n');
    }

    auto PrintStream::println(const std::vector<char>& v) const -> void
    {
        print(v);
        print('\n');
    }

    void PrintStream::flush()
    {
        if (outputStream_)
        {
            outputStream_->flush();
        }
    }

    void PrintStream::close()
    {
        if (outputStream_)
        {
            outputStream_->close();
        }
    }

    auto PrintStream::flushIfNeeded() const -> void
    {
        if (autoFlush_ && outputStream_)
        {
            outputStream_->flush();
        }
    }
}
