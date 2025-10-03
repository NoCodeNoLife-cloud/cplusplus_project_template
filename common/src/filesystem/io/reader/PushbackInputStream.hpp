#pragma once
#include "FilterInputStream.hpp"

namespace common
{
    /// @brief A pushback input stream allows bytes to be pushed back into the stream.
    /// This class wraps another input stream and provides the ability to "unread" bytes,
    /// making them available to be read again. This is useful for parsers that need to
    /// look ahead in the input stream.
    class PushbackInputStream final : public FilterInputStream
    {
    public:
        PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, size_t bufferSize);
        ~PushbackInputStream() override;

        /// @brief Returns the number of bytes that can be read from this input stream without blocking.
        /// @return the number of bytes that can be read from this input stream without blocking.
        auto available() -> size_t override;

        /// @brief Reads the next byte of data from the input stream.
        /// @return the next byte of data, or -1 if the end of the stream is reached.
        auto read() -> std::byte override;

        /// @brief Reads up to `buffer.size()` bytes of data from the input stream into the buffer.
        /// @param buffer the buffer into which the data is read.
        /// @return the total number of bytes read into the buffer, or 0 if there is no more data because the end of the
        /// stream has been reached.
        auto read(std::vector<std::byte>& buffer) -> size_t override;

        /// @brief Reads up to `len` bytes of data from the input stream into the buffer starting at `offset`.
        /// @param buffer the buffer into which the data is read.
        /// @param offset the start offset in the buffer at which the data is written.
        /// @param len the maximum number of bytes to read.
        /// @return the total number of bytes read into the buffer, or 0 if there is no more data because the end of the
        /// stream has been reached.
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;

        /// @brief Pushes back the entire buffer into the stream.
        /// @param buffer the buffer to push back.
        void unread(const std::vector<std::byte>& buffer);

        /// @brief Pushes back a portion of the buffer into the stream.
        /// @param buffer the buffer containing data to push back.
        /// @param offset the start offset in the buffer from which data is pushed back.
        /// @param len the number of bytes to push back.
        void unread(const std::vector<std::byte>& buffer, size_t offset, size_t len);

        /// @brief Pushes back a single byte into the stream.
        /// @param b the byte to push back.
        void unread(std::byte b);

        /// @brief Checks if this input stream has been closed.
        /// @return true if this input stream has been closed, false otherwise.
        [[nodiscard]] auto isClosed() const -> bool override;

    private:
        std::vector<std::byte> pushback_buffer_;
        size_t buffer_pos_{0};
    };
}
