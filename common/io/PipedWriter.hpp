#pragma once
#include <memory>
#include <mutex>
#include <utility>
#include "AbstractWriter.hpp"
#include "PipedReader.hpp"

namespace common::io
{
    class PipedReader;

    class PipedWriter final : public AbstractWriter
    {
    public:
        PipedWriter() = default;

        explicit PipedWriter(std::shared_ptr<PipedReader> writer) : reader_(std::move(writer))
        {
        }

        ~PipedWriter() override
        {
            close();
        }

        auto close() -> void override
        {
            if (closed_)
            {
                return;
            }
            flush();
            closed_ = true;
            if (reader_)
            {
                reader_->close();
                reader_.reset();
            }
        }

        auto flush() -> void override
        {
            // no-op
        }

        auto write(const char c) -> void override
        {
            std::lock_guard lock(writeMutex_);
            if (closed_)
            {
                throw std::runtime_error("Cannot write to a closed pipe.");
            }
            if (!reader_)
            {
                throw std::runtime_error("Pipe is not connected to a reader.");
            }
            reader_->writeToBuffer(c);
        }

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
        {
            std::lock_guard lock(writeMutex_);
            if (off + len > cBuf.size())
            {
                throw std::out_of_range("Buffer overflow detected in write.");
            }
            if (closed_)
            {
                throw std::runtime_error("Cannot write to a closed pipe.");
            }
            if (!reader_)
            {
                throw std::runtime_error("Pipe is not connected to a reader.");
            }
            for (size_t i = 0; i < len; ++i)
            {
                reader_->writeToBuffer(cBuf[off + i]);
            }
        }

        [[nodiscard]] auto toString() const -> std::string override
        {
            return "";
        }

        auto connect(std::shared_ptr<PipedReader> snk) -> void
        {
            if (reader_ || closed_)
            {
                throw std::runtime_error("Pipe already connected or closed.");
            }
            reader_ = std::move(snk);
        }

    private:
        std::shared_ptr<PipedReader> reader_;
        bool closed_{false};
        std::mutex writeMutex_;
    };
}