#pragma once
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

#include "FilterOutputStream.hpp"

namespace fox
{
    /// @brief A buffered output stream that writes data to an underlying output stream.
    /// This class buffers the data written to it and flushes it to the underlying stream
    /// when the buffer is full or when explicitly requested.
    class BufferedOutputStream final : public FilterOutputStream
    {
    public:
        explicit BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out);

        BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, const size_t size);

        ~BufferedOutputStream() override;

        /// @brief Writes a single byte to the buffer.
        /// @param b The byte to write.
        auto write(const std::byte b) -> void override;

        /// @brief Writes a sequence of bytes to the buffer.
        /// @param data The data to write.
        /// @param offset The start offset in the data.
        /// @param len The number of bytes to write.
        auto write(const std::vector<std::byte>& data, const size_t offset, const size_t len) -> void override;

        /// @brief Flushes the buffer by writing all buffered bytes to the underlying output stream.
        auto flush() -> void override;

        /// @brief Closes the stream by flushing the buffer and closing the underlying output stream.
        auto close() -> void override;

    protected:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        size_t bufferSize_;
        std::vector<std::byte> buffer_;
        size_t buffer_position_;

        auto flushBuffer() -> void;
    };

    inline BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out) : BufferedOutputStream(
        std::move(out), DEFAULT_BUFFER_SIZE)
    {
    }

    inline BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, const size_t size) :
        FilterOutputStream(std::move(out)), bufferSize_(size), buffer_(size), buffer_position_(0)
    {
        if (!output_stream_)
        {
            throw std::invalid_argument("Output stream cannot be null");
        }
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than 0");
        }
    }

    inline BufferedOutputStream::~BufferedOutputStream()
    {
        try
        {
            flush();
        }
        catch (...)
        {
            // Ignore exceptions during destruction
        }
    }

    inline void BufferedOutputStream::write(const std::byte b)
    {
        if (buffer_position_ >= bufferSize_)
        {
            flushBuffer();
        }
        buffer_[buffer_position_++] = b;
    }

    inline void BufferedOutputStream::write(const std::vector<std::byte>& data, const size_t offset, const size_t len)
    {
        if (len == 0)
        {
            return;
        }

        if (offset + len > data.size())
        {
            throw std::out_of_range("Data offset/length out of range");
        }

        size_t bytesWritten = 0;
        while (bytesWritten < len)
        {
            if (buffer_position_ == bufferSize_)
            {
                flushBuffer();
            }
            const size_t bytesToCopy = std::min(len - bytesWritten, bufferSize_ - buffer_position_);
            std::memcpy(&buffer_[buffer_position_], &data[offset + bytesWritten], bytesToCopy);
            buffer_position_ += bytesToCopy;
            bytesWritten += bytesToCopy;
        }
    }

    inline void BufferedOutputStream::flush()
    {
        flushBuffer();
        output_stream_->flush();
    }

    inline void BufferedOutputStream::close()
    {
        flush();
        output_stream_->close();
    }

    inline auto BufferedOutputStream::flushBuffer() -> void
    {
        if (buffer_position_ > 0 && output_stream_)
        {
            output_stream_->write(buffer_, 0, buffer_position_);
            buffer_position_ = 0;
        }
    }
} // namespace fox
