#include "src/filesystem/io/reader/FileInputStream.hpp"

#include <stdexcept>

namespace fox
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
        file_stream_.open(name, std::ios::binary);
        if (!file_stream_.is_open())
        {
            throw std::ios_base::failure("FileNotFoundException: Unable to open file.");
        }
        file_name_ = name;
    }

    FileInputStream::FileInputStream(const char* name) : FileInputStream(std::string(name))
    {
    }

    FileInputStream::FileInputStream(const std::filesystem::path& file) : FileInputStream(file.string())
    {
    }

    FileInputStream::~FileInputStream()
    {
        close();
    }

    auto FileInputStream::read() -> std::byte
    {
        if (closed_ || !file_stream_.good())
        {
            return static_cast<std::byte>(-1);
        }

        std::byte byte{};
        if (file_stream_.read(reinterpret_cast<char*>(&byte), 1))
        {
            return byte;
        }
        return static_cast<std::byte>(-1);
    }

    auto FileInputStream::read(std::vector<std::byte>& buffer) -> size_t
    {
        return read(buffer, 0, buffer.size());
    }

    auto FileInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t
    {
        if (offset > buffer.size() || len > buffer.size() - offset)
        {
            throw std::invalid_argument("Invalid buffer, offset, or length.");
        }

        if (closed_ || !file_stream_.good())
        {
            return 0;
        }

        file_stream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
        const auto bytes_read = file_stream_.gcount();
        return static_cast<size_t>(bytes_read);
    }

    auto FileInputStream::skip(const size_t n) -> size_t
    {
        if (closed_ || !file_stream_.good())
        {
            return 0;
        }

        const auto current_pos = file_stream_.tellg();
        if (current_pos == std::streampos(-1))
        {
            return 0;
        }

        file_stream_.seekg(static_cast<std::streamoff>(n), std::ios::cur);
        if (!file_stream_.good())
        {
            // Restore the original position if seek failed
            file_stream_.seekg(current_pos, std::ios::beg);
            return 0;
        }

        const auto new_pos = file_stream_.tellg();
        if (new_pos == std::streampos(-1))
        {
            return 0;
        }

        const auto skipped = new_pos - current_pos;
        return static_cast<size_t>(skipped);
    }

    auto FileInputStream::available() -> size_t
    {
        if (closed_ || !file_stream_.good())
        {
            return 0;
        }

        const auto current = file_stream_.tellg();
        if (current == std::streampos(-1))
        {
            return 0;
        }

        file_stream_.seekg(0, std::ios::end);
        const auto end = file_stream_.tellg();
        file_stream_.seekg(current, std::ios::beg);

        if (end == std::streampos(-1))
        {
            return 0;
        }

        const auto available_bytes = end - current;
        return static_cast<size_t>(std::max(available_bytes, static_cast<std::streamoff>(0)));
    }

    auto FileInputStream::close() -> void
    {
        if (file_stream_.is_open())
        {
            file_stream_.close();
        }
        closed_ = true;
    }

    auto FileInputStream::isClosed() const -> bool
    {
        return closed_;
    }

    auto FileInputStream::markSupported() const -> bool
    {
        return false;
    }
}
