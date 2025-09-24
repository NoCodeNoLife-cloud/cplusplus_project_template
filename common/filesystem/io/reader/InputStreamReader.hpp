#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING // NOLINT(*-reserved-identifier)
#include <algorithm>
#include <codecvt>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractReader.hpp"

namespace fox
{
    /// @brief InputStreamReader is a class for reading characters from a byte stream.
    /// This class inherits from AbstractReader and provides functionality to read characters
    /// from an input stream with specified charset encoding.
    class InputStreamReader final : public AbstractReader
    {
    public:
        explicit InputStreamReader(std::shared_ptr<AbstractReader> input);
        InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName);
        ~InputStreamReader() override;

        /// @brief Read a single character.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff),
        ///         or -1 if the end of the stream has been reached
        auto read() -> int override;

        /// @brief Read characters into an array.
        /// @param cBuf Destination buffer
        /// @param off Offset at which to start storing characters
        /// @param len Maximum number of characters to read
        /// @return The number of characters read, or -1 if the end of the stream has been reached
        auto read(std::vector<char>& cBuf, size_t off, size_t len) -> int override;

        /// @brief Tests if this input stream is ready to be read.
        /// @return true if the next read() is guaranteed not to block for input, false otherwise.
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Close the stream.
        auto close() -> void override;

        /// @brief Tests if this stream supports the mark and reset methods.
        /// @return true if this stream type supports the mark and reset methods; false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Marks the current position in the stream.
        /// @param readAheadLimit the maximum limit of bytes that can be read before the mark position becomes invalid.
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Resets the stream to the most recent mark.
        auto reset() -> void override;

        /// @brief Checks if this reader has been closed.
        /// @return true if this reader has been closed, false otherwise.
        auto isClosed() const -> bool override;

    private:
        std::shared_ptr<AbstractReader> reader_;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
        bool closed_{false};
    };

    inline InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input) : reader_(std::move(input))
    {
        if (!reader_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
    }

    inline InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName)
        : reader_(std::move(input))
    {
        if (!reader_)
        {
            throw std::invalid_argument("Input stream cannot be null");
        }
        if (charsetName != "UTF-8")
        {
            throw std::invalid_argument("Only UTF-8 charset is supported in this implementation");
        }
    }

    inline InputStreamReader::~InputStreamReader() = default;

    inline int InputStreamReader::read()
    {
        if (closed_ || !reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }

        // UTF-8 character can be 1-4 bytes, read one byte at a time to determine character boundaries
        std::vector<char> byteBuffer(1);
        const int firstByte = reader_->read();
        if (firstByte == -1)
        {
            return -1;
        }

        byteBuffer[0] = static_cast<char>(firstByte);

        // Determine how many additional bytes we need based on the first byte
        int additionalBytes = 0;
        const unsigned char firstByteUnsigned = static_cast<unsigned char>(firstByte);
        if ((firstByteUnsigned & 0x80) == 0)
        {
            // ASCII character (0xxxxxxx)
            additionalBytes = 0;
        }
        else if ((firstByteUnsigned & 0xE0) == 0xC0)
        {
            // 2-byte character (110xxxxx 10xxxxxx)
            additionalBytes = 1;
        }
        else if ((firstByteUnsigned & 0xF0) == 0xE0)
        {
            // 3-byte character (1110xxxx 10xxxxxx 10xxxxxx)
            additionalBytes = 2;
        }
        else if ((firstByteUnsigned & 0xF8) == 0xF0)
        {
            // 4-byte character (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
            additionalBytes = 3;
        }
        else
        {
            // Invalid UTF-8 first byte
            throw std::runtime_error("Invalid UTF-8 sequence");
        }

        // Read additional bytes if needed
        std::vector<char> fullByteBuffer(1 + additionalBytes);
        fullByteBuffer[0] = byteBuffer[0];

        for (int i = 0; i < additionalBytes; ++i)
        {
            const int nextByte = reader_->read();
            if (nextByte == -1)
            {
                throw std::runtime_error("Incomplete UTF-8 sequence");
            }
            const unsigned char nextByteUnsigned = static_cast<unsigned char>(nextByte);
            if ((nextByteUnsigned & 0xC0) != 0x80)
            {
                throw std::runtime_error("Invalid UTF-8 sequence");
            }
            fullByteBuffer[1 + i] = static_cast<char>(nextByte);
        }

        try
        {
            const std::string byteStr(fullByteBuffer.data(), fullByteBuffer.size());
            const std::u32string chars = converter_.from_bytes(byteStr);
            if (chars.empty())
            {
                return -1;
            }
            return static_cast<unsigned char>(chars[0]);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Failed to decode byte to character");
        }
    }

    inline auto InputStreamReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> int
    {
        if (closed_ || !reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Buffer overflow");
        }

        if (len == 0)
        {
            return 0;
        }

        // For simplicity, read one character at a time
        // A more optimized implementation would read multiple bytes and decode them together
        size_t totalCharsRead = 0;
        for (size_t i = 0; i < len; ++i)
        {
            const int ch = read();
            if (ch == -1)
            {
                return totalCharsRead > 0 ? static_cast<int>(totalCharsRead) : -1;
            }
            cBuf[off + i] = static_cast<char>(ch);
            ++totalCharsRead;
        }

        return static_cast<int>(totalCharsRead);
    }

    inline bool InputStreamReader::ready() const
    {
        if (closed_ || !reader_)
        {
            throw std::runtime_error("Input stream is not available");
        }
        return reader_->ready();
    }

    inline auto InputStreamReader::close() -> void
    {
        closed_ = true;
        if (reader_)
        {
            reader_->close();
        }
    }

    inline bool InputStreamReader::markSupported() const
    {
        return false;
    }

    inline auto InputStreamReader::mark(const size_t readAheadLimit) -> void
    {
        static_cast<void>(readAheadLimit); // Unused parameter
        throw std::runtime_error("Mark not supported");
    }

    inline auto InputStreamReader::reset() -> void
    {
        throw std::runtime_error("Reset not supported");
    }

    inline bool InputStreamReader::isClosed() const
    {
        return closed_ || !reader_ || reader_->isClosed();
    }
}
