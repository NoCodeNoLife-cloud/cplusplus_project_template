#pragma once
#include <filesystem>
#include <queue>
#include <utility>
#include <vector>
#include <optional>
#include <cstdint>
#include <chrono>

namespace fox
{
    /// @brief A class for directory operations
    /// @details This class provides various operations for directories, such as creation, deletion, listing contents, etc.
    class Directory
    {
    public:
        explicit Directory(std::filesystem::path filePath) noexcept;

        /// @brief Create a directory
        /// @return true if the directory was created successfully, false otherwise
        [[nodiscard]] auto mkdir() const noexcept -> bool;

        /// @brief Create directories recursively
        /// @param exist_ok If true, no error will be thrown if the directory already exists
        /// @return true if the directories were created successfully, false otherwise
        [[nodiscard]] auto mkdirs(bool exist_ok = false) const -> bool;

        /// @brief Check if the directory exists
        /// @return true if the directory exists, false otherwise
        [[nodiscard]] auto exists() const noexcept -> bool;

        /// @brief Check if the path is a directory
        /// @return true if the path is a directory, false otherwise
        [[nodiscard]] auto isDirectory() const noexcept -> bool;

        /// @brief List directory contents
        /// @param recursive Whether to list subdirectories recursively
        /// @return A vector of directory entries
        [[nodiscard]] auto listDir(bool recursive) const -> std::vector<std::filesystem::directory_entry>;

        /// @brief List directory contents
        /// @param dir_path The directory path to list
        /// @param recursive Whether to list subdirectories recursively
        /// @return A vector of directory entries
        [[nodiscard]] static auto listDir(const std::filesystem::path& dir_path, bool recursive)
            -> std::vector<std::filesystem::directory_entry>;

        /// @brief Remove the directory
        /// @return true if the directory was removed successfully, false otherwise
        [[nodiscard]] auto remove() const noexcept -> bool;

        /// @brief Remove the directory and all its contents
        /// @return The number of files removed
        [[nodiscard]] auto removeAll() const noexcept -> std::uintmax_t;

        /// @brief Copy the directory to a destination
        /// @param destination The destination path
        /// @return true if the directory was copied successfully, false otherwise
        [[nodiscard]] auto copy(const std::filesystem::path& destination) const -> bool;

        /// @brief Move the directory to a destination
        /// @param destination The destination path
        /// @return true if the directory was moved successfully, false otherwise
        [[nodiscard]] auto move(const std::filesystem::path& destination) const noexcept -> bool;

        /// @brief Get the size of the directory
        /// @return The size of the directory in bytes
        [[nodiscard]] auto size() const noexcept -> std::uintmax_t;

        /// @brief Get the last modified time of the directory
        /// @return The last modified time, or std::nullopt if an error occurred
        [[nodiscard]] auto lastModifiedTime() const -> std::optional<std::chrono::system_clock::time_point>;

        /// @brief Check if the directory is empty
        /// @return true if the directory is empty, false otherwise
        [[nodiscard]] auto isEmpty() const noexcept -> bool;

        /// @brief List directory entries
        /// @param recursive Whether to list subdirectories recursively
        /// @return A vector of directory entries
        [[nodiscard]] auto listEntries(
            bool recursive = false) const -> std::vector<std::filesystem::directory_entry>;

        /// @brief Clear all contents of the directory
        /// @return true if the directory was cleared successfully, false otherwise
        [[nodiscard]] auto clearAll() const -> bool;

        /// @brief Get the current working directory
        /// @return The current working directory path
        static auto getCurrentWorkingDirectory() -> std::filesystem::path;

    private:
        std::filesystem::path dir_path_;
    };

    inline Directory::Directory(std::filesystem::path filePath) noexcept : dir_path_(std::move(filePath))
    {
    }

