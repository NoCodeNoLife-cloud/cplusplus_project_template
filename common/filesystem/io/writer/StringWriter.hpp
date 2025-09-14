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
    explicit StringWriter(size_t initialSize)
    {
        buffer_.str(std::string(initialSize, '\0'));
        buffer_.seekp(0);
    }
    ~StringWriter() override = default;

    /// @brief Appends the specified character to this writer.
    /// @param c The character to append.
    /// @return A reference to this StringWriter.
    auto append(char c) -> StringWriter & override
    {
        buffer_.put(c);
        return *this;
    }

    /// @brief Appends the specified string to this writer.
    /// @param csq The string to append.
    /// @return A reference to this StringWriter.
    auto append(const std::string &csq) -> StringWriter & override
    {
        buffer_ << csq;
        return *this;
    }

    /// @brief Appends a subsequence of the specified string to this writer.
    /// @param csq The string from which a subsequence is appended.
    /// @param start The starting index of the subsequence.
    /// @param end The ending index of the subsequence.
    /// @return A reference to this StringWriter.
    auto append(const std::string &csq, size_t start, size_t end) -> StringWriter & override
    {
        if (start > end || end > csq.size())
        {
            throw std::out_of_range("Invalid start or end position");
        }
        buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
        return *this;
    }

    /// @brief Closes the writer and releases any associated resources.
    auto close() -> void override
    {
    }

    /// @brief Flushes the writer, ensuring all buffered data is written.
    auto flush() -> void override
    {
        buffer_.flush();
    }

    /// @brief Gets the current buffer content as a string.
    /// @return The buffer content.
    [[nodiscard]] auto getBuffer() const -> std::string
    {
        return buffer_.str();
    }

    /// @brief Converts the buffer content to a string representation.
    /// @return The string representation of the buffer.
    [[nodiscard]] auto toString() const -> std::string override
    {
        return buffer_.str();
    }

    /// @brief Writes a single character to the writer.
    /// @param c The character to write.
    auto write(char c) -> void override
    {
        buffer_.put(c);
    }

    /// @brief Writes the specified string to the writer.
    /// @param str The string to write.
    auto write(const std::string &str) -> void override
    {
        buffer_ << str;
    }

    /// @brief Writes a portion of the specified string to the writer.
    /// @param str The string to write.
    /// @param off The offset from which to start writing.
    /// @param len The number of characters to write.
    auto write(const std::string &str, const size_t off, const size_t len) -> void override
    {
        if (off > str.size() || off + len > str.size())
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
    }

    /// @brief Writes a portion of the specified character array to the writer.
    /// @param cBuf The character array to write.
    /// @param off The offset from which to start writing.
    /// @param len The number of characters to write.
    auto write(const std::vector<char> &cBuf, const size_t off, const size_t len) -> void override
    {
        if (off > cBuf.size() || len > cBuf.size() - off)
        {
            throw std::out_of_range("Invalid offset or length");
        }
        buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
    }

  private:
    std::ostringstream buffer_;
};
} // namespace fox