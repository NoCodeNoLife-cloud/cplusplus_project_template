#pragma once
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

namespace common::net {
/// \brief Class URL represents a URL.
/// \details This class represents a URL. It provides methods for accessing the protocol, host, port, path, query, and the whole URL.
class URL {
public:
  explicit URL(std::string url) : url_(std::move(url)), port_(0) {
    parse();
  }

  /// \brief Returns the protocol of the URL.
  /// \details This method returns the protocol of the URL, e.g. "http" or "https".
  [[nodiscard]] auto getProtocol() const -> std::string {
    return protocol_;
  }

  /// \brief Returns the host of the URL.
  /// \details This method returns the host portion of the URL, which is typically the domain name or IP address.
  /// It extracts this information from the URL string provided during object construction.
  [[nodiscard]] auto getHost() const -> std::string {
    return host_;
  }

  /// \brief Returns the port of the URL.
  /// \details This method returns the port of the URL. If no port is specified in the URL, the default port is returned.
  [[nodiscard]] auto getPort() const -> int {
    return port_;
  }

  /// \brief Returns the path of the URL.
  /// \details This method returns the path portion of the URL, which is the part following the host and port.
  /// It extracts this information from the URL string provided during object construction.
  [[nodiscard]] auto getPath() const -> std::string {
    return path_;
  }

  /// \brief Returns the query string of the URL.
  /// \details This method returns the query string of the URL, which is the part following the path.
  /// It extracts this information from the URL string provided during object construction.
  [[nodiscard]] auto getQuery() const -> std::string {
    return query_;
  }

  /// \brief Returns the whole URL.
  /// \details This method returns the whole URL string as provided during object construction.
  [[nodiscard]] auto getURL() const -> std::string {
    return url_;
  }

private:
  std::string url_;
  std::string protocol_;
  std::string host_;
  int port_;
  std::string path_;
  std::string query_;

  /// \brief Parses the URL string.
  /// \details This method uses a regular expression to extract components of the URL such as protocol, host, port, path, and query.
  /// If the URL format is invalid, it throws an invalid_argument exception.
  auto parse() -> void {
    const std::regex url_regex(R"(^(https?|ftp)://([^/:]+)(?::(\d+))?(\/[^?#]*)?(\?[^#]*)?(#.*)?$)", std::regex::extended);
    if (std::smatch url_match; std::regex_match(url_, url_match, url_regex)) {
      protocol_ = url_match[1];
      host_ = url_match[2];
      port_ = url_match[3].length() ? std::stoi(url_match[3]) : getDefaultPort(protocol_);
      path_ = url_match[4].length() ? url_match[4] : "/";
      query_ = url_match[5].length() ? url_match[5].str().substr(1) : "";
    }
    else {
      throw std::invalid_argument("Invalid URL format: " + url_);
    }
  }

  /// \brief Returns the default port number for the specified protocol.
  /// \details This method returns the default port number for the specified protocol.
  /// If the protocol is not recognized, it throws an invalid_argument exception.
  static auto getDefaultPort(const std::string& protocol) -> int {
    if (protocol == "http") return 80;
    if (protocol == "https") return 443;
    if (protocol == "ftp") return 21;
    throw std::invalid_argument("Unknown protocol: " + protocol);
  }
};
}
