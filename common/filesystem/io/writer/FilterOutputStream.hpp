#pragma once
#include "AbstractOutputStream.hpp"
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace fox
{
    /// @brief A filter output stream that wraps another output stream.
    /// @details This class provides a base for output stream filters that modify or enhance
    /// the behavior of the underlying output stream.
    class FilterOutputStream : public AbstractOutputStream
    {
    public:
        /// @brief Constructs a FilterOutputStream that wraps the specified output stream.
        /// @param outputStream The underlying output stream to wrap.
        inline explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream);

        /// @brief Destructor.
        inline ~FilterOutputStream() override = default;

        /// @brief Writes a single byte to the output stream.
        /// @param b The byte to write.
        /// @throws std::runtime_error If the output stream is not available.
        inline auto write(std::byte b) -> void override;

        /// @brief Writes all bytes from the given buffer to the output stream.
        /// @param buffer The buffer containing bytes to write.
        /// @throws std::runtime_error If the output stream is not available.
        inline auto write(const std::vector<std::byte>& buffer) -> void override;

        /// @brief Writes a specified number of bytes from the buffer starting at the given offset.
        /// @param buffer The buffer containing bytes to write.
        /// @param offset The starting position in the buffer.
        /// @param len The number of bytes to write.
        /// @throws std::runtime_error If the output stream is not available.
        /// @throws std::out_of_range If offset + len exceeds buffer size.
        inline auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;

        /// @brief Flushes the output stream, ensuring all buffered data is written.
        /// @throws std::runtime_error If the output stream is not available.
        inline auto flush() -> void override;

        /// @brief Closes the output stream and releases any associated resources.
        /// @throws std::runtime_error If the output stream is not available.
        inline auto close() -> void override;

        /// @brief Checks if the stream is closed.
        /// @return true if the stream is closed, false otherwise.
        inline auto isClosed() const -> bool override;

    protected:
        std::shared_ptr<AbstractOutputStream> output_stream_;
    };

    inline FilterOutputStream::FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream)
        : output_stream_(std::move(outputStream))
    {
    }

    inline auto FilterOutputStream::write(const std::byte b) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->write(b);
    }

    inline auto FilterOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->write(buffer);
    }

    inline auto FilterOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer overflow");
        }
        output_stream_->write(buffer, offset, len);
    }

    inline auto FilterOutputStream::flush() -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        output_stream_->flush();
    }

    inline auto FilterOutputStream::close() -> void
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is not available");
        }
        flush();
        output_stream_->close();
    }

    inline auto FilterOutputStream::isClosed() const -> bool
    {
        // A filter stream is considered closed if the underlying stream is not available
        // or if the underlying stream reports being closed
        return !output_stream_ || output_stream_->isClosed();
    }
}
