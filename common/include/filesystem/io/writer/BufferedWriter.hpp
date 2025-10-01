#pragma once
#include <glog/logging.h>

#include <fstream>
#include <vector>

#include "AbstractWriter.hpp"

namespace fox
{
    /// @brief A buffered writer that writes data to an output stream with buffering.
    /// This class provides efficient writing operations by buffering the output data
    /// before writing it to the underlying output stream.
    class BufferedWriter final : public AbstractWriter, public IAppendable<BufferedWriter>
    {
    public:
        /// @brief Constructs a buffered writer with specified buffer size.
        /// @param os The underlying output file stream.
        /// @param size The buffer size in bytes.
        /// @throws std::runtime_error if the output stream is null or not open.
        explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size = DEFAULT_BUFFER_SIZE);

        /// @brief Destructor that closes the writer.
        ~BufferedWriter() override;

        /// @brief Writes a string to the buffer.
        /// @param str The string to write.
        auto write(const std::string& str) -> void override;

        /// @brief Writes a portion of a character buffer to the buffer.
        /// @param cBuf The character buffer to write from.
        /// @param off The offset in the buffer to start writing from.
        /// @param len The number of characters to write.
        /// @throws std::out_of_range if offset and length are out of the bounds of the buffer.
        auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;

        /// @brief Flushes the buffer to the underlying output stream.
        /// @throws std::ios_base::failure if an I/O error occurs.
        auto flush() -> void override;

        /// @brief Closes the writer and releases any resources.
        /// @throws std::ios_base::failure if an I/O error occurs.
        auto close() -> void override;

        /// @brief Appends a single character to the buffer.
        /// @param c The character to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(char c) -> BufferedWriter& override;

        /// @brief Appends a string to the buffer.
        /// @param str The string to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(const std::string& str) -> BufferedWriter& override;

        /// @brief Appends a substring to the buffer.
        /// @param str The string to append.
        /// @param start The starting index of the substring.
        /// @param end The ending index of the substring.
        /// @return A reference to this BufferedWriter instance.
        auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;

        /// @brief Appends a string view to the buffer.
        /// @param str The string view to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(std::string_view str) -> BufferedWriter& override;

        /// @brief Appends a C-string to the buffer.
        /// @param str The C-string to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(const char* str) -> BufferedWriter& override;

        /// @brief Appends an initializer list of characters to the buffer.
        /// @param chars The initializer list of characters to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(std::initializer_list<char> chars) -> BufferedWriter& override;

        /// @brief Appends a sequence of characters to the buffer.
        /// @param chars Pointer to the character sequence.
        /// @param count Number of characters to append.
        /// @return A reference to this BufferedWriter instance.
        auto append(const char* chars, size_t count) -> BufferedWriter& override;

        /// @brief Appends a character multiple times to the buffer.
        /// @param c The character to append.
        /// @param count Number of times to append the character.
        /// @return A reference to this BufferedWriter instance.
        auto append(char c, size_t count) -> BufferedWriter& override;

        /// @brief Writes a newline character to the buffer.
        /// @return A reference to this BufferedWriter instance.
        auto newLine() -> BufferedWriter&;

        /// @brief Converts the buffer content to a string representation.
        /// @return The string representation of the buffer content.
        [[nodiscard]] auto toString() const -> std::string override;

        /// @brief Checks if the writer is closed.
        /// @return True if the writer is closed, false otherwise.
        [[nodiscard]] auto isClosed() const noexcept -> bool override;

    private:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
        std::unique_ptr<std::ofstream> output_stream_;
        std::vector<char> buffer_;
        size_t buffer_size_;

