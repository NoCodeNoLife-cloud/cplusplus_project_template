#pragma once
#include <openssl/evp.h>
#include <windows.h>

#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <iomanip>

namespace fox
{
    /// @brief A class representing a file in the file system
    /// This class provides various operations that can be performed on files,
    /// such as checking permissions, creating, deleting, renaming, and retrieving
    /// file properties like size, modification time, and path information.
    class File final
    {
    public:
        explicit File(const std::string& path);

        explicit File(std::filesystem::path path);

        explicit File(const char* path);

        ~File();

        /// @brief Checks if the file can be executed
        /// @return true if the file can be executed, false otherwise
        [[nodiscard]] auto canExecute() const noexcept -> bool;

        /// @brief Checks if the file can be read
        /// @return true if the file can be read, false otherwise
        [[nodiscard]] auto canRead() const noexcept -> bool;

        /// @brief Checks if the file can be written to
        /// @return true if the file can be written to, false otherwise
        [[nodiscard]] auto canWrite() const noexcept -> bool;

        /// @brief Creates a new file
        /// @return true if the file was created successfully, false otherwise
        [[nodiscard]] auto createNewFile() const -> bool;

        /// @brief Deletes the file
        /// @return true if the file was deleted successfully, false otherwise
        [[nodiscard]] auto deleteFile() const noexcept -> bool;

        /// @brief Checks if the file exists
        /// @return true if the file exists, false otherwise
        [[nodiscard]] auto exists() const noexcept -> bool;

        /// @brief Gets the absolute path of the file
        /// @return The absolute path as a string
        [[nodiscard]] auto getAbsolutePath() const -> std::string;

        /// @brief Gets the absolute file object
        /// @return A File object representing the absolute path
        [[nodiscard]] auto getAbsoluteFile() const -> File;

        /// @brief Gets the name of the file
        /// @return The file name as a string
        [[nodiscard]] auto getName() const noexcept -> std::string;

        /// @brief Gets the parent directory path
        /// @return The parent directory path as a string
        [[nodiscard]] auto getParent() const noexcept -> std::string;

        /// @brief Gets the parent directory as a File object
        /// @return A File object representing the parent directory
        [[nodiscard]] auto getParentFile() const -> File;

        /// @brief Gets the file path
        /// @return The file path as a string
        [[nodiscard]] auto getPath() const noexcept -> std::string;

        /// @brief Gets the total space of the file system
        /// @return The total space in bytes
        [[nodiscard]] auto getTotalSpace() const noexcept -> int64_t;

        /// @brief Gets the usable space of the file system
        /// @return The usable space in bytes
        [[nodiscard]] auto getUsableSpace() const noexcept -> int64_t;

        /// @brief Gets the hash code of the file path
        /// @return The hash code as a size_t
        [[nodiscard]] auto hashCode() const noexcept -> size_t;

        /// @brief Checks if the file path is absolute
        /// @return true if the path is absolute, false otherwise
        [[nodiscard]] auto isAbsolute() const noexcept -> bool;

        /// @brief Renames the file to the destination file
        /// @param dest The destination file
        /// @return true if the file was renamed successfully, false otherwise
        [[nodiscard]] auto renameTo(const File& dest) const noexcept -> bool;

        /// @brief Checks if the path refers to a regular file
        /// @return true if it's a regular file, false otherwise
        [[nodiscard]] auto isFile() const noexcept -> bool;

        /// @brief Checks if the file is hidden
        /// @return true if the file is hidden, false otherwise
        [[nodiscard]] auto isHidden() const noexcept -> bool;

        /// @brief Gets the length of the file
        /// @return The file length in bytes
        [[nodiscard]] auto length() const noexcept -> int64_t;

        /// @brief Gets the last modified time of the file
        /// @return The last modified time as a timestamp
        [[nodiscard]] auto lastModified() const noexcept -> int64_t;

        /// @brief Converts the file path to a URI string
        /// @return The URI as a string
        [[nodiscard]] auto toURI() const noexcept -> std::string;

        /// @brief Prints files with depth information
        /// @param file_path The path to start printing from
        static auto printFilesWithDepth(const std::filesystem::path& file_path) -> void;

        /// @brief Gets the MD5 hash of a file
        /// @param filePath The path to the file
        /// @return The MD5 hash as a string
        static auto getFileMD5(const std::filesystem::path& filePath) -> std::string;

