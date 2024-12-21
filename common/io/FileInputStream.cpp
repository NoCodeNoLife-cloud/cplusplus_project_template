#include "FileInputStream.hpp"

namespace common::io
{
    FileInputStream::FileInputStream(const std::string& name)
    {
        if (!std::filesystem::exists(name))
        {
            throw std::ios_base::failure("FileNotFoundException: File does not exist.");
        }
        if (std::filesystem::is_directory(name))
        {
            throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
        }
        fileStream_.open(name, std::ios::binary);
        if (!fileStream_.is_open())
        {
            throw std::ios_base::failure("FileNotFoundException: Unable to open file.");
        }
        fileName_ = name;
    }

    FileInputStream::FileInputStream(const char* name) : FileInputStream(std::string(name)) {}

    FileInputStream::FileInputStream(const std::filesystem::path& file): FileInputStream(file.string()) {}

    FileInputStream::~FileInputStream()
    {
        close();
    }

    auto FileInputStream::read() -> std::byte
    {
        std::byte byte;
        if (fileStream_.read(reinterpret_cast<char*>(&byte), 1))
        {
            return byte;
        }
        return static_cast<std::byte>(-1);
    }

    size_t FileInputStream::read(std::vector<std::byte>& buffer)
    {
        return read(buffer, 0, buffer.size());
    }

    size_t FileInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len)
    {
        if (offset + len > buffer.size())
        {
            throw std::invalid_argument("Invalid buffer, offset, or length.");
        }
        fileStream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
        return fileStream_.gcount();
    }

    size_t FileInputStream::skip(const size_t n)
    {
        fileStream_.seekg(static_cast<std::streamoff>(n), std::ios::cur);
        return fileStream_.good() ? static_cast<std::streamoff>(n) : 0;
    }

    auto FileInputStream::available() -> size_t
    {
        const auto current = fileStream_.tellg();
        fileStream_.seekg(0, std::ios::end);
        const auto end = fileStream_.tellg();
        fileStream_.seekg(current, std::ios::beg);
        return end - current;
    }

    auto FileInputStream::close() -> void
    {
        if (fileStream_.is_open())
        {
            fileStream_.close();
        }
    }

    bool FileInputStream::markSupported() const
    {
        return false;
    }
}
