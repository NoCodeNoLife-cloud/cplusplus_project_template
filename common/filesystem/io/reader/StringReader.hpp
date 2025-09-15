#pragma once
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief A StringReader class that reads data from a string.
    /// @details This class implements the AbstractReader interface to provide functionality
    ///          for reading characters from a string. It supports marking and resetting
    ///          to a previous position in the string.
    class StringReader final : public AbstractReader
    {
    public:
        explicit StringReader(std::string s);
        ~StringReader() override;

        /// @brief Closes the StringReader and releases any associated resources.
        auto close() -> void override;

        /// @brief Marks the current position in the stream.
        /// @param readAheadLimit the maximum number of characters that can be read from the stream before the mark position
        /// becomes invalid.
        auto mark(const size_t readAheadLimit) -> void override;

        /// @brief Tests if this input stream supports the mark and reset methods.
        /// @return true if this stream type supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Reads a single character from the string.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
        ///         or -1 if the end of the string has been reached.
        [[nodiscard]] auto read() -> size_t override;

        /// @brief Reads up to len characters from the string into the buffer cBuf starting at offset off.
        /// @param cBuf The buffer into which the data is read.
        /// @param off The start offset in the buffer at which the data is written.
        /// @param len The maximum number of characters to read.
        /// @return The total number of characters read into the buffer, or -1 if there is no more data because the end of
        /// the string has been reached.
        [[nodiscard]] auto read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t override;

        /// @brief Tests if this input stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input, false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Resets the stream to the most recent mark position.
        auto reset() -> void override;

        /// @brief Skips over and discards n characters from the input stream.
        /// @param ns The number of characters to skip.
        /// @return The actual number of characters skipped.
        auto skip(const size_t ns) -> size_t override;

    private:
        std::string source_;
        size_t position_;
        size_t mark_position_;
        bool mark_set_;
    };

    inline StringReader::StringReader(std::string s)
        : source_(std::move(s)), position_(0), mark_position_(0), mark_set_(false)
    {
    }

    inline StringReader::~StringReader() = default;

    inline auto StringReader::close() -> void
    {
        source_.clear();
        position_ = 0;
        mark_position_ = 0;
        mark_set_ = false;
    }

    inline auto StringReader::mark(const size_t readAheadLimit) -> void
    {
        mark_position_ = std::min(readAheadLimit, source_.size());
        mark_set_ = true;
    }

    inline bool StringReader::markSupported() const
    {
        return true;
    }

    inline size_t StringReader::read()
    {
        if (position_ >= source_.size())
        {
            return static_cast<size_t>(-1); // EOF
        }
        return static_cast<size_t>(static_cast<unsigned char>(source_[position_++]));
    }

    inline auto StringReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::invalid_argument("Offset is out of bounds of the buffer");
        }

        if (position_ >= source_.size())
        {
            return static_cast<size_t>(-1); // EOF
        }

        const size_t maxRead = std::min(len, source_.size() - position_);
        const size_t actualRead = std::min(maxRead, cBuf.size() - off);

        for (size_t i = 0; i < actualRead; ++i)
        {
            if (position_ < source_.size())
            {
                cBuf[off + i] = source_[position_++];
            }
            else
            {
                break;
            }
        }
        return actualRead;
    }

    inline bool StringReader::ready() const
    {
        return position_ < source_.size();
    }

    inline auto StringReader::reset() -> void
    {
        if (!mark_set_)
        {
            position_ = 0;
        }
        else
        {
            position_ = std::min(mark_position_, source_.size());
        }
    }

    inline size_t StringReader::skip(const size_t ns)
    {
        const size_t charsToSkip = std::min(ns, source_.size() - position_);
        position_ += charsToSkip;
        return charsToSkip;
    }
} // namespace fox
