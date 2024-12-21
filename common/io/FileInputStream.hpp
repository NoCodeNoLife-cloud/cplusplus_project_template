#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
    class FileInputStream final : public AbstractInputStream
    {
    public:
        explicit FileInputStream(const std::string& name)
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

        explicit FileInputStream(const char* name) : FileInputStream(std::string(name))
        {
        }

        explicit FileInputStream(const std::filesystem::path& file) : FileInputStream(file.string())
        {
        }

        ~FileInputStream() override
        {
            close();
        }

        auto read() -> std::byte override
        {
            std::byte byte;
            if (fileStream_.read(reinterpret_cast<char*>(&byte), 1))
            {
                return byte;
            }
            return static_cast<std::byte>(-1);
        }

        auto read(std::vector<std::byte>& buffer) -> size_t override
        {
            return read(buffer, 0, buffer.size());
        }

        auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t override
        {
            if (offset + len > buffer.size())
            {
                throw std::invalid_argument("Invalid buffer, offset, or length.");
            }
            fileStream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
            return fileStream_.gcount();
        }

        auto skip(const size_t n) -> size_t override
        {
            fileStream_.seekg(static_cast<std::streamoff>(n), std::ios::cur);
            return fileStream_.good() ? static_cast<std::streamoff>(n) : 0;
        }

        auto available() -> size_t override
        {
            const auto current = fileStream_.tellg();
            fileStream_.seekg(0, std::ios::end);
            const auto end = fileStream_.tellg();
            fileStream_.seekg(current, std::ios::beg);
            return end - current;
        }

        auto close() -> void override
        {
            if (fileStream_.is_open())
            {
                fileStream_.close();
            }
        }

        [[nodiscard]] auto markSupported() const -> bool override
        {
            return false;
        }

    private:
        std::ifstream fileStream_;
        std::string fileName_{};
    };
}
