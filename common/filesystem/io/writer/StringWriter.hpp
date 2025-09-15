#pragma once
#include <sstream>
#include <vector>

#include "AbstractWriter.hpp"

namespace fox
{
    /// @brief A writer that writes data to an in-memory string buffer.
    /// This class provides functionality to write characters and strings to an internal
    /// string buffer, which can then be retrieved as a string.
    class StringWriter final : public AbstractWriter, public IAppendable<StringWriter>
    {
    public:
        explicit StringWriter(const size_t initialSize);
        ~StringWriter() override;

        /// @brief Appends the specified character to this writer.
        /// @param c The character to append.
        /// @return A reference to this StringWriter.
        auto append(const char c) -> StringWriter& override;

        /// @brief Appends the specified string to this writer.
        /// @param csq The string to append.
        /// @return A reference to this StringWriter.
        auto append(const std::string& csq) -> StringWriter& override;

        /// @brief Appends a subsequence of the specified string to this writer.
        /// @param csq The string from which a subsequence is appended.
        /// @param start The starting index of the subsequence.
        /// @param end The ending index of the subsequence.
        /// @return A reference to this StringWriter.
        auto append(const std::string& csq, const size_t start, const size_t end) -> StringWriter& override;

        /// @brief Closes the writer and releases any associated resources.
        auto close() -> void override;

        /// @brief Flushes the writer, ensuring all buffered data is written.
        auto flush() -> void override;

        /// @brief Gets the current buffer content as a string.
        /// @return The buffer content.
        [[nodiscard]] auto getBuffer() const -> std::string;

        /// @brief Converts the buffer content to a string representation.
        /// @return The string representation of the buffer.
        [[nodiscard]] auto toString() const -> std::string override;

        /// @brief Writes a single character to the writer.
        /// @param c The character to write.
        auto write(const char c) -> void override;

        /// @brief Writes the specified string to the writer.
        /// @param str The string to write.
        auto write(const std::string& str) -> void override;

        /// @brief Writes a portion of the specified string to the writer.
        /// @param str The string to write.
        /// @param off The offset from which to start writing.
        /// @param len The number of characters to write.
        auto write(const std::string& str, const size_t off, const size_t len) -> void override;

        /// @brief Writes a portion of the specified character array to the writer.
        /// @param cBuf The character array to write.
        /// @param off The offset from which to start writing.
        /// @param len The number of characters to write.
        auto write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void override;

    private:
        std::ostringstream buffer_;
    };

    inline StringWriter::StringWriter(const size_t initialSize)
    {
        buffer_.str(std::string(initialSize, '\0'));
        buffer_.seekp(0);
    }

    inline StringWriter::~StringWriter() = default;

    inline StringWriter& StringWriter::append(const char c)
    {
        buffer_.put(c);
        return *this;
    }

    inline StringWriter& StringWriter::append(const std::string& csq)
    {
        if (!csq.empty())
        {
            buffer_ << csq;
        }
        return *this;
    }

    inline StringWriter& StringWriter::append(const std::string& csq, const size_t start, const size_t end)
    {
        if (start <= end && end <= csq.size())
        {
            const size_t actual_end = std::min(end, csq.size());
            if (actual_end > start)
            {
                buffer_.write(csq.data() + start, static_cast<std::streamsize>(actual_end - start));
            }
        }
        else
        {
            throw std::out_of_range("Invalid start or end position");
        }
        return *this;
    }

    inline auto StringWriter::close() -> void
    {
    }

    inline auto StringWriter::flush() -> void
    {
        buffer_.flush();
    }

    inline auto StringWriter::getBuffer() const -> std::string
    {
        return buffer_.str();
    }

    inline auto StringWriter::toString() const -> std::string
    {
        return buffer_.str();
    }

    inline void StringWriter::write(const char c)
    {
        buffer_.put(c);
    }

    inline void StringWriter::write(const std::string& str)
    {
        if (!str.empty())
        {
            buffer_ << str;
        }
    }

    inline void StringWriter::write(const std::string& str, const size_t off, const size_t len)
    {
        if (len == 0)
        {
            return;
        }

        if (off > str.size() || off + len > str.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
    }

    inline auto StringWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
    }
} // namespace fox
