#include "HttpCookie.hpp"
#include <utility>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

namespace common::net
{
    HttpCookie::HttpCookie(std::string name, std::string value): name_(std::move(name)), value_(std::move(value)) {}

    auto HttpCookie::setDomain(const std::string& domain) -> void
    {
        domain_ = domain;
    }

    auto HttpCookie::setPath(const std::string& path) -> void
    {
        path_ = path;
    }

    auto HttpCookie::setSecure(const bool secure) -> void
    {
        secure_ = secure;
    }

    auto HttpCookie::setHttpOnly(const bool httpOnly) -> void
    {
        httpOnly_ = httpOnly;
    }

    auto HttpCookie::setMaxAge(std::chrono::seconds maxAge) -> void
    {
        maxAge_ = maxAge;
        expiry_ = std::chrono::system_clock::now() + maxAge;
    }

    auto HttpCookie::setExpiry(const std::chrono::system_clock::time_point& expiry) -> void
    {
        expiry_ = expiry;
    }

    auto HttpCookie::getName() const -> std::string
    {
        return name_;
    }

    auto HttpCookie::getValue() const -> std::string
    {
        return value_;
    }

    auto HttpCookie::getDomain() const -> std::optional<std::string>
    {
        return domain_;
    }

    auto HttpCookie::getPath() const -> std::optional<std::string>
    {
        return path_;
    }

    auto HttpCookie::isSecure() const -> bool
    {
        return secure_;
    }

    auto HttpCookie::isHttpOnly() const -> bool
    {
        return httpOnly_;
    }

    auto HttpCookie::getExpiry() const -> std::optional<std::chrono::system_clock::time_point>
    {
        return expiry_;
    }

    auto HttpCookie::isExpired() const -> bool
    {
        if (expiry_)
        {
            return std::chrono::system_clock::now() > expiry_.value();
        }
        return false;
    }

    auto HttpCookie::toString() const -> std::string
    {
        std::ostringstream oss;
        oss << name_ << "=" << value_;
        if (domain_) oss << "; Domain=" << domain_.value();
        if (path_) oss << "; Path=" << path_.value();
        if (secure_) oss << "; Secure";
        if (httpOnly_) oss << "; HttpOnly";
        if (expiry_)
        {
            const auto expiry_time_t = std::chrono::system_clock::to_time_t(expiry_.value());
            oss << "; Expires=" << std::put_time(std::gmtime(&expiry_time_t), "%a, %d-%b-%Y %H:%M:%S GMT");
        }
        return oss.str();
    }

    auto HttpCookie::parse(const std::string& setCookieHeader) -> HttpCookie
    {
        std::istringstream stream(setCookieHeader);
        std::string token;
        std::string name, value;
        std::optional<std::string> domain;
        std::optional<std::string> path;
        std::optional<std::chrono::system_clock::time_point> expiry;
        bool secure = false;
        bool httpOnly = false;
        while (std::getline(stream, token, ';'))
        {
            if (auto pos = token.find('='); pos != std::string::npos)
            {
                std::string key = token.substr(0, pos);
                std::string val = token.substr(pos + 1);
                if (key == "Domain")
                {
                    domain = val;
                }
                else if (key == "Path")
                {
                    path = val;
                }
                else if (key == "Expires")
                {
                    std::istringstream dateStream(val);
                    std::tm tm = {};
                    dateStream >> std::get_time(&tm, "%a, %d-%b-%Y %H:%M:%S GMT");
                    expiry = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                }
                else if (key.empty())
                {
                    secure = (val == "Secure");
                }
                else if (key == "HttpOnly")
                {
                    httpOnly = true;
                }
                else
                {
                    if (name.empty())
                    {
                        name = key;
                        value = val;
                    }
                }
            }
        }
        HttpCookie cookie(name, value);
        if (domain) cookie.setDomain(domain.value());
        if (path) cookie.setPath(path.value());
        if (expiry) cookie.setExpiry(expiry.value());
        cookie.setSecure(secure);
        cookie.setHttpOnly(httpOnly);
        return cookie;
    }
}
