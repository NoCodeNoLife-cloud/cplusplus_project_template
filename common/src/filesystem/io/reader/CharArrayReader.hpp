#pragma once
#include "AbstractReader.hpp"

namespace fox
{
    /// @brief A reader class that reads from a character array.
    /// This class provides methods to read characters from an internal buffer,
    /// supporting operations like reading single characters, skipping characters,
    /// marking positions in the stream, and resetting to marked positions.
    class CharArrayReader final : public AbstractReader
    {
    public:
        explicit CharArrayReader(const std::vector<char>& buffer);
        CharArrayReader(const std::vector<char>& buffer, size_t offset, size_t length);
        ~CharArrayReader() override;

        /// @brief Reads a single character.
        /// @return The character read, as an integer in the range 0 to 65535 (0x00-0xffff), or -1 if the end of the stream
        /// has been reached
        auto read() -> int override;

        /// @brief Reads characters into an array.
        /// @param b The buffer into which the read characters are stored
        /// @param off The offset at which to store the characters
        /// @param len The maximum number of characters to read
        /// @return The number of characters read, or -1 if the end of the stream has been reached
        auto read(std::vector<char>& b, size_t off, size_t len) -> int override;

        /// @brief Skips characters.
        /// @param n The number of characters to skip
        /// @return The number of characters actually skipped
        auto skip(size_t n) -> size_t override;

        /// @brief Tests if this reader can be read without blocking.
        /// @return True if this reader can be read without blocking, false otherwise
        [[nodiscard]] auto ready() const -> bool override;

        /// @brief Tests if this reader supports the mark() operation.
        /// @return True if this reader supports the mark() operation, false otherwise
        [[nodiscard]] auto markSupported() const -> bool override;

        /// @brief Marks the present position in the stream.
        /// @param readAheadLimit Limit on the number of characters that may be read while still preserving the mark.
        auto mark(size_t readAheadLimit) -> void override;

        /// @brief Resets the stream to the most recent mark.
        auto reset() -> void override;

        /// @brief Closes the stream and releases any system resources associated with it.
        auto close() -> void override;

        /// @brief Checks if this reader has been closed.
        /// @return true if this reader has been closed, false otherwise.
        [[nodiscard]] auto isClosed() const -> bool override;

    private:
        std::vector<char> buf_;
        size_t pos_{0};
        size_t marked_pos_{0};
        size_t count_{0};
        bool closed_{false};
    };
}
