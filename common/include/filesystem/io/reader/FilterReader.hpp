#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief A FilterReader is a subclass of AbstractReader that acts as a wrapper for another AbstractReader.
    /// It can be used to extend the functionality of the wrapped reader by overriding methods as needed.
    class FilterReader : public AbstractReader
    {
    public:
        explicit FilterReader(std::shared_ptr<AbstractReader> reader);
        ~FilterReader() override;

        /// @brief Close the stream and release any system resources associated with it.
        auto close() -> void override;

        /// @brief Marks the current position in this input stream.
        /// @param readAheadLimit Limit on the number of bytes that can be read ahead.
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Tests if this input stream supports the mark and reset methods.
        /// @return true if this stream type supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reads the next character from this input stream.
        /// @return The next character from this input stream, or -1 if the end of the stream has been reached.
        auto read() -> int override;

        /// @brief Reads characters into an array of characters.
        /// @param cBuf The buffer into which characters are to be read.
        /// @param off The offset at which to begin storing characters.
        /// @param len The maximum number of characters to read.
        /// @return The number of characters read, or -1 if the end of the stream has been reached.
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> int override;

        /// @brief Reads characters into an array of characters.
        /// @param cBuf The buffer into which characters are to be read.
        /// @return The number of characters read, or -1 if the end of the stream has been reached.
        auto read(std::vector<char>& cBuf) -> int override;

        /// @brief Tests if this input stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input; false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Repositions this stream to the position at the time the mark method was last called on this input stream.
        auto reset() -> void override;

        /// @brief Skips over and discards n bytes of data from this input stream.
        /// @param n The number of characters to skip.
        /// @return The number of characters actually skipped.
        auto skip(size_t n) -> size_t override;

        /// @brief Checks if this reader has been closed.
        /// @return true if this reader has been closed, false otherwise.
        auto isClosed() const -> bool override;

    protected:
        std::shared_ptr<AbstractReader> in_;
    };

    inline FilterReader::FilterReader(std::shared_ptr<AbstractReader> reader) : in_(std::move(reader))
    {
    }

    inline FilterReader::~FilterReader() = default;

    inline auto FilterReader::close() -> void
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        in_->close();
    }

    inline auto FilterReader::mark(const size_t readAheadLimit) -> void
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        in_->mark(readAheadLimit);
    }

    inline bool FilterReader::markSupported() const
    {
        if (!in_)
        {
            return false;
        }
        return in_->markSupported();
    }

    inline int FilterReader::read()
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return in_->read();
    }

    inline auto FilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> int
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer overflow detected.");
        }
        return in_->read(cBuf, off, len);
    }

    inline int FilterReader::read(std::vector<char>& cBuf)
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return in_->read(cBuf);
    }

    inline bool FilterReader::ready() const
    {
        if (!in_)
        {
            return false;
        }
        return in_->ready();
    }

    inline auto FilterReader::reset() -> void
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        in_->reset();
    }

    inline size_t FilterReader::skip(const size_t n)
    {
        if (!in_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return in_->skip(n);
    }

    inline bool FilterReader::isClosed() const
    {
        if (!in_)
        {
            return true;
        }
        return in_->isClosed();
    }
}
