#pragma once
#include <chrono>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace common::net {
/// \brief A class representing an HTTP cookie.
/// \details The HttpCookie class is used to represent an HTTP cookie.
/// It provides methods to set the name, value, domain, path, secure flag,
/// HttpOnly flag, and maximum age for the cookie. It also provides a method
/// to parse a Set-Cookie header.
class HttpCookie {
public:
  HttpCookie(std::string name, std::string value) : name_(std::move(name)), value_(std::move(value)) {}

  /// \brief Sets the domain for the cookie.
  /// \param domain The domain to set.
  auto setDomain(const std::string& domain) -> void {
    domain_ = domain;
  }

  /// \brief Sets the path for the cookie.
  /// \param path The path to set.
  auto setPath(const std::string& path) -> void {
    path_ = path;
  }

  /// \brief Sets the secure flag for the cookie.
  /// \param secure True to mark the cookie as secure, false otherwise.
  auto setSecure(const bool secure) -> void {
    secure_ = secure;
  }

  /// \brief Sets the HttpOnly flag for the cookie.
  /// \param httpOnly True to mark the cookie as HttpOnly, false otherwise.
  auto setHttpOnly(const bool httpOnly) -> void {
    httpOnly_ = httpOnly;
  }

  /// \brief Sets the maximum age for the cookie.
  /// \param maxAge The maximum age in seconds.
  auto setMaxAge(std::chrono::seconds maxAge) -> void {
    maxAge_ = maxAge;
    expiry_ = std::chrono::system_clock::now() + maxAge;
  }

  /// \brief Sets the expiry time for the cookie.
  /// \param expiry The expiry time to set.
  auto setExpiry(const std::chrono::system_clock::time_point& expiry) -> void {
    expiry_ = expiry;
  }

  /// \brief Returns the name of the cookie.
  /// \return The name of the cookie.
  [[nodiscard]] auto getName() const -> std::string {
    return name_;
  }

  /// \brief Returns the value of the cookie.
  /// \return The value of the cookie.
  [[nodiscard]] auto getValue() const -> std::string {
    return value_;
  }

  /// \brief Returns the domain of the cookie.
  /// \return The domain of the cookie or std::nullopt if it is not set.
  [[nodiscard]] auto getDomain() const -> std::optional<std::string> {
    return domain_;
  }

  /// \brief Returns the path of the cookie.
  /// \return The path of the cookie or std::nullopt if it is not set.
  [[nodiscard]] auto getPath() const -> std::optional<std::string> {
    return path_;
  }

  /// \brief Returns whether the cookie is secure.
  /// \return true if the cookie is secure, false otherwise.
  [[nodiscard]] auto isSecure() const -> bool {
    return secure_;
  }

  /// \brief Returns whether the cookie is HttpOnly.
  /// \return true if the cookie is HttpOnly, false otherwise.
  [[nodiscard]] auto isHttpOnly() const -> bool {
    return httpOnly_;
  }

  /// \brief Returns the expiry time of the cookie.
  /// \return The expiry time of the cookie as a std::optional. If the expiry time is not set, returns std::nullopt.
  /// \details This method provides the expiry time of the cookie if it has been set.
  /// The expiry time is represented as a std::chrono::system_clock::time_point.
  [[nodiscard]] auto getExpiry() const -> std::optional<std::chrono::system_clock::time_point> {
    return expiry_;
  }

  /// \brief Checks if the cookie is expired.
  /// \return true if the cookie is expired, false otherwise.
  /// \details This method checks if the cookie has expired based on the current time.
  [[nodiscard]] auto isExpired() const -> bool {
    if (expiry_) {
      return std::chrono::system_clock::now() > expiry_.value();
    }
    return false;
  }

  /// \brief Returns a string representation of the cookie.
  /// \return A string representation of the cookie.
  /// \details This method returns a string representation of the cookie in the format of a Set-Cookie header.
  [[nodiscard]] auto toString() const -> std::string {
    std::ostringstream oss;
    oss << name_ << "=" << value_;
    if (domain_) oss << "; Domain=" << domain_.value();
    if (path_) oss << "; Path=" << path_.value();
    if (secure_) oss << "; Secure";
    if (httpOnly_) oss << "; HttpOnly";
    if (expiry_) {
      const auto expiry_time_t = std::chrono::system_clock::to_time_t(expiry_.value());
      oss << "; Expires=" << std::put_time(std::gmtime(&expiry_time_t), "%a, %d-%b-%Y %H:%M:%S GMT");
    }
    return oss.str();
  }

  /// \brief Parses a Set-Cookie header into a HttpCookie object.
  /// \param setCookieHeader The Set-Cookie header to parse.
  /// \return A HttpCookie object parsed from the Set-Cookie header.
  /// \details This method parses a Set-Cookie header into a HttpCookie object. It extracts the name, value, domain, path, secure flag, and HttpOnly flag from the header.
  static auto parse(const std::string& setCookieHeader) -> HttpCookie {
    std::istringstream stream(setCookieHeader);
    std::string token;
    std::string name, value;
    std::optional<std::string> domain;
    std::optional<std::string> path;
    std::optional<std::chrono::system_clock::time_point> expiry;
    bool secure = false;
    bool httpOnly = false;
    while (std::getline(stream, token, ';')) {
      if (auto pos = token.find('='); pos != std::string::npos) {
        std::string key = token.substr(0, pos);
        std::string val = token.substr(pos + 1);
        if (key == "Domain") {
          domain = val;
        }
        else if (key == "Path") {
          path = val;
        }
        else if (key == "Expires") {
          std::istringstream dateStream(val);
          std::tm tm = {};
          dateStream >> std::get_time(&tm, "%a, %d-%b-%Y %H:%M:%S GMT");
          expiry = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
        else if (key.empty()) {
          secure = (val == "Secure");
        }
        else if (key == "HttpOnly") {
          httpOnly = true;
        }
        else {
          if (name.empty()) {
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