    inline auto Directory::mkdir() const noexcept -> bool
    {
        try
        {
            return std::filesystem::create_directory(dir_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::mkdirs(const bool exist_ok) const -> bool
    {
        try
        {
            if (exist_ok)
            {
                return std::filesystem::create_directories(dir_path_);
            }
            // Check if any part of the path already exists
            if (std::filesystem::exists(dir_path_))
            {
                return false;
            }
            // For parent directories, we need to check recursively
            auto parent = dir_path_.parent_path();
            while (!parent.empty() && parent != dir_path_.root_path())
            {
                if (std::filesystem::exists(parent) && !std::filesystem::is_directory(parent))
                {
                    return false;
                }
                parent = parent.parent_path();
            }
            return std::filesystem::create_directories(dir_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::exists() const noexcept -> bool
    {
        return std::filesystem::exists(dir_path_);
    }

    inline auto Directory::isDirectory() const noexcept -> bool
    {
        return std::filesystem::is_directory(dir_path_);
    }

    inline auto Directory::listDir(const bool recursive) const -> std::vector<std::filesystem::directory_entry>
    {
        return listDir(dir_path_, recursive);
    }

    inline auto Directory::listDir(const std::filesystem::path& dir_path,
                                   const bool recursive) -> std::vector<std::filesystem::directory_entry>
    {
        std::vector<std::filesystem::directory_entry> entries;
        try
        {
            if (recursive)
            {
                for (const auto& entry : std::filesystem::recursive_directory_iterator(dir_path))
                {
                    entries.push_back(entry);
                }
            }
            else
            {
                for (const auto& entry : std::filesystem::directory_iterator(dir_path))
                {
                    entries.push_back(entry);
                }
            }
        }
        catch (...)
        {
        }
        return entries;
    }

    inline auto Directory::remove() const noexcept -> bool
    {
        try
        {
            return std::filesystem::remove(dir_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::removeAll() const noexcept -> std::uintmax_t
    {
        try
        {
            return std::filesystem::remove_all(dir_path_);
        }
        catch (...)
        {
            return 0;
        }
    }

    inline auto Directory::copy(const std::filesystem::path& destination) const -> bool
    {
        try
        {
            if (!exists() || !isDirectory())
                return false;

            if (!std::filesystem::create_directories(destination))
            {
                return false;
            }

            std::queue<std::pair<std::filesystem::path, std::filesystem::path>> dirQueue;
            dirQueue.emplace(dir_path_, destination);

            while (!dirQueue.empty())
            {
                const auto [srcPath, dstPath] = dirQueue.front();
                dirQueue.pop();

                for (const auto& entry : std::filesystem::directory_iterator(srcPath))
                {
                    const auto entryPath = entry.path();
                    const auto relativePath = entryPath.lexically_relative(srcPath);
                    const auto targetPath = dstPath / relativePath;

                    if (entry.is_directory())
                    {
                        if (!std::filesystem::create_directory(targetPath))
                        {
                            return false;
                        }
                        dirQueue.emplace(entryPath, targetPath);
                    }
                    else if (entry.is_regular_file())
                    {
                        std::filesystem::copy_file(entryPath, targetPath,
                                                   std::filesystem::copy_options::overwrite_existing);
                    }
                }
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::move(const std::filesystem::path& destination) const noexcept -> bool
    {
        try
        {
            std::filesystem::rename(dir_path_, destination);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::size() const noexcept -> std::uintmax_t
    {
        std::uintmax_t total = 0;
        try
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(dir_path_))
            {
                if (entry.is_regular_file())
                {
                    total += entry.file_size();
                }
            }
        }
        catch (...)
        {
        }
        return total;
    }

    inline auto Directory::lastModifiedTime() const -> std::optional<std::chrono::system_clock::time_point>
    {
        try
        {
            const auto ftime = std::filesystem::last_write_time(dir_path_);
            return std::chrono::clock_cast<std::chrono::system_clock>(ftime);
        }
        catch (...)
        {
            return std::nullopt;
        }
    }

    inline auto Directory::isEmpty() const noexcept -> bool
    {
        try
        {
            return std::filesystem::is_empty(dir_path_);
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::listEntries(const bool recursive) const -> std::vector<std::filesystem::directory_entry>
    {
        return listDir(dir_path_, recursive);
    }

    inline auto Directory::clearAll() const -> bool
    {
        try
        {
            if (!std::filesystem::exists(dir_path_) || !std::filesystem::is_directory(dir_path_))
            {
                return false;
            }
            for (const auto& entry : std::filesystem::directory_iterator(dir_path_))
            {
                std::filesystem::remove_all(entry.path());
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    inline auto Directory::getCurrentWorkingDirectory() -> std::filesystem::path
    {
        return std::filesystem::current_path();
    }
} // namespace fox
