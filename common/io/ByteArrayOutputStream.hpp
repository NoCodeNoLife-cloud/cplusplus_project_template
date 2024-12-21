#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
    class ByteArrayOutputStream final : public AbstractOutputStream
    {
    public:
        ByteArrayOutputStream();
        explicit ByteArrayOutputStream(size_t size);
        auto write(std::byte b) -> void override;
        auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;
        auto writeTo(AbstractOutputStream& out) const -> void;
        auto reset() -> void;
        [[nodiscard]] auto toByteArray() const -> std::vector<std::byte>;
        [[nodiscard]] auto size() const -> size_t;
        [[nodiscard]] auto toString() const -> std::string;
        auto close() -> void override;
        auto flush() -> void override;
    protected:
        std::vector<std::byte> buf_;
        size_t count_{0};
    };

    inline ByteArrayOutputStream::ByteArrayOutputStream(): buf_(32) {}

    inline ByteArrayOutputStream::ByteArrayOutputStream(const size_t size)
    {
        buf_.resize(size);
    }

    inline auto ByteArrayOutputStream::write(const std::byte b) -> void
    {
        if (count_ == buf_.size())
        {
            buf_.resize(buf_.size() * 2);
        }
        buf_[count_++] = b;
    }

    inline void ByteArrayOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }
        if (count_ + len > buf_.size())
        {
            buf_.resize(std::max(buf_.size() * 2, count_ + len));
        }
        std::copy_n(buffer.begin() + static_cast<std::vector<char>::difference_type>(offset), len, buf_.begin() + static_cast<std::vector<char>::difference_type>(count_));
        count_ += len;
    }

    inline auto ByteArrayOutputStream::writeTo(AbstractOutputStream& out) const -> void
    {
        out.write(buf_, 0, count_);
    }

    inline auto ByteArrayOutputStream::reset() -> void
    {
        count_ = 0;
    }

    inline auto ByteArrayOutputStream::toByteArray() const -> std::vector<std::byte>
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    inline auto ByteArrayOutputStream::size() const -> size_t
    {
        return count_;
    }

    inline auto ByteArrayOutputStream::toString() const -> std::string
    {
        return {reinterpret_cast<const char*>(buf_.data()), count_};
    }

    inline auto ByteArrayOutputStream::close() -> void {}

    inline auto ByteArrayOutputStream::flush() -> void
    {
        // No operation for ByteArrayOutputStream.
    }
}
