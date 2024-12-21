#include "PrintStream.hpp"

namespace framework::io {
    PrintStream::PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc) : FilterOutputStream(std::move(outStream)), auto_flush_(autoFlush), locale_(loc) {}

    auto PrintStream::append(char c) -> PrintStream& {
        write(static_cast<std::byte>(c));
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::append(const std::string& str) -> PrintStream& {
        for (char c : str) { write(static_cast<std::byte>(c)); }
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::append(const std::string& str, const size_t start, const size_t end) -> PrintStream& {
        for (size_t i = start; i < end; i++) { write(static_cast<std::byte>(str[i])); }
        flushIfNeeded();
        return *this;
    }

    auto PrintStream::print(const bool b) const -> void {
        if (output_stream_) { output_stream_->write(static_cast<std::byte>(b ? 1 : 0)); }
        flushIfNeeded();
    }

    auto PrintStream::print(char c) const -> void {
        if (output_stream_)
        {
            output_stream_->write(static_cast<std::byte>(c));
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const int32_t i) const -> void {
        if (output_stream_)
        {
            for (const auto buffer = std::to_string(i); char c : buffer) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const int64_t l) const -> void {
        if (output_stream_)
        {
            for (const auto buffer = std::to_string(l); char c : buffer) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const float f) const -> void {
        if (output_stream_)
        {
            for (const auto buffer = std::to_string(f); char c : buffer) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const double d) const -> void {
        if (output_stream_)
        {
            for (const auto buffer = std::to_string(d); char c : buffer) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const char* s) const -> void {
        if (output_stream_ && s)
        {
            while (*s) { output_stream_->write(static_cast<std::byte>(*s++)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const std::string& s) const -> void {
        if (output_stream_)
        {
            for (char c : s) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::print(const std::vector<char>& v) const -> void {
        if (output_stream_)
        {
            for (char c : v) { output_stream_->write(static_cast<std::byte>(c)); }
            flushIfNeeded();
        }
    }

    auto PrintStream::println(const bool b) const -> void {
        print(b);
        print('\n');
    }

    auto PrintStream::println(const char c) const -> void {
        print(c);
        print('\n');
    }

    auto PrintStream::println(const int32_t i) const -> void {
        print(i);
        print('\n');
    }

    auto PrintStream::println(const int64_t l) const -> void {
        print(l);
        print('\n');
    }

    auto PrintStream::println(const float f) const -> void {
        print(f);
        print('\n');
    }

    auto PrintStream::println(const double d) const -> void {
        print(d);
        print('\n');
    }

    auto PrintStream::println(const char* s) const -> void {
        print(s);
        print('\n');
    }

    auto PrintStream::println(const std::string& s) const -> void {
        print(s);
        print('\n');
    }

    auto PrintStream::println(const std::vector<char>& v) const -> void {
        print(v);
        print('\n');
    }

    void PrintStream::flush() { if (output_stream_) { output_stream_->flush(); } }

    void PrintStream::close() { if (output_stream_) { output_stream_->close(); } }

    auto PrintStream::flushIfNeeded() const -> void { if (auto_flush_ && output_stream_) { output_stream_->flush(); } }
} // namespace framework::io
