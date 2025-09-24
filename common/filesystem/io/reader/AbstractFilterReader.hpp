#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief AbstractFilterReader is a base class that serves as a filter for other readers.
    /// It implements the AbstractReader interface and delegates all operations to an underlying reader.
    /// This class follows the decorator pattern, allowing additional functionality to be added to readers
    /// by wrapping them with filter implementations.
    class AbstractFilterReader : public AbstractReader
    {
    public:
        /// @brief Construct a filter reader with the specified input reader.
        /// @param inputReader The underlying reader to be filtered
        /// @throws std::invalid_argument if inputReader is null
        explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader);

        /// @brief Virtual destructor for proper cleanup of derived classes
        ~AbstractFilterReader() override;

        /// @brief Read a single character.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
        /// or -1 if the end of the stream has been reached
        auto read() -> int override;

        /// @brief Read characters into an array.
        /// @param cBuf Destination buffer.
        /// @param off Offset at which to start storing characters.
        /// @param len Maximum number of characters to read.
        /// @return The number of characters read, or -1 if the end of the stream has been reached.
        /// @pre off + len <= cBuf.size()
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> int override;

        /// @brief Skip characters.
        /// @param n The number of characters to skip.
        /// @return The number of characters actually skipped.
        auto skip(size_t n) -> size_t override;

        /// @brief Tell whether this stream is ready to be read.
        /// @return True if the next read() is guaranteed not to block for input, false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Tell whether this stream supports the mark() operation.
        /// @return True if this stream type supports the mark() operation, false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Mark the present position in the stream.
        /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
        /// @throws std::ios_base::failure if mark is not supported
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Reset the stream to the most recent mark.
        /// @throws std::ios_base::failure if mark has not been called or is not supported
        auto reset() -> void override;

        /// @brief Close the stream.
        /// @throws std::ios_base::failure if an I/O error occurs
        auto close() -> void override;
        auto isClosed() const -> bool override;

    protected:
        std::unique_ptr<AbstractReader> reader_;
    };

    inline AbstractFilterReader::AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader)
    {
        if (!inputReader)
        {
            throw std::invalid_argument("Input reader cannot be null");
        }
        reader_ = std::move(inputReader);
    }

    inline AbstractFilterReader::~AbstractFilterReader() = default;

    inline auto AbstractFilterReader::read() -> int
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->read();
    }

    inline auto AbstractFilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> int
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        if (off + len > cBuf.size())
        {
            return -1;
        }
        return reader_->read(cBuf, off, len);
    }

    inline auto AbstractFilterReader::skip(const size_t n) -> size_t
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->skip(n);
    }

    inline auto AbstractFilterReader::ready() const -> bool
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->ready();
    }

    inline auto AbstractFilterReader::markSupported() const -> bool
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->markSupported();
    }

    inline auto AbstractFilterReader::mark(const size_t readAheadLimit) -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->mark(readAheadLimit);
    }

    inline auto AbstractFilterReader::reset() -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->reset();
    }

    inline auto AbstractFilterReader::close() -> void
    {
        if (!reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        reader_->close();
    }
}
