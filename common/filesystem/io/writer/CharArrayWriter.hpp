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
    CharArrayWriter() = default;

    explicit CharArrayWriter(int32_t initialSize)
    {
        if (initialSize < 0)
        {
            throw std::invalid_argument("initialSize must be non-negative");
        }
        buf_.reserve(initialSize);
    }

    ~CharArrayWriter() override = default;

    /// @brief Writes a single character to the buffer.
    /// @param c The character to write.
    void write(char c) override
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

    /// @brief Writes a portion of a character array to the buffer.
    /// @param cBuf The character array to write from.
    /// @param off The offset in the array to start writing from.
    /// @param len The number of characters to write.
    auto write(const std::vector<char> &cBuf, const size_t off, const size_t len) -> void override
    {
        if (off + len > static_cast<int32_t>(cBuf.size()))
        {
            throw std::out_of_range("Invalid offset or length");
        }
        if (count_ + len > static_cast<int32_t>(buf_.size()))
        {
            buf_.resize(count_ + len);
        }
        std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len,
                    buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    /// @brief Writes a portion of a string to the buffer.
    /// @param str The string to write from.
    /// @param off The offset in the string to start writing from.
    /// @param len The number of characters to write.
    void write(const std::string &str, size_t off, size_t len) override
    {
        if (off + len > static_cast<int32_t>(str.size()))
        {
            throw std::out_of_range("Invalid offset or length");
        }
        if (count_ + len > static_cast<int32_t>(buf_.size()))
        {
            buf_.resize(count_ + len);
        }
        std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len,
                    buf_.begin() + static_cast<std::ptrdiff_t>(count_));
        count_ += len;
    }

    /// @brief Writes the contents of this writer to another writer.
    /// @param out The writer to write to.
    auto writeTo(AbstractWriter &out) const -> void
    {
        out.write(buf_, 0, count_);
    }

    /// @brief Appends a string to the buffer.
    /// @param csq The string to append.
    /// @return A reference to this writer.
    CharArrayWriter &append(const std::string &csq) override
    {
        write(csq, 0, csq.size());
        return *this;
    }

    /// @brief Appends a subsequence of a string to the buffer.
    /// @param csq The string to append from.
    /// @param start The starting index of the subsequence.
    /// @param end The ending index of the subsequence.
    /// @return A reference to this writer.
    CharArrayWriter &append(const std::string &csq, const size_t start, const size_t end) override
    {
        write(csq, start, end - start);
        return *this;
    }

    /// @brief Appends a single character to the buffer.
    /// @param c The character to append.
    /// @return A reference to this writer.
    CharArrayWriter &append(char c) override
    {
        write(c);
        return *this;
    }

    /// @brief Resets the buffer to empty.
    auto reset() -> void
    {
        count_ = 0;
    }

    /// @brief Returns a copy of the buffer's contents as a character array.
    /// @return A vector containing the buffer's contents.
    [[nodiscard]] auto toCharArray() const -> std::vector<char>
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    /// @brief Returns the current size of the buffer.
    /// @return The number of characters in the buffer.
    [[nodiscard]] auto size() const -> size_t
    {
        return count_;
    }

    /// @brief Returns the buffer's contents as a string.
    /// @return A string representation of the buffer's contents.
    [[nodiscard]] auto toString() const -> std::string override
    {
        return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
    }

    /// @brief Flushes the stream (no-op for this implementation).
    auto flush() -> void override
    {
        buf_.clear();
        count_ = 0;
    }

    /// @brief Closes the writer (no-op for this implementation).
    auto close() -> void override
    {
        buf_.clear();
        count_ = 0;
    }

  private:
    std::vector<char> buf_;
    size_t count_{0};
};
} // namespace fox