#pragma once
#include <string>
#include <vector>

#include "filesystem/io/interface/IAppendable.hpp"
#include "filesystem/io/interface/ICloseable.hpp"
#include "filesystem/io/interface/IFlushable.hpp"

namespace fox
{
    /// @brief Abstract base class for writers that provides basic functionality for writing characters and strings.
    class AbstractWriter : public ICloseable, public IFlushable, IAppendable<AbstractWriter>
    {
    public:
        AbstractWriter();
        ~AbstractWriter() override;

        /// @brief Appends a single character to the writer.
        /// @param c The character to append.
        /// @return A reference to this AbstractWriter instance.
        auto append(char c) -> AbstractWriter& override;

        /// @brief Appends a string to the writer.
        /// @param csq The string to append.
        /// @return A reference to this AbstractWriter instance.
        auto append(const std::string& csq) -> AbstractWriter& override;

        /// @brief Appends a subsequence of a string to the writer.
        /// @param csq The string from which a subsequence is to be appended.
        /// @param start The starting index of the subsequence to be appended.
        /// @param end The ending index of the subsequence to be appended.
        /// @return A reference to this AbstractWriter instance.
        auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;

        /// @brief Writes a single character to the writer.
        /// @param c The character to write.
        virtual auto write(char c) -> void;

        /// @brief Writes a sequence of characters to the writer.
        /// @param cBuf The character sequence to write.
        virtual auto write(const std::vector<char>& cBuf) -> void;

        /// @brief Writes a sequence of characters to the writer, starting from a specified offset.
        /// @param cBuf The character sequence to write.
        /// @param off The starting offset in the character sequence.
        /// @param len The number of characters to write.
        virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;

        /// @brief Writes a string to the writer.
        /// @param str The string to write.
        virtual auto write(const std::string& str) -> void;

        /// @brief Writes a substring to the writer, starting from a specified offset.
        /// @param str The string to write.
        /// @param off The starting offset in the string.
        /// @param len The number of characters to write.
        virtual auto write(const std::string& str, size_t off, size_t len) -> void;

        /// @brief Converts the content of the writer to a string representation.
        /// @return A string representation of the writer's content.
        [[nodiscard]] virtual auto toString() const -> std::string = 0;
    };

    inline AbstractWriter::AbstractWriter() = default;
    inline AbstractWriter::~AbstractWriter() = default;

    inline auto AbstractWriter::append(const char c) -> AbstractWriter&
    {
        write(c);
        return *this;
    }

    inline auto AbstractWriter::append(const std::string& csq) -> AbstractWriter&
    {
        write(csq);
        return *this;
    }

    inline auto AbstractWriter::append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter&
    {
        if (start <= end && start <= csq.length())
        {
            const size_t safe_end = std::min(end, csq.length());
            write(csq, start, safe_end - start);
        }
        return *this;
    }

    inline auto AbstractWriter::write(const char c) -> void
    {
        const std::vector<char> buf(1, c);
        write(buf, 0, 1);
    }

    inline auto AbstractWriter::write(const std::vector<char>& cBuf) -> void
    {
        if (!cBuf.empty())
        {
            write(cBuf, 0, cBuf.size());
        }
    }

    inline auto AbstractWriter::write(const std::string& str) -> void
    {
        if (!str.empty())
        {
            write(str, 0, str.size());
        }
    }

    inline auto AbstractWriter::write(const std::string& str, const size_t off, const size_t len) -> void
    {
        if (off < str.size() && len > 0)
        {
            const size_t end = std::min(off + len, str.size());
            const std::vector<char> buf(str.begin() + static_cast<std::string::difference_type>(off),
                                        str.begin() + static_cast<std::string::difference_type>(end));
            write(buf, 0, buf.size());
        }
    }
} // namespace fox
