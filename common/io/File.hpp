#pragma once
#include <chrono>
#include <filesystem>
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
