#pragma once
#include <chrono>
#include <optional>
#include <string>


namespace common::net
{
    class HttpCookie
    {
    public:
        HttpCookie(std::string name, std::string value);
        auto setDomain(const std::string& domain) -> void;
        auto setPath(const std::string& path) -> void;
        auto setSecure(bool secure) -> void;
        auto setHttpOnly(bool httpOnly) -> void;
        auto setMaxAge(std::chrono::seconds maxAge) -> void;
        auto setExpiry(const std::chrono::system_clock::time_point& expiry) -> void;
        [[nodiscard]] auto getName() const -> std::string;
        [[nodiscard]] auto getValue() const -> std::string;
        [[nodiscard]] auto getDomain() const -> std::optional<std::string>;
        [[nodiscard]] auto getPath() const -> std::optional<std::string>;
        [[nodiscard]] auto isSecure() const -> bool;
        [[nodiscard]] auto isHttpOnly() const -> bool;
        [[nodiscard]] auto getExpiry() const -> std::optional<std::chrono::system_clock::time_point>;
        [[nodiscard]] auto isExpired() const -> bool;
        [[nodiscard]] auto toString() const -> std::string;
        static auto parse(const std::string& setCookieHeader) -> HttpCookie;
    private:
        std::string name_{};
        std::string value_{};
        std::optional<std::string> domain_;
        std::optional<std::string> path_;
        std::optional<std::chrono::system_clock::time_point> expiry_;
        std::optional<std::chrono::seconds> maxAge_;
        bool secure_{false};
        bool httpOnly_{false};
    };
}
