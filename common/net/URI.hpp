#pragma once
#include <string>
#include <boost/url.hpp>

namespace common::io {
/// \brief Class URI represents a resource on the network.
/// \details This class wraps a boost::urls::url object and provides a simpler interface for working with URIs.
class URI {
public:
  explicit URI(const std::string& uri_str) {
    try {
      url_ = boost::urls::url(uri_str);
    }
    catch (const std::exception& e) {
      throw std::invalid_argument("Invalid URI: " + std::string(e.what()));
    }
  }

  /// \brief Constructor taking a URI string.
  /// \details This constructor takes a string representing a URI and parses it.
  /// If the string is not a valid URI, it throws an exception.
  [[nodiscard]] auto scheme() const -> std::string {
    return url_.scheme();
  }

  /// \brief Returns the scheme of this URI.
  /// \details This method returns the scheme of this URI or an empty string if not present.
  /// The scheme is the first part of the authority component of a URI.
  [[nodiscard]] auto host() const -> std::string {
    return url_.host();
  }

  /// \brief Returns the host of this URI.
  /// \details This method returns the host of this URI or an empty string if not present.
  /// The host is the second part of the authority component of a URI.
  [[nodiscard]] auto path() const -> std::string {
    return url_.path();
  }

  /// \brief Returns the path of this URI.
  /// \details This method returns the path of this URI or an empty string if not present.
  /// The path is the third part of the authority component of a URI.
  [[nodiscard]] auto query() const -> std::string {
    return url_.query();
  }

  /// \brief Returns the port of this URI.
  /// \details This method returns the port of this URI or an empty string if not present.
  /// The port is the optional part of the authority component of a URI.
  [[nodiscard]] auto port() const -> std::string {
    return url_.port();
  }

  /// \brief Converts the URI object to its string representation.
  /// \details This method returns a string representation of the URI object,
  /// including its scheme, host, path, query, and port components.
  [[nodiscard]] auto toString() const -> std::string {
    std::string result;
    result += "Scheme: " + scheme() + "\n";
    result += "Host: " + host() + "\n";
    result += "Path: " + path() + "\n";
    result += "Query: " + query() + "\n";
    result += "Port: " + port() + "\n";
    return result;
  }

  /// \brief Parses a URI string into a URI object.
  /// \param uri_str The URI string to be parsed.
  /// \return A URI object created from the provided URI string.
  /// \details This static method takes a URI string as input and returns a URI object.
  /// It constructs the URI object using the given string, allowing access to its components.
  static auto parse(const std::string& uri_str) -> URI {
    return URI(uri_str);
  }

private:
  boost::urls::url url_;
};
}
