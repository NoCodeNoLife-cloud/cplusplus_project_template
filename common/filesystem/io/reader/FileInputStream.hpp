#pragma once
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>

#include "AbstractInputStream.hpp"

namespace fox
{
    /// @brief A FileInputStream class for reading data from a file.
    /// @details This class provides functionality to read bytes from a file,
    ///          including methods for reading single bytes, multiple bytes,
    ///          skipping bytes, checking available bytes, and closing the stream.
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
            file_stream_.open(name, std::ios::binary);
            if (!file_stream_.is_open())
            {
                throw std::ios_base::failure("FileNotFoundException: Unable to open file.");
            }
            file_name_ = name;
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

        /// @brief Read a single byte from the stream.
        /// @return The byte read or EOF (-1) if the end of the stream is reached.
        auto read() -> std::byte override
        {
            std::byte byte{};
            if (file_stream_.read(reinterpret_cast<char*>(&byte), 1))
            {
                return byte;
            }
            return static_cast<std::byte>(-1);
        }

        /// @brief Read bytes from the stream.
        /// @param buffer The buffer to read into.
        /// @return The number of bytes read.
        auto read(std::vector<std::byte>& buffer) -> size_t override
        {
            return read(buffer, 0, buffer.size());
        }

        /// @brief Read bytes from the stream.
        /// @param buffer The buffer to read into.
        /// @param offset The offset to start reading from.
        /// @param len The number of bytes to read.
        /// @return The number of bytes read.
        auto read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t override
        {
            if (offset > buffer.size() || len > buffer.size() - offset)
            {
                throw std::invalid_argument("Invalid buffer, offset, or length.");
            }

            if (!file_stream_.good())
            {
                return 0;
            }

            file_stream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
            const auto bytes_read = file_stream_.gcount();
            return static_cast<size_t>(bytes_read);
        }

        /// @brief Skip bytes in the stream.
        /// @param n The number of bytes to skip.
        /// @return The number of bytes skipped.
        auto skip(const size_t n) -> size_t override
        {
            if (!file_stream_.good())
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

        /// @brief Get the number of bytes available to read.
        /// @return The number of bytes available to read.
        auto available() -> size_t override
        {
            if (!file_stream_.good())
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

        /// @brief Close the stream.
        auto close() -> void override
        {
            if (file_stream_.is_open())
            {
                file_stream_.close();
            }
        }

        /// @brief Check if the stream supports marking.
        /// @return True if the stream supports marking, false otherwise.
        [[nodiscard]] auto markSupported() const -> bool override
        {
            return false;
        }

    private:
        std::ifstream file_stream_;
        std::string file_name_{};
    };
}
