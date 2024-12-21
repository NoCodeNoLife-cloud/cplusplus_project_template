#pragma once
#include "AbstractInputStream.hpp"

namespace common::io
{
    class FilterInputStream : public AbstractInputStream
    {
    public:
        explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream): inputStream_(
            std::move(inputStream))
        {
        }

        ~FilterInputStream() override = default;

        auto available() -> size_t override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return inputStream_->available();
        }

        auto mark(const int readLimit) -> void override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            inputStream_->mark(readLimit);
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            if (!inputStream_)
            {
                return false;
            }
            return inputStream_->markSupported();
        }

        auto read() -> std::byte override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return inputStream_->read();
        }

        size_t read(std::vector<std::byte>& buffer) override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return inputStream_->read(buffer);
        }

        size_t read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return inputStream_->read(buffer, offset, len);
        }

        void reset() override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            inputStream_->reset();
        }

        size_t skip(const size_t n) override
        {
            if (!inputStream_)
            {
                throw std::runtime_error("Input stream is not available");
            }
            return inputStream_->skip(n);
        }

        auto close() -> void override
        {
            inputStream_->close();
        }

    protected:
        std::unique_ptr<AbstractInputStream> inputStream_;
    };
}
