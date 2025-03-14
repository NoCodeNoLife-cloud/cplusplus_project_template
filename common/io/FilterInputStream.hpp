#pragma once
#include "AbstractInputStream.hpp"

namespace common::io
{
    class FilterInputStream : public AbstractInputStream
    {
    public:
        explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream);
        ~FilterInputStream() override;
        auto available() -> size_t override;
        auto mark(int32_t readLimit) -> void override;
        [[nodiscard]] auto markSupported() const -> bool override;
        auto read() -> std::byte override;
        size_t read(std::vector<std::byte>& buffer) override;
        size_t read(std::vector<std::byte>& buffer, size_t offset, size_t len) override;
        void reset() override;
        size_t skip(size_t n) override;
        auto close() -> void override;
    protected:
        std::unique_ptr<AbstractInputStream> inputStream_;
    };

    inline FilterInputStream::FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream): inputStream_(std::move(inputStream)) {}

    inline FilterInputStream::~FilterInputStream() = default;

    inline auto FilterInputStream::available() -> size_t
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->available();
    }

    inline void FilterInputStream::mark(const int32_t readLimit)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        inputStream_->mark(readLimit);
    }

    inline bool FilterInputStream::markSupported() const
    {
        if (!inputStream_)
        {
            return false;
        }
        return inputStream_->markSupported();
    }

    inline auto FilterInputStream::read() -> std::byte
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read();
    }

    inline size_t FilterInputStream::read(std::vector<std::byte>& buffer)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read(buffer);
    }

    inline size_t FilterInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->read(buffer, offset, len);
    }

    inline void FilterInputStream::reset()
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        inputStream_->reset();
    }

    inline size_t FilterInputStream::skip(const size_t n)
    {
        if (!inputStream_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return inputStream_->skip(n);
    }

    inline auto FilterInputStream::close() -> void
    {
        inputStream_->close();
    }
}
