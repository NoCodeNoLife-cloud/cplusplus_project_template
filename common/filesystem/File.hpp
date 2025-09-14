#pragma once
#include <openssl/evp.h>
#include <windows.h>

#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fox
{
/// @brief A class representing a file in the file system
/// This class provides various operations that can be performed on files,
/// such as checking permissions, creating, deleting, renaming, and retrieving
/// file properties like size, modification time, and path information.
class File final
{
  public:
    explicit File(const std::string &path) : file_path_(path)
    {
    }

    explicit File(std::filesystem::path path) : file_path_(std::move(path))
    {
    }

    explicit File(const char *path) : file_path_(path)
    {
    }

    ~File() = default;

    /// @brief Checks if the file can be executed
    /// @return true if the file can be executed, false otherwise
    [[nodiscard]] auto canExecute() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(file_path_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    /// @brief Checks if the file can be read
    /// @return true if the file can be read, false otherwise
    [[nodiscard]] auto canRead() const -> bool
    {
        const std::ifstream file(file_path_);
        return file.good();
    }

    /// @brief Checks if the file can be written to
    /// @return true if the file can be written to, false otherwise
    [[nodiscard]] auto canWrite() const -> bool
    {
        const std::ofstream file(file_path_, std::ios::app);
        return file.good();
    }

    /// @brief Creates a new file
    /// @return true if the file was created successfully, false otherwise
    [[nodiscard]] auto createNewFile() const -> bool
    {
        if (std::filesystem::exists(file_path_))
        {
            return false;
        }
        const std::ofstream file(file_path_);
        return file.good();
    }

    /// @brief Deletes the file
    /// @return true if the file was deleted successfully, false otherwise
    [[nodiscard]] auto deleteFile() const -> bool
    {
        return std::filesystem::remove(file_path_);
    }

    /// @brief Checks if the file exists
    /// @return true if the file exists, false otherwise
    [[nodiscard]] auto exists() const -> bool
    {
        return std::filesystem::exists(file_path_);
    }

    /// @brief Gets the absolute path of the file
    /// @return The absolute path as a string
    [[nodiscard]] auto getAbsolutePath() const -> std::string
    {
        return absolute(file_path_).string();
    }

    /// @brief Gets the absolute file object
    /// @return A File object representing the absolute path
    [[nodiscard]] auto getAbsoluteFile() const -> File
    {
        return File(absolute(file_path_).string());
    }

    /// @brief Gets the name of the file
    /// @return The file name as a string
    [[nodiscard]] auto getName() const -> std::string
    {
        return file_path_.filename().string();
    }

    /// @brief Gets the parent directory path
    /// @return The parent directory path as a string
    [[nodiscard]] auto getParent() const -> std::string
    {
        return file_path_.parent_path().string();
    }

    /// @brief Gets the parent directory as a File object
    /// @return A File object representing the parent directory
    [[nodiscard]] auto getParentFile() const -> File
    {
        return file_path_.has_parent_path() ? File(file_path_.parent_path()) : File(std::string(""));
    }

    /// @brief Gets the file path
    /// @return The file path as a string
    [[nodiscard]] auto getPath() const -> std::string
    {
        return file_path_.string();
    }

    /// @brief Gets the total space of the file system
    /// @return The total space in bytes
    [[nodiscard]] auto getTotalSpace() const -> int64_t
    {
        const auto spaceInfo = space(file_path_);
        return static_cast<int64_t>(spaceInfo.capacity);
    }

    /// @brief Gets the usable space of the file system
    /// @return The usable space in bytes
    [[nodiscard]] auto getUsableSpace() const -> int64_t
    {
        const auto spaceInfo = space(file_path_);
        return static_cast<int64_t>(spaceInfo.free);
    }

    /// @brief Gets the hash code of the file path
    /// @return The hash code as a size_t
    [[nodiscard]] auto hashCode() const -> size_t
    {
        return std::hash<std::string>()(file_path_.string());
    }

    /// @brief Checks if the file path is absolute
    /// @return true if the path is absolute, false otherwise
    [[nodiscard]] auto isAbsolute() const -> bool
    {
        return file_path_.is_absolute();
    }

    /// @brief Renames the file to the destination file
    /// @param dest The destination file
    /// @return true if the file was renamed successfully, false otherwise
    [[nodiscard]] auto renameTo(const File &dest) const -> bool
    {
        try
        {
            std::filesystem::rename(file_path_, dest.file_path_);
            return true;
        }
        catch (const std::filesystem::filesystem_error &)
        {
            return false;
        }
    }

    /// @brief Checks if the path refers to a regular file
    /// @return true if it's a regular file, false otherwise
    [[nodiscard]] auto isFile() const -> bool
    {
        return is_regular_file(file_path_);
    }

    /// @brief Checks if the file is hidden
    /// @return true if the file is hidden, false otherwise
    [[nodiscard]] auto isHidden() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(file_path_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
    }

    /// @brief Gets the length of the file
    /// @return The file length in bytes
    [[nodiscard]] auto length() const -> int64_t
    {
        if (std::filesystem::exists(file_path_) && is_regular_file(file_path_))
        {
            return static_cast<int64_t>(file_size(file_path_));
        }
        return 0;
    }

    /// @brief Gets the last modified time of the file
    /// @return The last modified time as a timestamp
    [[nodiscard]] auto lastModified() const -> int64_t
    {
        const auto lastWriteTime = last_write_time(file_path_);
        const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        return std::chrono::system_clock::to_time_t(sctp);
    }

    /// @brief Converts the file path to a URI string
    /// @return The URI as a string
    [[nodiscard]] auto toURI() const -> std::string
    {
        return "file://" + file_path_.string();
    }

    /// @brief Prints files with depth information
    /// @param file_path The path to start printing from
    static auto printFilesWithDepth(const std::filesystem::path &file_path) -> void
    {
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_directory(file_path))
        {
            throw std::runtime_error("Invalid directory path: " + file_path.string());
        }

        for (auto it_entry = std::filesystem::recursive_directory_iterator(file_path);
             it_entry != std::filesystem::recursive_directory_iterator{}; ++it_entry)
        {
            const auto &entry = *it_entry;
            const auto depth = it_entry.depth();

            std::cout << std::string(depth * 2, ' ');

            if (entry.is_directory())
            {
                std::cout << "[DIR]" << entry.path().filename() << std::endl;
            }
            else
            {
                std::cout << "[FILE]" << entry.path().filename() << std::endl;
            }
        }
    }

    /// @brief Gets the MD5 hash of a file
    /// @param filePath The path to the file
    /// @return The MD5 hash as a string
    static auto getFileMD5(const std::filesystem::path &filePath) -> std::string
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + filePath.string());
        }

        const auto mdContext =
            std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>(EVP_MD_CTX_new(), EVP_MD_CTX_free);
        if (!mdContext)
        {
            throw std::runtime_error("Failed to create MD5 context");
        }

        if (EVP_DigestInit_ex(mdContext.get(), EVP_md5(), nullptr) != 1)
        {
            throw std::runtime_error("Failed to initialize MD5 context");
        }

        constexpr size_t bufferSize = 4096;
        char buffer[bufferSize];
        while (file.read(buffer, bufferSize))
        {
            if (const auto bytesRead = static_cast<size_t>(file.gcount());
                EVP_DigestUpdate(mdContext.get(), buffer, bytesRead) != 1)
            {
                throw std::runtime_error("MD5 update failed");
            }
        }
        if (const auto bytesRead = static_cast<size_t>(file.gcount()); bytesRead > 0)
        {
            if (EVP_DigestUpdate(mdContext.get(), buffer, bytesRead) != 1)
            {
                throw std::runtime_error("MD5 update failed");
            }
        }

        std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
        uint32_t digestLength;
        if (EVP_DigestFinal_ex(mdContext.get(), digest.data(), &digestLength) != 1)
        {
            throw std::runtime_error("MD5 finalization failed");
        }

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (uint32_t i = 0; i < digestLength; ++i)
        {
            oss << std::setw(2) << static_cast<unsigned>(digest[i]);
        }

        return oss.str();
    }

  private:
    std::filesystem::path file_path_;
};
} // namespace fox