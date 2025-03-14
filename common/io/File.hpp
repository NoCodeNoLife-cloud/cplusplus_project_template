#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "entity/interface/IComparable.hpp"

namespace common::io
{
    class File final : public iface::IComparable<File>
    {
    public:
        explicit File(const std::string& path);
        explicit File(std::filesystem::path path);
        explicit File(const char* path);
        ~File() override;
        [[nodiscard]] auto compareTo(const File& other) const -> int32_t override;
        [[nodiscard]] auto equals(const File& other) const -> bool override;
        [[nodiscard]] auto canExecute() const -> bool;
        [[nodiscard]] auto canRead() const -> bool;
        [[nodiscard]] auto canWrite() const -> bool;
        [[nodiscard]] auto createNewFile() const -> bool;
        static auto createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory) -> File;
        [[nodiscard]] auto deleteFile() const -> bool;
        [[nodiscard]] auto exists() const -> bool;
        [[nodiscard]] auto getAbsolutePath() const -> std::string;
        [[nodiscard]] auto getAbsoluteFile() const -> File;
        [[nodiscard]] auto getName() const -> std::string;
        [[nodiscard]] auto getParent() const -> std::string;
        [[nodiscard]] auto getCanonicalFile() const -> File;
        [[nodiscard]] auto getParentFile() const -> File;
        [[nodiscard]] auto getPath() const -> std::string;
        [[nodiscard]] auto getTotalSpace() const -> int64_t;
        [[nodiscard]] auto getUsableSpace() const -> int64_t;
        [[nodiscard]] auto hashCode() const -> size_t;
        [[nodiscard]] auto isAbsolute() const -> bool;
        [[nodiscard]] auto mkdir() const -> bool;
        [[nodiscard]] auto renameTo(const File& dest) const -> bool;
        [[nodiscard]] auto isDirectory() const -> bool;
        [[nodiscard]] auto isFile() const -> bool;
        [[nodiscard]] auto isHidden() const -> bool;
        [[nodiscard]] auto length() const -> int64_t;
        [[nodiscard]] auto lastModified() const -> int64_t;
        [[nodiscard]] auto list() const -> std::vector<std::string>;
        [[nodiscard]] auto toString() const -> std::string;
        [[nodiscard]] auto toURI() const -> std::string;
    private:
        std::filesystem::path filePath_;
        friend std::formatter<File>;
    };

    inline File::File(const std::string& path): filePath_(path) {}

    inline File::File(std::filesystem::path path): filePath_(std::move(path)) {}

    inline File::File(const char* path): filePath_(path) {}

    inline File::~File() = default;

    inline auto File::compareTo(const File& other) const -> int32_t
    {
        return filePath_.string().compare(other.filePath_.string());
    }

    inline auto File::equals(const File& other) const -> bool
    {
        return equivalent(filePath_, other.filePath_);
    }

    inline auto File::canExecute() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(filePath_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    inline auto File::canRead() const -> bool
    {
        const std::ifstream file(filePath_);
        return file.good();
    }

    inline auto File::canWrite() const -> bool
    {
        const std::ofstream file(filePath_, std::ios::app);
        return file.good();
    }

    inline auto File::createNewFile() const -> bool
    {
        if (std::filesystem::exists(filePath_))
        {
            return false;
        }
        const std::ofstream file(filePath_);
        return file.good();
    }

    inline auto File::createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory) -> File
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

    inline auto File::deleteFile() const -> bool
    {
        return std::filesystem::remove(filePath_);
    }

    inline auto File::exists() const -> bool
    {
        return std::filesystem::exists(filePath_);
    }

    inline auto File::getAbsolutePath() const -> std::string
    {
        return absolute(filePath_).string();
    }

    inline auto File::getAbsoluteFile() const -> File
    {
        return File(absolute(filePath_).string());
    }

    inline auto File::getName() const -> std::string
    {
        return filePath_.filename().string();
    }

    inline auto File::getParent() const -> std::string
    {
        return filePath_.parent_path().string();
    }

    inline auto File::getCanonicalFile() const -> File
    {
        return File(canonical(filePath_));
    }

    inline auto File::getParentFile() const -> File
    {
        return filePath_.has_parent_path() ? File(filePath_.parent_path()) : File(std::string(""));
    }

    inline auto File::getPath() const -> std::string
    {
        return filePath_.string();
    }

    inline auto File::getTotalSpace() const -> int64_t
    {
        const auto spaceInfo = space(filePath_);
        return static_cast<int64_t>(spaceInfo.capacity);
    }

    inline auto File::getUsableSpace() const -> int64_t
    {
        const auto spaceInfo = space(filePath_);
        return static_cast<int64_t>(spaceInfo.free);
    }

    inline auto File::hashCode() const -> size_t
    {
        return std::hash<std::string>()(filePath_.string());
    }

    inline auto File::isAbsolute() const -> bool
    {
        return filePath_.is_absolute();
    }

    inline auto File::mkdir() const -> bool
    {
        return create_directory(filePath_);
    }

    inline auto File::renameTo(const File& dest) const -> bool
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

    inline auto File::isDirectory() const -> bool
    {
        return is_directory(filePath_);
    }

    inline auto File::isFile() const -> bool
    {
        return is_regular_file(filePath_);
    }

    inline auto File::isHidden() const -> bool
    {
        const DWORD attributes = GetFileAttributesW(filePath_.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
    }

    inline auto File::length() const -> int64_t
    {
        if (std::filesystem::exists(filePath_) && is_regular_file(filePath_))
        {
            return static_cast<int64_t>(file_size(filePath_));
        }
        return 0;
    }

    inline auto File::lastModified() const -> int64_t
    {
        const auto lastWriteTime = last_write_time(filePath_);
        const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        return std::chrono::system_clock::to_time_t(sctp);
    }

    inline auto File::list() const -> std::vector<std::string>
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

    inline auto File::toString() const -> std::string
    {
        return std::format("{}", *this);
    }

    inline auto File::toURI() const -> std::string
    {
        return "file://" + filePath_.string();
    }
}

template <> struct std::formatter<common::io::File>
{
    constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator
    {
        const auto begin = ctx.begin();
        if (const auto end = ctx.end(); begin != end && *begin != '}')
        {
            throw std::format_error("invalid format");
        }
        return begin;
    }

    static auto format(const common::io::File& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
    {
        return std::format_to(ctx.out(), "File{{path: {}}}", content.filePath_.string());
    }
};

inline auto operator<<(std::ostream& os, const common::io::File& content) -> std::ostream&
{
    return os << std::format("{}", content);
}
