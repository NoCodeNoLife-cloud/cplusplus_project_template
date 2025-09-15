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
        FileOutputStream(const std::string& name, const bool append)
        {
            if (std::filesystem::exists(name) && std::filesystem::is_directory(name))
            {
                throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
            }
            file_stream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
            if (!file_stream_.is_open())
            {
                throw std::ios_base::failure("FileNotFoundException: Unable to open or create file.");
            }
            file_name_ = name;
        }

        FileOutputStream(const char* name, const bool append) : FileOutputStream(std::string(name), append)
        {
        }

        FileOutputStream(const std::filesystem::path& file, const bool append) : FileOutputStream(file.string(), append)
        {
        }

        ~FileOutputStream() override
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

        /// @brief Writes a single byte to the file stream.
        /// @param b The byte to write.
        void write(std::byte b) override
        {
            checkStreamWritable("IOException: Stream is not writable.");
            const char byte = static_cast<char>(b);
            file_stream_.write(&byte, 1);
            checkStreamState();
        }

        /// @brief Writes a vector of bytes to the file stream.
        /// @param buffer The vector of bytes to write.
        void write(const std::vector<std::byte>& buffer) override
        {
            if (!buffer.empty())
            {
                write(buffer, 0, buffer.size());
            }
        }

        /// @brief Writes a portion of a vector of bytes to the file stream.
        /// @param buffer The vector of bytes to write from.
        /// @param offset The starting position in the buffer.
        /// @param len The number of bytes to write.
        void write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) override
        {
            if (len == 0)
            {
                return;
            }

            if (offset > buffer.size() || len > buffer.size() - offset)
            {
                throw std::invalid_argument("Invalid buffer, offset, or length.");
            }

            checkStreamWritable("IOException: Stream is not writable.");
            file_stream_.write(reinterpret_cast<const char*>(buffer.data() + offset),
                               static_cast<std::streamsize>(len));
            checkStreamState();
        }

        /// @brief Closes the file stream.
        void close() override
        {
            if (file_stream_.is_open())
            {
                file_stream_.close();
            }
        }

        /// @brief Flushes the file stream.
        void flush() override
        {
            checkStreamWritable("IOException: Stream is not writable.");
            file_stream_.flush();
        }

    private:
        std::ofstream file_stream_;
        std::string file_name_{};

        /// @brief Checks if the stream is writable, throwing an exception if not.
        /// @param message The message for the exception if the stream is not writable.
        auto checkStreamWritable(const std::string& message) const -> void
        {
            if (!file_stream_)
            {
                throw std::ios_base::failure(message);
            }
        }

        /// @brief Checks the stream state and throws an exception if badbit or failbit is set.
        auto checkStreamState() const -> void
        {
            if (file_stream_.bad())
            {
                throw std::ios_base::failure("IOException: Stream bad state.");
            }
            if (file_stream_.fail())
            {
                throw std::ios_base::failure("IOException: Stream operation failed.");
            }
        }
    };

    inline FileOutputStream::FileOutputStream(const std::string& name, const bool append)
    {
        if (std::filesystem::exists(name) && std::filesystem::is_directory(name))
        {
            throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
        }
        file_stream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
        if (!file_stream_.is_open())
        {
            throw std::ios_base::failure("FileNotFoundException: Unable to open or create file.");
        }
        file_name_ = name;
    }

    inline FileOutputStream::FileOutputStream(const char* name, const bool append) : FileOutputStream(
        std::string(name), append)
    {
    }

    inline FileOutputStream::FileOutputStream(const std::filesystem::path& file, const bool append) : FileOutputStream(
        file.string(), append)
    {
    }

    inline FileOutputStream::~FileOutputStream()
    {
    }

    inline void FileOutputStream::write(std::byte b)
    {
    }

    inline void FileOutputStream::write(const std::vector<std::byte>& buffer)
    {
        AbstractOutputStream::write(buffer);
    }

    inline void FileOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        AbstractOutputStream::write(buffer, offset, len);
    }

    inline void FileOutputStream::close()
    {
    }

    inline void FileOutputStream::flush()
    {
    }

    inline auto FileOutputStream::checkStreamWritable(const std::string& message) const -> void
    {
    }

    inline auto FileOutputStream::checkStreamState() const -> void
    {
    }
} // namespace fox
