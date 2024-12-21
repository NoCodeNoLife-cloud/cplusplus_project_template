#include "File.hpp"
#include <fstream>

namespace common::io
{
    File::File(const std::string& path): filePath_(path) {}

    File::File(std::filesystem::path path): filePath_(std::move(path)) {}

    File::File(const char* path): filePath_(path) {}

    File::~File() = default;

    auto File::compareTo(const File& other) const -> int32_t
    {
        return filePath_.string().compare(other.filePath_.string());
    }

    auto File::equals(const File& other) const -> bool
    {
        return equivalent(filePath_, other.filePath_);
    }

    auto File::canExecute() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(filePath_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    auto File::canRead() const -> bool
    {
        const std::ifstream file(filePath_);
        return file.good();
    }

    auto File::canWrite() const -> bool
    {
        const std::ofstream file(filePath_, std::ios::app);
        return file.good();
    }

    auto File::createNewFile() const -> bool
    {
        if (std::filesystem::exists(filePath_))
        {
            return false;
        }
        const std::ofstream file(filePath_);
        return file.good();
    }

    auto File::createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory) -> File
    {
        char tempPath[MAX_PATH];
        if (directory.empty())
        {
            GetTempPath(MAX_PATH, tempPath);
        }
        else
        {
            strncpy_s(tempPath, directory.c_str(), MAX_PATH);
        }
        char tempFileName[MAX_PATH];
        GetTempFileName(tempPath, prefix.c_str(), 0, tempFileName);
        const std::string tempFilePath = std::string(tempFileName) + suffix;
        return File(tempFilePath);
    }

    auto File::deleteFile() const -> bool
    {
        return std::filesystem::remove(filePath_);
    }

    auto File::exists() const -> bool
    {
        return std::filesystem::exists(filePath_);
    }

    auto File::getAbsolutePath() const -> std::string
    {
        return absolute(filePath_).string();
    }

    auto File::getAbsoluteFile() const -> File
    {
        return File(absolute(filePath_).string());
    }

    auto File::getName() const -> std::string
    {
        return filePath_.filename().string();
    }

    auto File::getParent() const -> std::string
    {
        return filePath_.parent_path().string();
    }

    auto File::getCanonicalFile() const -> File
    {
        return File(canonical(filePath_));
    }

    auto File::getParentFile() const -> File
    {
        return filePath_.has_parent_path() ? File(filePath_.parent_path()) : File(std::string(""));
    }

    auto File::getPath() const -> std::string
    {
        return filePath_.string();
    }

    auto File::getTotalSpace() const -> int64_t
    {
        const auto spaceInfo = space(filePath_);
        return static_cast<int64_t>(spaceInfo.capacity);
    }

    auto File::getUsableSpace() const -> int64_t
    {
        const auto spaceInfo = space(filePath_);
        return static_cast<int64_t>(spaceInfo.free);
    }

    auto File::hashCode() const -> size_t
    {
        return std::hash<std::string>()(filePath_.string());
    }

    auto File::isAbsolute() const -> bool
    {
        return filePath_.is_absolute();
    }

    auto File::mkdir() const -> bool
    {
        return create_directory(filePath_);
    }

    auto File::renameTo(const File& dest) const -> bool
    {
        try
        {
            std::filesystem::rename(filePath_, dest.filePath_);
            return true;
        }
        catch (const std::filesystem::filesystem_error&)
        {
            return false;
        }
    }

    auto File::isDirectory() const -> bool
    {
        return is_directory(filePath_);
    }

    auto File::isFile() const -> bool
    {
        return is_regular_file(filePath_);
    }

    auto File::isHidden() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(filePath_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
    }

    auto File::length() const -> int64_t
    {
        if (std::filesystem::exists(filePath_) && is_regular_file(filePath_))
        {
            return static_cast<int64_t>(file_size(filePath_));
        }
        return 0;
    }

    auto File::lastModified() const -> int64_t
    {
        const auto lastWriteTime = last_write_time(filePath_);
        const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        return std::chrono::system_clock::to_time_t(sctp);
    }

    auto File::list() const -> std::vector<std::string>
    {
        std::vector<std::string> entries;
        if (isDirectory())
        {
            for (const auto& entry : std::filesystem::directory_iterator(filePath_))
            {
                entries.push_back(entry.path().filename().string());
            }
        }
        return entries;
    }

    auto File::toString() const -> std::string
    {
        return std::format("{}", *this);
    }

    auto File::toURI() const -> std::string
    {
        return "file://" + filePath_.string();
    }
}
