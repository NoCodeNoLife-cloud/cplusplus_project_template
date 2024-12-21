#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
    class ByteArrayOutputStream final : public AbstractOutputStream
    {
    public:
        ByteArrayOutputStream(): buf_(32)
        {
        }

        explicit ByteArrayOutputStream(const size_t size)
        {
            buf_.resize(size);
        }

        auto write(const std::byte b) -> void override
        {
            if (count_ == buf_.size())
            {
                buf_.resize(buf_.size() * 2);
            }
            buf_[count_++] = b;
        }

        auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void override
        {
            if (offset + len > buffer.size())
            {
                throw std::out_of_range("Buffer offset/length out of range");
            }
            if (count_ + len > buf_.size())
            {
                buf_.resize(std::max(buf_.size() * 2, count_ + len));
            }
            std::copy_n(buffer.begin() + static_cast<std::vector<char>::difference_type>(offset), len,
                        buf_.begin() + static_cast<std::vector<char>::difference_type>(count_));
            count_ += len;
        }

        auto writeTo(AbstractOutputStream& out) const -> void
        {
            out.write(buf_, 0, count_);
        }

        auto reset() -> void
        {
            count_ = 0;
        }

        [[nodiscard]] auto toByteArray() const -> std::vector<std::byte>
        {
            return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
        }

        [[nodiscard]] auto size() const -> size_t
        {
            return count_;
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            return {reinterpret_cast<const char*>(buf_.data()), count_};
        }

        auto close() -> void override
        {
        }

        auto flush() -> void override
        {
            // No operation for ByteArrayOutputStream.
        }

    protected:
        std::vector<std::byte> buf_;
        size_t count_{0};
    };
}
