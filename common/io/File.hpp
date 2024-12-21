#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "entity/interface/IfaceComparable.hpp"

namespace common::io
{
    class File final : public iface::IfaceComparable<File>
    {
    public:
        explicit File(const std::string& path) : filePath_(path)
        {
        }

        explicit File(std::filesystem::path path) : filePath_(std::move(path))
        {
        }

        explicit File(const char* path) : filePath_(path)
        {
        }

        ~File() override = default;

        [[nodiscard]] auto compareTo(const File& other) const -> int override
        {
            return filePath_.string().compare(other.filePath_.string());
        }

        [[nodiscard]] auto equals(const File& other) const -> bool override
        {
            return equivalent(filePath_, other.filePath_);
        }

        [[nodiscard]] auto canExecute() const -> bool
        {
            const DWORD attributes = GetFileAttributesW(filePath_.c_str());
            return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
        }

        [[nodiscard]] auto canRead() const -> bool
        {
            const std::ifstream file(filePath_);
            return file.good();
        }

        [[nodiscard]] auto canWrite() const -> bool
        {
            const std::ofstream file(filePath_, std::ios::app);
            return file.good();
        }

        [[nodiscard]] auto createNewFile() const -> bool
        {
            if (std::filesystem::exists(filePath_))
            {
                return false;
            }
            const std::ofstream file(filePath_);
            return file.good();
        }

        static auto createTempFile(const std::string& prefix, const std::string& suffix,
                                   const std::string& directory) -> File
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

        [[nodiscard]] auto deleteFile() const -> bool
        {
            return std::filesystem::remove(filePath_);
        }

        [[nodiscard]] auto exists() const -> bool
        {
            return std::filesystem::exists(filePath_);
        }

        [[nodiscard]] auto getAbsolutePath() const -> std::string
        {
            return absolute(filePath_).string();
        }

        [[nodiscard]] auto getAbsoluteFile() const -> File
        {
            return File(absolute(filePath_).string());
        }

        [[nodiscard]] auto getName() const -> std::string
        {
            return filePath_.filename().string();
        }

        [[nodiscard]] auto getParent() const -> std::string
        {
            return filePath_.parent_path().string();
        }

        [[nodiscard]] auto getCanonicalFile() const -> File
        {
            return File(canonical(filePath_));
        }

        [[nodiscard]] auto getParentFile() const -> File
        {
            return filePath_.has_parent_path() ? File(filePath_.parent_path()) : File(std::string(""));
        }

        [[nodiscard]] auto getPath() const -> std::string
        {
            return filePath_.string();
        }

        [[nodiscard]] auto getTotalSpace() const -> long
        {
            const auto spaceInfo = space(filePath_);
            return static_cast<long>(spaceInfo.capacity);
        }

        [[nodiscard]] auto getUsableSpace() const -> long
        {
            const auto spaceInfo = space(filePath_);
            return static_cast<long>(spaceInfo.free);
        }

        [[nodiscard]] auto hashCode() const -> size_t
        {
            return std::hash<std::string>()(filePath_.string());
        }

        [[nodiscard]] auto isAbsolute() const -> bool
        {
            return filePath_.is_absolute();
        }

        [[nodiscard]] auto mkdir() const -> bool
        {
            return create_directory(filePath_);
        }

        [[nodiscard]] auto renameTo(const File& dest) const -> bool
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

        [[nodiscard]] auto isDirectory() const -> bool
        {
            return is_directory(filePath_);
        }

        [[nodiscard]] auto isFile() const -> bool
        {
            return is_regular_file(filePath_);
        }

        [[nodiscard]] auto isHidden() const -> bool
        {
            const DWORD attributes = GetFileAttributesW(filePath_.c_str());
            return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
        }

        [[nodiscard]] auto length() const -> long long
        {
            if (std::filesystem::exists(filePath_) && is_regular_file(filePath_))
            {
                return static_cast<long long>(file_size(filePath_));
            }
            return 0;
        }

        [[nodiscard]] auto lastModified() const -> long long
        {
            const auto lastWriteTime = last_write_time(filePath_);
            const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
            return std::chrono::system_clock::to_time_t(sctp);
        }

        [[nodiscard]] auto list() const -> std::vector<std::string>
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

        [[nodiscard]] auto toString() const -> std::string
        {
            return std::format("{}", *this);
        }

        [[nodiscard]] auto toURI() const -> std::string
        {
            return "file://" + filePath_.string();
        }

    private:
        std::filesystem::path filePath_;
        friend std::formatter<File>;
    };
}

template <>
struct std::formatter<common::io::File>
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