        /// @brief Copies the file to the destination path
        /// @param dest The destination file path
        /// @return true if the file was copied successfully, false otherwise
        [[nodiscard]] auto copyTo(const File& dest) const -> bool;

        /// @brief Gets the file extension
        /// @return The file extension as a string (including the dot)
        [[nodiscard]] auto getExtension() const noexcept -> std::string;

        /// @brief Sets the last modified time of the file
        /// @param time The time to set as last modified time
        /// @return true if the time was set successfully, false otherwise
        [[nodiscard]] auto setLastModified(int64_t time) const noexcept -> bool;

        /// @brief Sets the file as read-only
        /// @return true if the file was set as read-only successfully, false otherwise
        [[nodiscard]] auto setReadOnly() const noexcept -> bool;

        /// @brief Gets the file size in a human-readable format
        /// @return The file size as a string with appropriate units (B, KB, MB, GB)
        [[nodiscard]] auto getSizeString() const noexcept -> std::string;

    private:
        std::filesystem::path file_path_;
    };

    inline File::File(const std::string& path) : file_path_(path)
    {
    }

    inline File::File(std::filesystem::path path) : file_path_(std::move(path))
    {
    }

    inline File::File(const char* path) : file_path_(path)
    {
    }

    inline File::~File() = default;

    inline auto File::canExecute() const noexcept -> bool
    {
        const DWORD attributes = GetFileAttributesW(file_path_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    inline auto File::canRead() const noexcept -> bool
    {
        const std::ifstream file(file_path_);
        return file.good();
    }

    inline auto File::canWrite() const noexcept -> bool
    {
        const std::ofstream file(file_path_, std::ios::app);
        return file.good();
    }

    inline auto File::createNewFile() const -> bool
    {
        if (std::filesystem::exists(file_path_))
        {
            return false;
        }
        const std::ofstream file(file_path_);
        return file.good();
    }

    inline auto File::deleteFile() const noexcept -> bool
    {
        try
        {
            return std::filesystem::remove(file_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto File::exists() const noexcept -> bool
    {
        try
        {
            return std::filesystem::exists(file_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto File::getAbsolutePath() const -> std::string
    {
        try
        {
            return std::filesystem::absolute(file_path_).string();
        }
        catch (...)
        {
            return file_path_.string();
        }
    }

    inline auto File::getAbsoluteFile() const -> File
    {
        try
        {
            return File(std::filesystem::absolute(file_path_).string());
        }
        catch (...)
        {
            return File(file_path_.string());
        }
    }

    inline auto File::getName() const noexcept -> std::string
    {
        return file_path_.filename().string();
    }

    inline auto File::getParent() const noexcept -> std::string
    {
        return file_path_.parent_path().string();
    }

    inline auto File::getParentFile() const -> File
    {
        return file_path_.has_parent_path() ? File(file_path_.parent_path()) : File(std::string(""));
    }

    inline auto File::getPath() const noexcept -> std::string
    {
        return file_path_.string();
    }

    inline auto File::getTotalSpace() const noexcept -> int64_t
    {
        try
        {
            const auto spaceInfo = std::filesystem::space(file_path_);
            return static_cast<int64_t>(spaceInfo.capacity);
        }
        catch (...)
        {
            return 0;
        }
    }

    inline auto File::getUsableSpace() const noexcept -> int64_t
    {
        try
        {
            const auto spaceInfo = std::filesystem::space(file_path_);
            return static_cast<int64_t>(spaceInfo.free);
        }
        catch (...)
        {
            return 0;
        }
    }

    inline auto File::hashCode() const noexcept -> size_t
    {
        return std::hash<std::string>{}(file_path_.string());
    }

    inline auto File::isAbsolute() const noexcept -> bool
    {
        return file_path_.is_absolute();
    }

    inline auto File::renameTo(const File& dest) const noexcept -> bool
    {
        try
        {
            std::filesystem::rename(file_path_, dest.file_path_);
            return true;
        }
        catch (const std::filesystem::filesystem_error&)
        {
            return false;
        }
    }

    inline auto File::isFile() const noexcept -> bool
    {
        try
        {
            return std::filesystem::is_regular_file(file_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto File::isHidden() const noexcept -> bool
    {
        const DWORD attributes = GetFileAttributesW(file_path_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
    }

    inline auto File::length() const noexcept -> int64_t
    {
        try
        {
            if (std::filesystem::exists(file_path_) && std::filesystem::is_regular_file(file_path_))
            {
                return static_cast<int64_t>(std::filesystem::file_size(file_path_));
            }
            return 0;
        }
        catch (...)
        {
            return 0;
        }
    }

    inline auto File::lastModified() const noexcept -> int64_t
    {
        try
        {
            const auto lastWriteTime = std::filesystem::last_write_time(file_path_);
            const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
            return std::chrono::system_clock::to_time_t(sctp);
        }
        catch (...)
        {
            return 0;
        }
    }

    inline auto File::toURI() const noexcept -> std::string
    {
        return "file://" + file_path_.string();
    }

    inline auto File::printFilesWithDepth(const std::filesystem::path& file_path) -> void
    {
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_directory(file_path))
        {
            throw std::runtime_error("Invalid directory path: " + file_path.string());
        }

        for (auto it_entry = std::filesystem::recursive_directory_iterator(file_path);
             it_entry != std::filesystem::recursive_directory_iterator{}; ++it_entry)
        {
            const auto& entry = *it_entry;
            const auto depth = it_entry.depth();

            std::cout << std::string(static_cast<size_t>(depth * 2), ' ');

            if (entry.is_directory())
            {
                std::cout << "[DIR]" << entry.path().filename().string() << std::endl;
            }
            else
            {
                std::cout << "[FILE]" << entry.path().filename().string() << std::endl;
            }
        }
    }

    inline auto File::getFileMD5(const std::filesystem::path& filePath) -> std::string
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
        std::array<char, bufferSize> buffer{};
        while (file.read(buffer.data(), static_cast<std::streamsize>(bufferSize)))
        {
            if (const auto bytesRead = static_cast<size_t>(file.gcount());
                EVP_DigestUpdate(mdContext.get(), buffer.data(), bytesRead) != 1)
            {
                throw std::runtime_error("MD5 update failed");
            }
        }
        if (const auto bytesRead = static_cast<size_t>(file.gcount()); bytesRead > 0)
        {
            if (EVP_DigestUpdate(mdContext.get(), buffer.data(), bytesRead) != 1)
            {
                throw std::runtime_error("MD5 update failed");
            }
        }

        std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
        unsigned int digestLength = 0;
        if (EVP_DigestFinal_ex(mdContext.get(), digest.data(), &digestLength) != 1)
        {
            throw std::runtime_error("MD5 finalization failed");
        }

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (unsigned int i = 0; i < digestLength; ++i)
        {
            oss << std::setw(2) << static_cast<unsigned>(digest[i]);
        }

        return oss.str();
    }

    // Implementation of new functions

    inline auto File::copyTo(const File& dest) const -> bool
    {
        try
        {
            std::filesystem::copy_file(file_path_, dest.file_path_, std::filesystem::copy_options::overwrite_existing);
            return true;
        }
        catch (const std::filesystem::filesystem_error&)
        {
            return false;
        }
    }

    inline auto File::getExtension() const noexcept -> std::string
    {
        try
        {
            const auto extension = file_path_.extension();
            return extension.string();
        }
        catch (...)
        {
            return std::string{};
        }
    }

    inline auto File::setLastModified(int64_t time) const noexcept -> bool
    {
        try
        {
            const auto timePoint = std::chrono::system_clock::from_time_t(static_cast<time_t>(time));
            const auto fileTime = std::chrono::time_point_cast<std::filesystem::file_time_type::duration>(
                timePoint - std::chrono::system_clock::now() + std::filesystem::file_time_type::clock::now());
            std::filesystem::last_write_time(file_path_, fileTime);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto File::setReadOnly() const noexcept -> bool
    {
        try
        {
            const DWORD attributes = GetFileAttributesW(file_path_.c_str());
            if (attributes == INVALID_FILE_ATTRIBUTES)
            {
                return false;
            }

            if (SetFileAttributesW(file_path_.c_str(), attributes | FILE_ATTRIBUTE_READONLY))
            {
                return true;
            }
            return false;
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto File::getSizeString() const noexcept -> std::string
    {
        const auto size = length();
        if (size < 0)
        {
            return "Unknown";
        }

        constexpr int64_t KB = 1024;
        constexpr int64_t MB = KB * 1024;
        constexpr int64_t GB = MB * 1024;

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);

        if (size >= GB)
        {
            oss << static_cast<double>(size) / GB << " GB";
        }
        else if (size >= MB)
        {
            oss << static_cast<double>(size) / MB << " MB";
        }
        else if (size >= KB)
        {
            oss << static_cast<double>(size) / KB << " KB";
        }
        else
        {
            oss << size << " B";
        }

        return oss.str();
    }
}
