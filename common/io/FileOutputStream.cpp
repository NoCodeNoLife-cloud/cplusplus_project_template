#include "FileOutputStream.hpp"

namespace common::io
{
    FileOutputStream::FileOutputStream(const std::string& name, const bool append)
    {
        if (std::filesystem::exists(name) && std::filesystem::is_directory(name))
        {
            throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
        }
        fileStream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
        if (!fileStream_.is_open())
        {
            throw std::ios_base::failure("FileNotFoundException: Unable to open or create file.");
        }
        fileName_ = name;
    }

    FileOutputStream::FileOutputStream(const char* name, const bool append) : FileOutputStream(std::string(name), append) {}

    FileOutputStream::FileOutputStream(const std::filesystem::path& file, const bool append): FileOutputStream(file.string(), append) {}

    FileOutputStream::~FileOutputStream()
    {
        close();
    }

    void FileOutputStream::write(std::byte b)
    {
        if (!fileStream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        const char byte = static_cast<char>(b);
        fileStream_.write(&byte, 1);
    }

    void FileOutputStream::write(const std::vector<std::byte>& buffer)
    {
        write(buffer, 0, buffer.size());
    }

    void FileOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::invalid_argument("Invalid buffer, offset, or length.");
        }
        if (!fileStream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        fileStream_.write(reinterpret_cast<const char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
    }

    void FileOutputStream::close()
    {
        if (fileStream_.is_open())
        {
            fileStream_.close();
        }
    }

    void FileOutputStream::flush()
    {
        if (!fileStream_)
        {
            throw std::ios_base::failure("IOException: Stream is not writable.");
        }
        fileStream_.flush();
    }
}
