#pragma once
#include <stdexcept>
#include "AbstractWriter.hpp"

namespace common::io
{
    class CharArrayWriter final : public AbstractWriter, iface::IAppendable<CharArrayWriter>
    {
    public:
        CharArrayWriter();
        explicit CharArrayWriter(int32_t initialSize);
        ~CharArrayWriter() override;
        void write(char c) override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        void write(const std::string& str, size_t off, size_t len) override;
        auto writeTo(AbstractWriter& out) const -> void;
        CharArrayWriter& append(const std::string& csq) override;
        CharArrayWriter& append(const std::string& csq, size_t start, size_t end) override;
        CharArrayWriter& append(char c) override;
        auto reset() -> void;
        [[nodiscard]] auto toCharArray() const -> std::vector<char>;
        [[nodiscard]] auto size() const -> size_t;
        [[nodiscard]] auto toString() const -> std::string override;
        auto flush() -> void override;
        auto close() -> void override;
    private:
        std::vector<char> buf_;
        size_t count_{0};
    };

    inline CharArrayWriter::CharArrayWriter() = default;

    inline CharArrayWriter::CharArrayWriter(const int32_t initialSize)
    {
        if (initialSize < 0)
        {
            throw std::invalid_argument("initialSize must be non-negative");
        }
        buf_.reserve(initialSize);
    }

    inline CharArrayWriter::~CharArrayWriter() = default;

    inline void CharArrayWriter::write(const char c)
    {
        if (count_ == buf_.size())
        {
            buf_.push_back(c);
        }
        else
        {
            buf_[count_] = c;
        }
        ++count_;
    }

    inline auto CharArrayWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (off + len > static_cast<int32_t>(cBuf.size()))
        {
            throw std::out_of_range("Invalid offset or length");
        }
        if (count_ + len > static_cast<int32_t>(buf_.size()))
        {
            buf_.resize(count_ + len);
        }
        std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    inline void CharArrayWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (off + len > static_cast<int32_t>(str.size()))
        {
            throw std::out_of_range("Invalid offset or length");
        }
        if (count_ + len > static_cast<int32_t>(buf_.size()))
        {
            buf_.resize(count_ + len);
        }
        std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    inline auto CharArrayWriter::writeTo(AbstractWriter& out) const -> void
    {
        out.write(buf_, 0, count_);
    }

    inline CharArrayWriter& CharArrayWriter::append(const std::string& csq)
    {
        write(csq, 0, csq.size());
        return *this;
    }

    inline CharArrayWriter& CharArrayWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        write(csq, start, end - start);
        return *this;
    }

    inline CharArrayWriter& CharArrayWriter::append(const char c)
    {
        write(c);
        return *this;
    }

    inline auto CharArrayWriter::reset() -> void
    {
        count_ = 0;
    }

    inline auto CharArrayWriter::toCharArray() const -> std::vector<char>
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    inline auto CharArrayWriter::size() const -> size_t
    {
        return count_;
    }

    inline auto CharArrayWriter::toString() const -> std::string
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    inline auto CharArrayWriter::flush() -> void
    {
        buf_.clear();
        count_ = 0;
    }

    inline auto CharArrayWriter::close() -> void
    {
        buf_.clear();
        count_ = 0;
    }
}
