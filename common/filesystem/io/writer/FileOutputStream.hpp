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
    inline FileOutputStream(const std::string &name, bool append)
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

    inline FileOutputStream(const char *name, bool append) : FileOutputStream(std::string(name), append)
    {
    }

    inline FileOutputStream(const std::filesystem::path &file, bool append) : FileOutputStream(file.string(), append)
    {
    }

    inline ~FileOutputStream() override
    {
        close();
    }

    /// @brief Writes a single byte to the file stream.
    /// @param b The byte to write.
    inline void write(std::byte b) override
    {
        if (!file_stream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        const char byte = static_cast<char>(b);
        file_stream_.write(&byte, 1);
    }

    /// @brief Writes a vector of bytes to the file stream.
    /// @param buffer The vector of bytes to write.
    inline void write(const std::vector<std::byte> &buffer) override
    {
        write(buffer, 0, buffer.size());
    }

    /// @brief Writes a portion of a vector of bytes to the file stream.
    /// @param buffer The vector of bytes to write from.
    /// @param offset The starting position in the buffer.
    /// @param len The number of bytes to write.
    inline void write(const std::vector<std::byte> &buffer, const size_t offset, const size_t len) override
    {
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::invalid_argument("Invalid buffer, offset, or length.");
        }
        if (!file_stream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        file_stream_.write(reinterpret_cast<const char *>(buffer.data() + offset), static_cast<std::streamsize>(len));
    }

    /// @brief Closes the file stream.
    inline void close() override
    {
        if (file_stream_.is_open())
        {
            file_stream_.close();
        }
    }

    /// @brief Flushes the file stream.
    inline void flush() override
    {
        if (!file_stream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        file_stream_.flush();
    }

  private:
    std::ofstream file_stream_;
    std::string file_name_{};
};
} // namespace fox