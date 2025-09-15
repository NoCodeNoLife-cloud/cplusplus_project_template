#pragma once
#include "AbstractOutputStream.hpp"

namespace fox
{
    /// @brief A filter output stream that wraps another output stream.
    /// This class provides a base for output stream filters that modify or enhance
    /// the behavior of the underlying output stream.
    class FilterOutputStream : public AbstractOutputStream
    {
    public:
        explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream)
            : output_stream_(std::move(outputStream))
        {
        }

        ~FilterOutputStream() override = default;

        /// @brief Writes a single byte to the output stream.
        /// @param b The byte to write.
        auto write(const std::byte b) -> void override
        {
            if (!output_stream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            output_stream_->write(b);
        }

        /// @brief Writes all bytes from the given buffer to the output stream.
        /// @param buffer The buffer containing bytes to write.
        auto write(const std::vector<std::byte>& buffer) -> void override
        {
            if (!output_stream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            output_stream_->write(buffer);
        }

        /// @brief Writes a specified number of bytes from the buffer starting at the given offset.
        /// @param buffer The buffer containing bytes to write.
        /// @param offset The starting position in the buffer.
        /// @param len The number of bytes to write.
        auto write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void override
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

        /// @brief Flushes the output stream, ensuring all buffered data is written.
        auto flush() -> void override
        {
            if (!output_stream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            output_stream_->flush();
        }

        /// @brief Closes the output stream and releases any associated resources.
        auto close() -> void override
        {
            if (!output_stream_)
            {
                throw std::runtime_error("Output stream is not available");
            }
            flush();
            output_stream_->close();
        }

    protected:
        std::shared_ptr<AbstractOutputStream> output_stream_;
    };
} // namespace fox
