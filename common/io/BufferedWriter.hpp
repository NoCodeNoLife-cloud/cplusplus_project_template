#pragma once
#include <fstream>
#include <stdexcept>
#include <vector>
#include <glog/logging.h>
#include "AbstractWriter.hpp"
#include "interface/IAppendable.hpp"

namespace common::io
{
    class BufferedWriter final : public AbstractWriter, public iface::IAppendable<BufferedWriter>
    {
    public:
        explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size = DEFAULT_BUFFER_SIZE);
        ~BufferedWriter() override;
        auto write(const std::string& str) -> void override;
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
        auto newLine() -> BufferedWriter&;
        auto flush() -> void override;
        auto close() -> void override;
        auto append(char c) -> BufferedWriter& override;
        auto append(const std::string& str) -> BufferedWriter& override;
        auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;
        [[nodiscard]] auto toString() const -> std::string override;
    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::unique_ptr<std::ofstream> outputStream_;
        std::vector<char> buffer_;
        size_t bufferSize_;
    };

    inline BufferedWriter::BufferedWriter(std::unique_ptr<std::ofstream> os, const size_t size): outputStream_(std::move(os)), bufferSize_(size)
    {
        if (!outputStream_->is_open())
        {
            throw std::runtime_error("Output stream is not open.");
        }
        buffer_.reserve(size);
    }

    inline BufferedWriter::~BufferedWriter()
    {
        close();
    }

    inline void BufferedWriter::write(const std::string& str)
    {
        if (str.size() > bufferSize_)
        {
            flush();
            *outputStream_ << str;
        }
        else
        {
            for (const char c : str)
            {
                buffer_.push_back(static_cast<char>(c));
            }
            if (buffer_.size() >= bufferSize_)
            {
                flush();
            }
        }
    }

    inline auto BufferedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Offset and length are out of the bounds of the buffer.");
        }
        if (len > bufferSize_)
        {
            flush();
            outputStream_->write(cBuf.data() + off, static_cast<std::streamsize>(len));
        }
        else
        {
            for (size_t i = 0; i < len; ++i)
            {
                buffer_.push_back(cBuf[off + i]);
                if (buffer_.size() >= bufferSize_)
                {
                    flush();
                }
            }
        }
    }

    inline auto BufferedWriter::newLine() -> BufferedWriter&
    {
        write("\n");
        return *this;
    }

    inline auto BufferedWriter::flush() -> void
    {
        if (!buffer_.empty())
        {
            outputStream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
            buffer_.clear();
        }
    }

    inline auto BufferedWriter::close() -> void
    {
        flush();
        outputStream_->close();
    }

    inline BufferedWriter& BufferedWriter::append(const char c)
    {
        buffer_.push_back(static_cast<char>(c));
        if (buffer_.size() >= bufferSize_)
        {
            flush();
        }
        return *this;
    }

    inline BufferedWriter& BufferedWriter::append(const std::string& str)
    {
        for (const char c : str)
        {
            buffer_.push_back(static_cast<char>(c));
            if (buffer_.size() >= bufferSize_)
            {
                flush();
            }
        }
        return *this;
    }

    inline BufferedWriter& BufferedWriter::append(const std::string& str, const size_t start, const size_t end)
    {
        if (start < str.length() && end <= str.length() && start < end)
        {
            for (size_t i = start; i < end; ++i)
            {
                buffer_.push_back(static_cast<char>(str[i]));
                if (buffer_.size() >= bufferSize_)
                {
                    flush();
                }
            }
        }
        return *this;
    }

    inline auto BufferedWriter::toString() const -> std::string
    {
        std::string str;
        for (const char c : buffer_)
        {
            str.push_back(c);
        }
        return str;
    }
}
