#pragma once
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

#include "filesystem/io/interface/ICloseable.hpp"

namespace fox
{
    /// @brief Abstract base class for all input streams.
    /// Provides standard input stream functionality that can be extended by concrete implementations.
    class AbstractInputStream : public ICloseable
    {
    public:
        ~AbstractInputStream() override;

        /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking.
        /// @return The number of bytes that can be read without blocking.
        [[nodiscard]] virtual auto available() -> size_t = 0;

        /// @brief Marks the current position in this input stream.
        /// @param readLimit The maximum limit of bytes that can be read before the mark position becomes invalid.
        virtual auto mark(int32_t readLimit) -> void;

        /// @brief Tells whether this stream supports the mark() operation.
        /// @return true if this stream supports the mark operation, false otherwise.
        [[nodiscard]] virtual auto markSupported() const -> bool;

        /// @brief Reads the next byte of data from the input stream.
        /// @return The next byte of data, or -1 if the end of the stream is reached.
        virtual auto read() -> std::byte = 0;

        /// @brief Reads up to len bytes of data from the input stream into an array of bytes.
        /// @param buffer The buffer into which the data is read.
        /// @return The total number of bytes read into the buffer, or 0 if there is no more data.
        virtual auto read(std::vector<std::byte>& buffer) -> size_t;

        /// @brief Reads up to len bytes of data from the input stream into an array of bytes.
        /// @param buffer The buffer into which the data is read.
        /// @param offset The start offset in the destination array buffer.
        /// @param len The maximum number of bytes to read.
        /// @return The total number of bytes read into the buffer, or 0 if there is no more data.
        virtual auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t;

        /// @brief Repositions this stream to the position at the time the mark() method was last called.
        virtual auto reset() -> void;

        /// @brief Skips over and discards n bytes of data from this input stream.
        /// @param n The number of bytes to skip.
        /// @return The actual number of bytes skipped.
        virtual auto skip(size_t n) -> size_t;
    };

    inline AbstractInputStream::~AbstractInputStream() = default;

    inline auto AbstractInputStream::mark(int32_t readLimit) -> void
    {
        throw std::runtime_error("mark not supported");
    }

    inline auto AbstractInputStream::markSupported() const -> bool
    {
        return false;
    }

    inline auto AbstractInputStream::read(std::vector<std::byte>& buffer) -> size_t
    {
        return read(buffer, 0, buffer.size());
    }

    inline auto AbstractInputStream::read(std::vector<std::byte>& buffer, const size_t offset,
                                          const size_t len) -> size_t
    {
        // Check for buffer overflow
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::out_of_range("Buffer offset/length out of range");
        }

        size_t bytesRead = 0;
        for (size_t i = 0; i < len; ++i)
        {
            const std::byte byte = read();
            // Check for end of stream
            if (static_cast<int>(byte) == -1)
            {
                break;
            }
            buffer[offset + i] = byte;
            ++bytesRead;
        }
        return bytesRead;
    }

    inline auto AbstractInputStream::reset() -> void
    {
        throw std::runtime_error("reset not supported");
    }

    inline auto AbstractInputStream::skip(const size_t n) -> size_t
    {
        size_t skipped = 0;
        // Prevent potential overflow
        const size_t maxSkip = std::min(n, static_cast<size_t>(std::numeric_limits<int>::max()));

        for (size_t i = 0; i < maxSkip; ++i)
        {
            if (static_cast<int>(read()) == -1)
            {
                break;
            }
            ++skipped;
        }
        return skipped;
    }
}
