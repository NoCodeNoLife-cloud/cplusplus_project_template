#include "URL.hpp"
#include <stdexcept>
#include <utility>

namespace common::net
{
    URL::URL(std::string url): url_(std::move(url)), port_(0)
    {
        parse();
    }

    auto URL::getProtocol() const -> std::string
    {
        return protocol_;
    }

    auto URL::getHost() const -> std::string
    {
        return host_;
    }

    auto URL::getPort() const -> int32_t
    {
        return port_;
    }

    auto URL::getPath() const -> std::string
    {
        return path_;
    }

    auto URL::getQuery() const -> std::string
    {
        return query_;
    }

    auto URL::getURL() const -> std::string
    {
        return url_;
    }

    auto URL::parse() -> void
    {
        const std::regex url_regex(R"(^(https?|ftp)://([^/:]+)(?::(\d+))?(\/[^?#]*)?(\?[^#]*)?(#.*)?$)", std::regex::extended);
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

    auto URL::getDefaultPort(const std::string& protocol) -> int32_t
    {
        if (protocol == "http") return 80;
        if (protocol == "https") return 443;
        if (protocol == "ftp") return 21;
        throw std::invalid_argument("Unknown protocol: " + protocol);
    }
}
