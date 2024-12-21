#pragma once
#include <stdexcept>
#include "AbstractWriter.hpp"

namespace common::io
{
    class CharArrayWriter final : public AbstractWriter, iface::IfaceAppendable<CharArrayWriter>
    {
    public:
        CharArrayWriter() = default;

        explicit CharArrayWriter(const int initialSize)
        {
            if (initialSize < 0)
            {
                throw std::invalid_argument("initialSize must be non-negative");
            }
            buf_.reserve(initialSize);
        }

        ~CharArrayWriter() override = default;

        void write(const char c) override
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

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
        {
            if (off + len > static_cast<int>(cBuf.size()))
            {
                throw std::out_of_range("Invalid offset or length");
            }
            if (count_ + len > static_cast<int>(buf_.size()))
            {
                buf_.resize(count_ + len);
            }
            std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len,
                        buf_.begin() + static_cast<std::ptrdiff_t>(count_));
            count_ += len;
        }

        void write(const std::string& str, const size_t off, const size_t len) override
        {
            if (off + len > static_cast<int>(str.size()))
            {
                throw std::out_of_range("Invalid offset or length");
            }
            if (count_ + len > static_cast<int>(buf_.size()))
            {
                buf_.resize(count_ + len);
            }
            std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len,
                        buf_.begin() + static_cast<std::ptrdiff_t>(count_));
            count_ += len;
        }

        auto writeTo(AbstractWriter& out) const -> void
        {
            out.write(buf_, 0, count_);
        }

        CharArrayWriter& append(const std::string& csq) override
        {
            write(csq, 0, csq.size());
            return *this;
        }

        CharArrayWriter& append(const std::string& csq, const size_t start, const size_t end) override
        {
            write(csq, start, end - start);
            return *this;
        }

        CharArrayWriter& append(const char c) override
        {
            write(c);
            return *this;
        }

        auto reset() -> void
        {
            count_ = 0;
        }

        [[nodiscard]] auto toCharArray() const -> std::vector<char>
        {
            return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
        }

        [[nodiscard]] auto size() const -> size_t
        {
            return count_;
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
        }

        auto flush() -> void override
        {
            buf_.clear();
            count_ = 0;
        }

        auto close() -> void override
        {
            buf_.clear();
            count_ = 0;
        }

    private:
        std::vector<char> buf_;
        size_t count_{0};
    };
}
