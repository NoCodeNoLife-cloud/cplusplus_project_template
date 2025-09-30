#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>

#include "AbstractWriter.hpp"

namespace fox
{
    /// @brief A class for writing character data to a buffer in memory.
    /// CharArrayWriter is a utility class that allows you to write character data
    /// to an internal buffer. The buffer automatically expands as needed to hold
    /// more data. You can retrieve the contents of the buffer as either a string
    /// or a character array.
    class CharArrayWriter final : public AbstractWriter, IAppendable<CharArrayWriter>
    {
    public:
        /// @brief Constructs a new character array writer with default buffer size.
        CharArrayWriter() = default;

        /// @brief Constructs a new character array writer with the specified initial size.
        /// @param initialSize The initial size of the buffer.
        /// @throws std::invalid_argument if initialSize is negative.
        explicit CharArrayWriter(int32_t initialSize);

        /// @brief Destructor for CharArrayWriter.
        ~CharArrayWriter() override = default;

        // Writer functions
        /// @brief Writes a single character to the buffer.
        /// @param c The character to write.
        auto write(char c) -> void override;

        /// @brief Writes a portion of a character array to the buffer.
        /// @param cBuf The character array to write from.
        /// @param off The offset in the array to start writing from.
        /// @param len The number of characters to write.
        /// @throws std::out_of_range if offset and length are out of the bounds of the buffer.
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

        /// @brief Writes a character array to the buffer.
        /// @param cBuf The character array to write.
        auto write(const std::vector<char>& cBuf) -> void override;

        /// @brief Writes a portion of a string to the buffer.
        /// @param str The string to write from.
        /// @param off The offset in the string to start writing from.
        /// @param len The number of characters to write.
        /// @throws std::out_of_range if offset and length are out of the bounds of the string.
        auto write(const std::string& str, size_t off, size_t len) -> void override;

        /// @brief Writes a string to the buffer.
        /// @param str The string to write.
        auto write(const std::string& str) -> void override;

        /// @brief Writes the contents of this writer to another writer.
        /// @param out The writer to write to.
        auto writeTo(AbstractWriter& out) const -> void;

        // Appendable functions
        /// @brief Appends a single character to the buffer.
        /// @param c The character to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(char c) -> CharArrayWriter& override;

        /// @brief Appends a string to the buffer.
        /// @param csq The string to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(const std::string& csq) -> CharArrayWriter& override;

        /// @brief Appends a subsequence of a string to the buffer.
        /// @param csq The string to append from.
        /// @param start The starting index of the subsequence.
        /// @param end The ending index of the subsequence.
        /// @return A reference to this CharArrayWriter instance.
        auto append(const std::string& csq, size_t start, size_t end) -> CharArrayWriter& override;

        /// @brief Appends a string view to the buffer.
        /// @param str The string view to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(std::string_view str) -> CharArrayWriter& override;

        /// @brief Appends a C-string to the buffer.
        /// @param str The C-string to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(const char* str) -> CharArrayWriter& override;

        /// @brief Appends an initializer list of characters to the buffer.
        /// @param chars The initializer list of characters to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(std::initializer_list<char> chars) -> CharArrayWriter& override;

        /// @brief Appends a sequence of characters to the buffer.
        /// @param chars Pointer to the character sequence.
        /// @param count Number of characters to append.
        /// @return A reference to this CharArrayWriter instance.
        auto append(const char* chars, size_t count) -> CharArrayWriter& override;

        /// @brief Appends a character multiple times to the buffer.
        /// @param c The character to append.
        /// @param count Number of times to append the character.
        /// @return A reference to this CharArrayWriter instance.
        auto append(char c, size_t count) -> CharArrayWriter& override;

        // Utility functions
        /// @brief Resets the buffer to empty.
        auto reset() -> void;

        /// @brief Returns a copy of the buffer's contents as a character array.
        /// @return A vector containing the buffer's contents.
        [[nodiscard]] auto toCharArray() const -> std::vector<char>;

        /// @brief Returns the current size of the buffer.
        /// @return The number of characters in the buffer.
        [[nodiscard]] auto size() const -> size_t;

        /// @brief Returns the buffer's contents as a string.
        /// @return A string representation of the buffer's contents.
        [[nodiscard]] auto toString() const -> std::string override;

