#pragma once
#include <fstream>
#include <stdexcept>
#include <vector>
#include <glog/logging.h>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
    class BufferedWriter final : public common::io::AbstractWriter,
                                 public common::iface::IfaceAppendable<BufferedWriter>
    {
    public:
        explicit BufferedWriter(std::unique_ptr<std::ofstream> os,
                                const size_t size = DEFAULT_BUFFER_SIZE): outputStream_(std::move(os)),
                                                                          bufferSize_(size)
        {
            if (!outputStream_->is_open())
            {
                throw std::runtime_error("Output stream is not open.");
            }
            buffer_.reserve(size);
        }

        ~BufferedWriter() override
        {
            close();
        }

        auto write(const std::string& str) -> void override
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

        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override
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

        auto newLine() -> BufferedWriter&
        {
            write("\n");
            return *this;
        }

        auto flush() -> void override
        {
            if (!buffer_.empty())
            {
                outputStream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
                buffer_.clear();
            }
        }

        auto close() -> void override
        {
            flush();
            outputStream_->close();
        }

        auto append(const char c) -> BufferedWriter& override
        {
            buffer_.push_back(static_cast<char>(c));
            if (buffer_.size() >= bufferSize_)
            {
                flush();
            }
            return *this;
        }

        auto append(const std::string& str) -> BufferedWriter& override
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

        auto append(const std::string& str, const size_t start, const size_t end) -> BufferedWriter& override
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

        [[nodiscard]] auto toString() const -> std::string override
        {
            std::string str;
            for (const char c : buffer_)
            {
                str.push_back(c);
            }
            return str;
        }

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::unique_ptr<std::ofstream> outputStream_;
        std::vector<char> buffer_;
        size_t bufferSize_;
    };
}
