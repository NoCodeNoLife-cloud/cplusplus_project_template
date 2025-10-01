#pragma once
#include <filesystem>
#include <fstream>
#include <vector>

#include "AbstractOutputStream.hpp"

namespace fox
{
    /// @brief A class for writing data to a file.
    /// @details This class provides methods for writing bytes to a file, either
    /// appending to or overwriting the file's contents. It inherits from
    /// AbstractOutputStream to provide a consistent interface for output streams.
    class FileOutputStream final : public AbstractOutputStream
    {
    public:
        /// @brief Constructs a FileOutputStream for the specified file path.
        /// @param name The file path as a string.
        /// @param append If true, opens file in append mode; otherwise truncates.
        /// @throws std::ios_base::failure If the path is a directory or file cannot be opened.
        inline FileOutputStream(const std::string& name, bool append);

        /// @brief Constructs a FileOutputStream for the specified file path.
        /// @param name The file path as a C-string.
        /// @param append If true, opens file in append mode; otherwise truncates.
        /// @throws std::ios_base::failure If the path is a directory or file cannot be opened.
        inline FileOutputStream(const char* name, bool append);

        /// @brief Constructs a FileOutputStream for the specified file path.
        /// @param file The file path as a filesystem path object.
        /// @param append If true, opens file in append mode; otherwise truncates.
        /// @throws std::ios_base::failure If the path is a directory or file cannot be opened.
        inline FileOutputStream(const std::filesystem::path& file, bool append);

        /// @brief Destructor that closes the file stream if open.
        inline ~FileOutputStream() override;

        /// @brief Writes a single byte to the file stream.
        /// @param b The byte to write.
        /// @throws std::ios_base::failure If the stream is not writable or in a bad state.
        inline auto write(std::byte b) -> void override;

        /// @brief Writes an array of bytes to the file stream.
        /// @param buffer Pointer to the array of bytes to write.
        /// @param length Number of bytes to write.
        /// @throws std::ios_base::failure If the stream is not writable or in a bad state.
        inline auto write(const std::byte* buffer, size_t length) -> void override;

        /// @brief Writes a vector of bytes to the file stream.
        /// @param buffer The vector of bytes to write.
        /// @throws std::ios_base::failure If the stream is not writable or in a bad state.
        inline auto write(const std::vector<std::byte>& buffer) -> void override;

        /// @brief Writes a portion of a vector of bytes to the file stream.
        /// @param buffer The vector of bytes to write from.
        /// @param offset The starting position in the buffer.
        /// @param len The number of bytes to write.
        /// @throws std::ios_base::failure If the stream is not writable or in a bad state.
        inline auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;

        /// @brief Closes the file stream.
        /// @throws std::ios_base::failure If the stream is not writable.
        inline auto close() -> void override;

        /// @brief Flushes the file stream.
        /// @throws std::ios_base::failure If the stream is not writable or in a bad state.
        inline auto flush() -> void override;

        /// @brief Checks if the stream is closed.
        /// @return true if the stream is closed, false otherwise.
        inline auto isClosed() const -> bool override;

    private:
        std::ofstream file_stream_;
        std::string file_name_;

        /// @brief Checks if the stream is writable, throwing an exception if not.
        /// @param message The message for the exception if the stream is not writable.
        /// @throws std::ios_base::failure If the stream is not open or not writable.
        inline auto checkStreamWritable(const std::string& message) const -> void;

        /// @brief Checks the stream state and throws an exception if badbit or failbit is set.
        /// @throws std::ios_base::failure If the stream is in a bad state.
        inline auto checkStreamState() const -> void;
    };

    inline FileOutputStream::FileOutputStream(const std::string& name, const bool append)
    {
        if (std::filesystem::exists(name) && std::filesystem::is_directory(name))
        {
            throw std::ios_base::failure("Path is a directory.");
        }
        file_stream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
        if (!file_stream_.is_open())
        {
            throw std::ios_base::failure("Unable to open or create file.");
        }
        file_name_ = name;
    }

    inline FileOutputStream::FileOutputStream(const char* name, const bool append)
        : FileOutputStream(std::string(name), append)
    {
    }

    inline FileOutputStream::FileOutputStream(const std::filesystem::path& file, const bool append)
        : FileOutputStream(file.string(), append)
    {
    }

    inline FileOutputStream::~FileOutputStream()
    {
        if (file_stream_.is_open())
        {
            file_stream_.close();
        }
    }

    inline auto FileOutputStream::write(std::byte b) -> void
    {
        checkStreamWritable("Cannot write to closed or unwritable stream.");
        checkStreamState();
        file_stream_.put(static_cast<char>(b));
        checkStreamState();
    }

    inline auto FileOutputStream::write(const std::byte* buffer, const size_t length) -> void
    {
        checkStreamWritable("Cannot write to closed or unwritable stream.");
        checkStreamState();
        file_stream_.write(reinterpret_cast<const char*>(buffer), static_cast<std::streamsize>(length));
        checkStreamState();
    }

    inline auto FileOutputStream::write(const std::vector<std::byte>& buffer) -> void
    {
        if (!buffer.empty())
        {
            write(buffer.data(), buffer.size());
        }
    }

    inline auto FileOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void
    {
        if (offset + len > buffer.size())
        {
            throw std::out_of_range("Buffer access out of bounds.");
        }

        if (len > 0)
        {
            write(buffer.data() + offset, len);
        }
    }

    inline auto FileOutputStream::close() -> void
    {
        checkStreamWritable("Cannot close closed or unwritable stream.");
        file_stream_.close();
    }

    inline auto FileOutputStream::flush() -> void
    {
        checkStreamWritable("Cannot flush closed or unwritable stream.");
        checkStreamState();
        file_stream_.flush();
        checkStreamState();
    }

    inline auto FileOutputStream::isClosed() const -> bool
    {
        return !file_stream_.is_open();
    }

    inline auto FileOutputStream::checkStreamWritable(const std::string& message) const -> void
    {
        if (!file_stream_.is_open())
        {
            throw std::ios_base::failure(message);
        }
    }

    inline auto FileOutputStream::checkStreamState() const -> void
    {
        if (file_stream_.bad())
        {
            throw std::ios_base::failure("Stream is in bad state.");
        }
        if (file_stream_.fail())
        {
            throw std::ios_base::failure("Stream operation failed.");
        }
    }
}
