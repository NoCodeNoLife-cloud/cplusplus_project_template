#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <codecvt>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "AbstractWriter.hpp"

namespace fox
{
    /// @brief A writer that converts character streams to byte streams using a specified charset.
    /// @details OutputStreamWriter is a bridge from character streams to byte streams: Characters written to it
    /// are encoded into bytes using the specified charset. The charset can be specified by name or
    /// defaults to the system's default charset.
    class OutputStreamWriter final : public AbstractWriter
    {
    public:
        /// @brief Constructs an OutputStreamWriter that uses the specified charset.
        /// @param outputStream The underlying output stream.
        /// @param charsetName The name of the charset to be used.
        /// @throws std::invalid_argument If the charset is not supported.
        inline OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName);

        /// @brief Constructs an OutputStreamWriter that uses the default charset.
        /// @param outputStream The underlying output stream.
        inline explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream);

        /// @brief Destructor.
        inline ~OutputStreamWriter() override;

        /// @brief Get the encoding of the writer.
        /// @return The encoding name as a string.
        [[nodiscard]] inline auto getEncoding() const -> std::string;

        /// @brief Write a single character.
        /// @param c The character to write.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto write(char c) -> void override;

        /// @brief Write an entire character array.
        /// @param cBuf The character array to write.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto write(const std::vector<char>& cBuf) -> void override;

        /// @brief Write a portion of a character array.
        /// @param cBuf The character array to write from.
        /// @param off The offset in the array to start writing from.
        /// @param len The number of characters to write.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        /// @throws std::out_of_range If offset and length exceed buffer size.
        inline auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

        /// @brief Write a string.
        /// @param str The string to write.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto write(const std::string& str) -> void override;

        /// @brief Write a portion of a string.
        /// @param str The string to write from.
        /// @param off The offset in the string to start writing from.
        /// @param len The number of characters to write.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        /// @throws std::out_of_range If offset and length exceed string size.
        inline auto write(const std::string& str, size_t off, size_t len) -> void override;

        /// @brief Flush the stream.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto flush() -> void override;

        /// @brief Close the writer.
        /// @throws std::ios_base::failure If the output stream is not available.
        inline auto close() -> void override;

        /// @brief Checks if the stream is closed.
        /// @return true if the stream is closed, false otherwise.
        inline auto isClosed() const -> bool override;

        /// @brief Append a character to the writer.
        /// @param c The character to append.
        /// @return A reference to this writer.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto append(char c) -> AbstractWriter& override;

        /// @brief Append a string to the writer.
        /// @param csq The string to append.
        /// @return A reference to this writer.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto append(const std::string& csq) -> AbstractWriter& override;

        /// @brief Append a subsequence of a string to the writer.
        /// @param csq The string to append from.
        /// @param start The starting index of the subsequence.
        /// @param end The ending index of the subsequence.
        /// @return A reference to this writer.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        inline auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;

        /// @brief Convert the writer to a string representation.
        /// @return A string representation of the writer.
        /// @throws std::ios_base::failure If the stream is closed or output stream is not available.
        [[nodiscard]] inline auto toString() const -> std::string override;

    private:
        std::unique_ptr<AbstractWriter> output_writer_;
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
        std::string charset_;
        bool closed_;

        /// @brief Checks if the stream is closed.
        /// @throws std::ios_base::failure if the stream is closed.
        inline auto checkIfClosed() const -> void;

        /// @brief Checks if the output stream is available.
        /// @throws std::ios_base::failure if the output stream is not available.
        inline auto checkOutputStream() const -> void;
    };

    inline OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream,
                                                  const std::string& charsetName) :
        output_writer_(std::move(outputStream)), charset_(charsetName), closed_(false)
    {
        if (charsetName != "UTF-8")
        {
            throw std::invalid_argument("Unsupported encoding: " + charsetName);
        }
    }

    inline OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream) : OutputStreamWriter(
        std::move(outputStream), "UTF-8")
    {
    }

    inline OutputStreamWriter::~OutputStreamWriter() = default;

    inline auto OutputStreamWriter::getEncoding() const -> std::string
    {
        return closed_ ? "" : charset_;
    }

    inline auto OutputStreamWriter::write(const char c) -> void
    {
        checkIfClosed();
        write(std::string(1, c));
    }

    inline auto OutputStreamWriter::write(const std::vector<char>& cBuf) -> void
    {
        if (!cBuf.empty())
        {
            write(cBuf, 0, cBuf.size());
        }
    }

    inline auto OutputStreamWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        checkIfClosed();
        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Offset and length exceed buffer size");
        }
        output_writer_->write(cBuf, off, len);
        checkOutputStream();
    }

    inline auto OutputStreamWriter::write(const std::string& str) -> void
    {
        if (!str.empty())
        {
            write(std::vector<char>(str.begin(), str.end()));
        }
    }

    inline auto OutputStreamWriter::write(const std::string& str, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        if (off + len > str.size())
        {
            throw std::out_of_range("Offset and length exceed string size");
        }
        write(std::vector<char>(str.begin() + static_cast<std::string::difference_type>(off),
                                str.begin() + static_cast<std::string::difference_type>(off + len)));
    }

    inline auto OutputStreamWriter::flush() -> void
    {
        checkIfClosed();
        output_writer_->flush();
        checkOutputStream();
    }

    inline auto OutputStreamWriter::close() -> void
    {
        if (closed_)
        {
            return;
        }
        flush();
        closed_ = true;
    }

    inline auto OutputStreamWriter::isClosed() const -> bool
    {
        return closed_;
    }

    inline auto OutputStreamWriter::append(const char c) -> AbstractWriter&
    {
        write(c);
        return *this;
    }

    inline auto OutputStreamWriter::append(const std::string& csq) -> AbstractWriter&
    {
        write(csq);
        return *this;
    }

    inline auto OutputStreamWriter::append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter&
    {
        if (start <= end && start <= csq.length())
        {
            const size_t safe_end = std::min(end, csq.length());
            write(csq, start, safe_end - start);
        }
        return *this;
    }

    inline auto OutputStreamWriter::toString() const -> std::string
    {
        checkIfClosed();
        return output_writer_->toString();
    }

    inline auto OutputStreamWriter::checkIfClosed() const -> void
    {
        if (closed_)
        {
            throw std::ios_base::failure("Stream is closed");
        }
    }

    inline auto OutputStreamWriter::checkOutputStream() const -> void
    {
        if (!output_writer_)
        {
            throw std::ios_base::failure("Failed to write to stream");
        }
    }
}
