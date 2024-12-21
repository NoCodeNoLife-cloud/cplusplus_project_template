#pragma once
#include <regex>
#include <string>

namespace common::net
{
    class URL
    {
    public:
        explicit URL(std::string url);
        [[nodiscard]] auto getProtocol() const -> std::string;
        [[nodiscard]] auto getHost() const -> std::string;
        [[nodiscard]] auto getPort() const -> int32_t;
        [[nodiscard]] auto getPath() const -> std::string;
        [[nodiscard]] auto getQuery() const -> std::string;
        [[nodiscard]] auto getURL() const -> std::string;
    private:
        std::string url_;
        std::string protocol_;
        std::string host_;
        int32_t port_;
        std::string path_;
        std::string query_;
        auto parse() -> void;
        static auto getDefaultPort(const std::string& protocol) -> int32_t;
    };
}
