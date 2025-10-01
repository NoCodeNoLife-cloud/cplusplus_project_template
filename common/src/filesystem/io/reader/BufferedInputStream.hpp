#pragma once
#include <memory>
#include <vector>

#include "FilterInputStream.hpp"

namespace fox
{
    /// @brief BufferedInputStream is a wrapper around another input stream that provides buffering functionality.
    /// It reads data from the underlying stream in chunks and stores it in an internal buffer to improve performance.
    class BufferedInputStream final : public FilterInputStream
    {
    public:
        explicit BufferedInputStream(std::unique_ptr<AbstractInputStream> in);
        BufferedInputStream(std::unique_ptr<AbstractInputStream> in, size_t size);

        /// @brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking.
        /// @return the number of bytes that can be read (or skipped over) from this input stream without blocking.
        [[nodiscard]] auto available() const -> size_t;

        /// @brief Closes this input stream and releases any system resources associated with the stream.
        auto close() -> void override;

        /// @brief Marks the current position in this input stream.
        /// @param readLimit the maximum limit of bytes that can be read before the mark position becomes invalid.
        auto mark(int32_t readLimit) -> void override;

        /// @brief Tests if this input stream supports the mark and reset methods.
        /// @return true if this stream instance supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reads the next byte of data from this input stream.
        /// @return the next byte of data, or -1 if the end of the stream is reached.
        auto read() -> std::byte override;

        /// @brief Reads up to len bytes of data from this input stream into an array of bytes.
        /// @param buffer the buffer into which the data is read.
        /// @param offset the start offset in the destination array buffer.
        /// @param len the maximum number of bytes to read.
        /// @return the total number of bytes read into the buffer, or 0 if there is no more data because the end of the stream has been reached.
        auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;

        /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
        auto reset() -> void override;

        /// @brief Skips over and discards n bytes of data from this input stream.
        /// @param n the number of bytes to skip.
        /// @return the actual number of bytes skipped.
        auto skip(size_t n) -> size_t override;

        /// @brief Checks if this input stream has been closed.
        /// @return true if this input stream has been closed, false otherwise.
        [[nodiscard]] auto isClosed() const -> bool override;

    protected:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
        std::vector<std::byte> buf_;
        size_t count_{0};
        size_t mark_limit_{0};
        size_t mark_pos_{0};
        size_t pos_{0};
        static auto fillBuffer() -> void;
    };
}
