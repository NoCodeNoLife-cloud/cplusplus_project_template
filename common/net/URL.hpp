#pragma once
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

namespace common::net
{
    class URL
    {
    public:
        explicit URL(std::string url) : url_(std::move(url)), port_(0)
        {
            parse();
        }

        [[nodiscard]] auto getProtocol() const -> std::string
        {
            return protocol_;
        }

        [[nodiscard]] auto getHost() const -> std::string
        {
            return host_;
        }

        [[nodiscard]] auto getPort() const -> int
        {
            return port_;
        }

        [[nodiscard]] auto getPath() const -> std::string
        {
            return path_;
        }

        [[nodiscard]] auto getQuery() const -> std::string
        {
            return query_;
        }

        [[nodiscard]] auto getURL() const -> std::string
        {
            return url_;
        }

    private:
        std::string url_;
        std::string protocol_;
        std::string host_;
        int port_;
        std::string path_;
        std::string query_;

        auto parse() -> void
        {
            const std::regex url_regex(R"(^(https?|ftp)://([^/:]+)(?::(\d+))?(\/[^?#]*)?(\?[^#]*)?(#.*)?$)",
                                       std::regex::extended);
            if (std::smatch url_match; std::regex_match(url_, url_match, url_regex))
            {
                protocol_ = url_match[1];
                host_ = url_match[2];
                port_ = url_match[3].length() ? std::stoi(url_match[3]) : getDefaultPort(protocol_);
                path_ = url_match[4].length() ? url_match[4] : "/";
                query_ = url_match[5].length() ? url_match[5].str().substr(1) : "";
            }
            else
            {
                throw std::invalid_argument("Invalid URL format: " + url_);
            }
        }

        static auto getDefaultPort(const std::string& protocol) -> int
        {
            if (protocol == "http") return 80;
            if (protocol == "https") return 443;
            if (protocol == "ftp") return 21;
            throw std::invalid_argument("Unknown protocol: " + protocol);
        }
    };
}
