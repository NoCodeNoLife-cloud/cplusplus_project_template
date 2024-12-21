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
        PipedWriter();
        explicit PipedWriter(std::shared_ptr<PipedReader> writer);
        ~PipedWriter() override;
        auto close() -> void override;
        auto flush() -> void override;
        auto write(char c) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        [[nodiscard]] auto toString() const -> std::string override;
        auto connect(std::shared_ptr<PipedReader> snk) -> void;
    private:
        std::shared_ptr<PipedReader> reader_;
        bool closed_{false};
        std::mutex writeMutex_;
    };

    inline PipedWriter::PipedWriter() = default;

    inline PipedWriter::PipedWriter(std::shared_ptr<PipedReader> writer): reader_(std::move(writer)) {}

    inline PipedWriter::~PipedWriter()
    {
        close();
    }

    inline auto PipedWriter::close() -> void
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

    inline auto PipedWriter::flush() -> void
    {
        // no-op
    }

    inline void PipedWriter::write(const char c)
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

    inline auto PipedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
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

    inline auto PipedWriter::toString() const -> std::string
    {
        return "";
    }

    inline auto PipedWriter::connect(std::shared_ptr<PipedReader> snk) -> void
    {
        if (reader_ || closed_)
        {
            throw std::runtime_error("Pipe already connected or closed.");
        }
        reader_ = std::move(snk);
    }
}
