#pragma once
#include <algorithm>
#include <stdexcept>

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
        CharArrayWriter();

        explicit CharArrayWriter(int32_t initialSize);

        ~CharArrayWriter() override;

        /// @brief Writes a single character to the buffer.
        /// @param c The character to write.
        void write(char c) override;

        /// @brief Writes a portion of a character array to the buffer.
        /// @param cBuf The character array to write from.
        /// @param off The offset in the array to start writing from.
        /// @param len The number of characters to write.
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

        /// @brief Writes a portion of a string to the buffer.
        /// @param str The string to write from.
        /// @param off The offset in the string to start writing from.
        /// @param len The number of characters to write.
        void write(const std::string& str, size_t off, size_t len) override;

        /// @brief Writes the contents of this writer to another writer.
        /// @param out The writer to write to.
        auto writeTo(AbstractWriter& out) const -> void;

        /// @brief Appends a string to the buffer.
        /// @param csq The string to append.
        /// @return A reference to this writer.
        CharArrayWriter& append(const std::string& csq) override;

        /// @brief Appends a subsequence of a string to the buffer.
        /// @param csq The string to append from.
        /// @param start The starting index of the subsequence.
        /// @param end The ending index of the subsequence.
        /// @return A reference to this writer.
        CharArrayWriter& append(const std::string& csq, size_t start, size_t end) override;

        /// @brief Appends a single character to the buffer.
        /// @param c The character to append.
        /// @return A reference to this writer.
        CharArrayWriter& append(char c) override;

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

    private:
        std::vector<char> buf_;
        size_t count_{0};

        /// @brief Ensures that the buffer has at least the specified capacity.
        /// @param minCapacity The minimum capacity required.
        auto ensureCapacity(size_t minCapacity) -> void;
    };

    inline CharArrayWriter::CharArrayWriter() = default;

    inline CharArrayWriter::CharArrayWriter(const int32_t initialSize)
    {
        if (initialSize < 0)
        {
            throw std::invalid_argument("initialSize must be non-negative");
        }
        buf_.reserve(static_cast<size_t>(initialSize));
    }

    inline CharArrayWriter::~CharArrayWriter() = default;

    inline void CharArrayWriter::write(const char c)
    {
        if (count_ == buf_.size())
        {
            buf_.push_back(c);
        }
        else
        {
            buf_[count_] = c;
        }
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

    inline void CharArrayWriter::write(const std::string& str, const size_t off, const size_t len)
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

    inline auto CharArrayWriter::writeTo(AbstractWriter& out) const -> void
    {
        if (count_ > 0)
        {
            out.write(buf_, 0, count_);
        }
    }

    inline CharArrayWriter& CharArrayWriter::append(const std::string& csq)
    {
        write(csq);
        return *this;
    }

    inline CharArrayWriter& CharArrayWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        if (start <= end && start <= csq.length())
        {
            const size_t safe_end = std::min(end, csq.length());
            write(csq, start, safe_end - start);
        }
        return *this;
    }

    inline CharArrayWriter& CharArrayWriter::append(const char c)
    {
        write(c);
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
        buf_.clear();
        count_ = 0;
    }

    inline auto CharArrayWriter::close() -> void
    {
        buf_.clear();
        count_ = 0;
    }

    inline auto CharArrayWriter::ensureCapacity(size_t minCapacity) -> void
    {
        if (minCapacity > buf_.size())
        {
            buf_.resize(minCapacity);
        }
    }
} // namespace fox
