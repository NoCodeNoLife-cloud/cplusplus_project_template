#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

namespace common::net {
class InetSocketAddress {
public:
  InetSocketAddress() = default;

  /// \brief Constructs an InetSocketAddress object from a host and port number.
  /// \details The host can be an IP address or a hostname. The port number is a value between 0 and 65535.
  InetSocketAddress(const std::string& host, const unsigned short port) {
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::resolver resolver(ioContext);
    const auto endpoints = resolver.resolve(host, std::to_string(port));
    if (endpoints.empty()) {
      throw std::invalid_argument("Unable to resolve host and port");
    }
    mEndpoint = *endpoints.begin();
  }

  /// \brief Constructs an InetSocketAddress object from a TCP endpoint.
  /// \details This constructor initializes the InetSocketAddress with a given boost::asio::ip::tcp::endpoint,
  /// allowing direct manipulation and usage of the endpoint in network operations.
  explicit InetSocketAddress(boost::asio::ip::tcp::endpoint endpoint) : mEndpoint(std::move(endpoint)) {}

  /// \brief Returns the address of the InetSocketAddress object as a string.
  /// \details Depending on whether the address is an IPv4 or IPv6 address, the returned string will be in the format of
  /// "xx.xx.xx.xx" or "[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx]".
  [[nodiscard]] auto getAddress() const -> std::string {
    return mEndpoint.address().to_string();
  }

  /// \brief Returns the port number of the InetSocketAddress object.
  /// \details This method returns the port number associated with the InetSocketAddress object as an unsigned short value.
  [[nodiscard]] auto getPort() const -> unsigned short {
    return mEndpoint.port();
  }

  /// \brief Creates an InetSocketAddress object from a string in the format "host:port".
  /// \details This static method takes a string argument representing a host and port number in the format "host:port"
  /// and returns an InetSocketAddress object with the specified host and port number.
  /// The host can be an IP address or a hostname. The port number is a value between 0 and 65535.
  static auto fromString(const std::string& str) -> InetSocketAddress {
    const size_t colonPos = str.find(':');
    if (colonPos == std::string::npos) {
      throw std::invalid_argument("Invalid address format. Expected host:port");
    }
    std::string host = str.substr(0, colonPos);
    unsigned short port = std::stoi(str.substr(colonPos + 1));
    return {host, port};
  }

  /// \brief Compares two InetSocketAddress objects for equality.
  /// \details This method compares two InetSocketAddress objects and returns true if they are equal, false otherwise.
  /// Two InetSocketAddress objects are considered equal if their addresses and port numbers are equal.
  auto operator==(const InetSocketAddress& other) const -> bool {
    return mEndpoint == other.mEndpoint;
  }

  /// \brief Compares two InetSocketAddress objects for inequality.
  /// \details This method compares two InetSocketAddress objects and returns true if they are not equal, false otherwise.
  /// Two InetSocketAddress objects are considered not equal if their addresses or port numbers are not equal.
  auto operator!=(const InetSocketAddress& other) const -> bool {
    return !(*this == other);
  }

  /// \brief Prints the address and port of the InetSocketAddress object.
  /// \details This method outputs the address and port number of the InetSocketAddress object
  /// to the standard output stream in the format "Address: <address>, Port: <port>".
  auto print() const -> void {
    std::cout << "Address: " << getAddress() << ", Port: " << getPort() << std::endl;
  }

private:
  boost::asio::ip::tcp::endpoint mEndpoint{};
};
}