        /// @brief Flushes the internal buffer if it reaches the buffer size threshold.
        auto checkAndFlush() -> void;
    };

    inline BufferedWriter::BufferedWriter(std::unique_ptr<std::ofstream> os, const size_t size) :
        output_stream_(std::move(os)), buffer_size_(size)
    {
        if (!output_stream_)
        {
            throw std::runtime_error("Output stream is null.");
        }
        if (!output_stream_->is_open())
        {
            throw std::runtime_error("Output stream is not open.");
        }
        buffer_.reserve(buffer_size_);
    }

    inline BufferedWriter::~BufferedWriter()
    {
        try
        {
            close();
        }
        catch (...)
        {
            // Ignore exceptions during destruction
        }
    }

    inline auto BufferedWriter::write(const std::string& str) -> void
    {
        if (str.size() > buffer_size_)
        {
            flush();
            *output_stream_ << str;
        }
        else
        {
            for (const char c : str)
            {
                buffer_.push_back(c);
            }
            checkAndFlush();
        }
    }

    inline auto BufferedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void
    {
        if (len == 0)
        {
            return;
        }

        if (off + len > cBuf.size())
        {
            throw std::out_of_range("Offset and length are out of the bounds of the buffer.");
        }

        if (len > buffer_size_)
        {
            flush();
            output_stream_->write(cBuf.data() + off, static_cast<std::streamsize>(len));
        }
        else
        {
            for (size_t i = 0; i < len; ++i)
            {
                buffer_.push_back(cBuf[off + i]);
                checkAndFlush();
            }
        }
    }

    inline auto BufferedWriter::flush() -> void
    {
        if (!buffer_.empty())
        {
            output_stream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
            buffer_.clear();
        }
        output_stream_->flush();
    }

    inline auto BufferedWriter::close() -> void
    {
        if (output_stream_ && output_stream_->is_open())
        {
            flush();
            output_stream_->close();
        }
    }

    inline auto BufferedWriter::append(const char c) -> BufferedWriter&
    {
        buffer_.push_back(c);
        checkAndFlush();
        return *this;
    }

    inline auto BufferedWriter::append(const std::string& str) -> BufferedWriter&
    {
        for (const char c : str)
        {
            buffer_.push_back(c);
            checkAndFlush();
        }
        return *this;
    }

    inline auto BufferedWriter::append(const std::string& str, const size_t start, const size_t end) -> BufferedWriter&
    {
        if (start < str.length() && end <= str.length() && start < end)
        {
            for (size_t i = start; i < end; ++i)
            {
                buffer_.push_back(str[i]);
                checkAndFlush();
            }
        }
        return *this;
    }

    inline auto BufferedWriter::append(const std::string_view str) -> BufferedWriter&
    {
        for (const char c : str)
        {
            buffer_.push_back(c);
            checkAndFlush();
        }
        return *this;
    }

    inline auto BufferedWriter::append(const char* str) -> BufferedWriter&
    {
        if (str)
        {
            for (size_t i = 0; str[i] != '\0'; ++i)
            {
                buffer_.push_back(str[i]);
                checkAndFlush();
            }
        }
        return *this;
    }

    inline auto BufferedWriter::append(const std::initializer_list<char> chars) -> BufferedWriter&
    {
        for (const char c : chars)
        {
            buffer_.push_back(c);
            checkAndFlush();
        }
        return *this;
    }

    inline auto BufferedWriter::append(const char* chars, const size_t count) -> BufferedWriter&
    {
        if (chars)
        {
            for (size_t i = 0; i < count; ++i)
            {
                buffer_.push_back(chars[i]);
                checkAndFlush();
            }
        }
        return *this;
    }

    inline auto BufferedWriter::append(const char c, const size_t count) -> BufferedWriter&
    {
        for (size_t i = 0; i < count; ++i)
        {
            buffer_.push_back(c);
            checkAndFlush();
        }
        return *this;
    }

    inline auto BufferedWriter::newLine() -> BufferedWriter&
    {
        return append('\n');
    }

    inline auto BufferedWriter::toString() const -> std::string
    {
        return std::string(buffer_.begin(), buffer_.end());
    }

    inline auto BufferedWriter::isClosed() const noexcept -> bool
    {
        return output_stream_ == nullptr || !output_stream_->is_open();
    }

    inline auto BufferedWriter::checkAndFlush() -> void
    {
        if (buffer_.size() >= buffer_size_)
        {
            flush();
        }
    }
}