        /// @brief Flushes the stream (no-op for this implementation).
        auto flush() -> void override;

        /// @brief Closes the writer (no-op for this implementation).
        auto close() -> void override;

        /// @brief Checks if the writer is closed.
        /// @return Always false for this implementation.
        [[nodiscard]] auto isClosed() const -> bool override;

    private:
        std::vector<char> buf_{};
        size_t count_{0};

        /// @brief Ensures that the buffer has at least the specified capacity.
        /// @param minCapacity The minimum capacity required.
        auto ensureCapacity(size_t minCapacity) -> void;
    };

    inline CharArrayWriter::CharArrayWriter(const int32_t initialSize)
    {
        if (initialSize < 0)
        {
            throw std::invalid_argument("initialSize must be non-negative");
        }
        buf_.reserve(static_cast<size_t>(initialSize));
    }

    inline auto CharArrayWriter::write(const char c) -> void
    {
        ensureCapacity(count_ + 1);
        buf_[count_] = c;
        ++count_;
    }

    inline auto CharArrayWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }

        ensureCapacity(count_ + len);
        std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len,
                    buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    inline auto CharArrayWriter::write(const std::vector<char>& cBuf) -> void
    {
        write(cBuf, 0, cBuf.size());
    }

    inline auto CharArrayWriter::write(const std::string& str, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        if (off + len > str.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }

        ensureCapacity(count_ + len);
        std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len,
                    buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    inline auto CharArrayWriter::write(const std::string& str) -> void
    {
        write(str, 0, str.size());
    }

    inline auto CharArrayWriter::writeTo(AbstractWriter& out) const -> void
    {
        if (count_ > 0)
        {
            out.write(buf_, 0, count_);
        }
    }

    inline auto CharArrayWriter::append(const char c) -> CharArrayWriter&
    {
        write(c);
        return *this;
    }

    inline auto CharArrayWriter::append(const std::string& csq) -> CharArrayWriter&
    {
        write(csq);
        return *this;
    }

    inline auto CharArrayWriter::append(const std::string& csq, const size_t start, const size_t end) -> CharArrayWriter&
    {
        if (start <= end && start <= csq.length())
        {
            const size_t safe_end = std::min(end, csq.length());
            write(csq, start, safe_end - start);
        }
        return *this;
    }

    inline auto CharArrayWriter::append(const std::string_view str) -> CharArrayWriter&
    {
        if (!str.empty())
        {
            write(std::string(str));
        }
        return *this;
    }

    inline auto CharArrayWriter::append(const char* str) -> CharArrayWriter&
    {
        if (str)
        {
            write(std::string(str));
        }
        return *this;
    }

    inline auto CharArrayWriter::append(const std::initializer_list<char> chars) -> CharArrayWriter&
    {
        if (chars.begin() != chars.end()) // Check if initializer_list is not empty
        {
            const auto vec = std::vector(chars);
            write(vec, 0, vec.size());
        }
        return *this;
    }


    inline auto CharArrayWriter::append(const char* chars, const size_t count) -> CharArrayWriter&
    {
        if (chars && count > 0)
        {
            const std::vector vec(chars, chars + count);
            write(vec);
        }
        return *this;
    }

    inline auto CharArrayWriter::append(const char c, const size_t count) -> CharArrayWriter&
    {
        if (count > 0)
        {
            const std::vector buf(count, c);
            write(buf);
        }
        return *this;
    }

    inline auto CharArrayWriter::reset() -> void
    {
        count_ = 0;
    }

    inline auto CharArrayWriter::toCharArray() const -> std::vector<char>
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    inline auto CharArrayWriter::size() const -> size_t
    {
        return count_;
    }

    inline auto CharArrayWriter::toString() const -> std::string
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    inline auto CharArrayWriter::flush() -> void
    {
        // No operation for CharArrayWriter.
    }

    inline auto CharArrayWriter::close() -> void
    {
        // No operation for CharArrayWriter.
    }

    inline auto CharArrayWriter::isClosed() const -> bool
    {
        // CharArrayWriter is never considered closed.
        return false;
    }

    inline auto CharArrayWriter::ensureCapacity(const size_t minCapacity) -> void
    {
        if (minCapacity > buf_.capacity())
        {
            buf_.resize(minCapacity);
        }
    }
}
