#pragma once
#include <array>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <glog/logging.h>

namespace common::net {
/// \brief Represents an IP address, providing methods for address manipulation and information retrieval.
/// \details The InetAddress class supports operations such as obtaining the address in byte form,
/// determining the hostname, checking if the address is a loopback or multicast address,
/// and determining if it is reachable within a specified timeout. It also provides functionality
/// for comparing equality and generating hash codes for InetAddress objects.
class InetAddress {
public:
  InetAddress(const std::string& host, const unsigned short port) : endpoint_(boost::asio::ip::make_address(host), port) {}

  explicit InetAddress(const std::string& host) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    const boost::asio::ip::tcp::resolver::results_type results = resolver.resolve(host, "");
    endpoint_.address() = results->endpoint().address();
  }

  /// \brief Returns the address of the InetAddress object as a vector of bytes.
  /// \details Depending on whether the address is an IPv4 or IPv6 address, the size of the returned vector will be 4 bytes
  /// (for IPv4) or 16 bytes (for IPv6).
  [[nodiscard]] auto getAddress() const -> std::vector<unsigned char> {
    std::vector<unsigned char> result;
    if (endpoint_.address().is_v4()) {
      const boost::asio::ip::address_v4 v4_address = endpoint_.address().to_v4();
      result.assign(v4_address.to_bytes().begin(), v4_address.to_bytes().end());
    }
    else if (endpoint_.address().is_v6()) {
      const boost::asio::ip::address_v6 v6_address = endpoint_.address().to_v6();
      result.assign(v6_address.to_bytes().begin(), v6_address.to_bytes().end());
    }
    return result;
  }

  /// \brief Returns the address of the InetAddress object as a string.
  /// \details Depending on whether the address is an IPv4 or IPv6 address, the returned string will be in the format of
  /// "xx.xx.xx.xx" or "[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx]".
  [[nodiscard]] auto getHostAddress() const -> std::string {
    return endpoint_.address().to_string();
  }

  /// \brief Retrieves the local host address.
  /// \details This function returns an InetAddress object representing the loopback address, which is typically used
  /// to refer to the local host in networking contexts. The loopback address is an IPv6 address in this implementation.
  static auto getLocalHost() -> InetAddress {
    const boost::asio::ip::address_v6 addr = boost::asio::ip::address_v6::loopback();
    return InetAddress(addr.to_string());
  }

  /// \brief Compares this InetAddress object with another.
  /// \details This function compares the addresses of this and the other InetAddress objects to determine if they are equal.
  /// \param other The InetAddress object to compare with.
  /// \return true if the addresses are equal, false otherwise.
  [[nodiscard]] auto equals(const InetAddress& other) const -> bool {
    return endpoint_.address() == other.endpoint_.address();
  }

  /// \brief Returns the canonical hostname of the InetAddress object.
  /// \details This function returns the canonical hostname representation of the current IP address.
  /// The canonical hostname is the fully qualified domain name (FQDN) of the host that the InetAddress object represents.
  /// \return A string representing the canonical hostname of the InetAddress object.
  [[nodiscard]] auto getCanonicalHostName() const -> std::string {
    return endpoint_.address().to_string();
  }

  /// \brief Retrieves the hostname associated with the IP address.
  /// \details This function returns the hostname representation of the current IP address.
  /// It uses the address conversion functionality provided by boost::asio to obtain the hostname.
  /// \return A string representing the hostname of the InetAddress object.
  [[nodiscard]] auto getHostName() const -> std::string {
    return endpoint_.address().to_string();
  }

  /// \brief Returns a hash code value for this InetAddress object.
  /// \details The returned hash code is based on the IP address of the InetAddress object.
  /// \return A size_t value representing the hash code of the InetAddress object.
  [[nodiscard]] auto hashCode() const -> size_t {
    return std::hash<std::string>{}(endpoint_.address().to_string());
  }

  /// \brief Checks if the InetAddress object is an IP loopback address.
  /// \details This function returns true if the InetAddress object is a loopback address,
  /// false otherwise.
  [[nodiscard]] auto isLoopbackAddress() const -> bool {
    return endpoint_.address().is_loopback();
  }

  /// \brief Checks if the InetAddress object is a multicast address.
  /// \details This function returns true if the InetAddress object is a multicast address,
  /// false otherwise.
  /// \return true if the address is a multicast address, false otherwise.
  [[nodiscard]] auto isMulticastAddress() const -> bool {
    return endpoint_.address().is_multicast();
  }

  /// \brief Checks if the InetAddress object is reachable within a specified time limit.
  /// \details This function attempts to establish a connection to the InetAddress object
  /// within a specified time limit. The InetAddress object is considered reachable if
  /// the connection is established before the time limit is reached.
  /// \param timeout_ms The time limit in milliseconds. The connection attempt will be
  /// aborted if the connection is not established before this time.
  /// \return true if the InetAddress object is reachable, false otherwise.
  [[nodiscard]] auto isReachable(const int timeout_ms) const -> bool {
    try {
      boost::asio::io_context io_context;
      boost::asio::ip::tcp::socket socket(io_context, endpoint_);
      boost::asio::steady_timer timer(io_context);
      timer.expires_from_now(std::chrono::milliseconds(timeout_ms));
      socket.async_connect(endpoint_, [&timer](const boost::system::error_code& error) {
        if (!error) {
          timer.cancel();
        }
      });

      timer.async_wait([&socket](const boost::system::error_code& ec) {
        if (!ec) {
          socket.cancel();
        }
      });
      io_context.run();
      return socket.is_open();
    }
    catch (const std::exception& e) {
      LOG(ERROR) << "Error: " << e.what();
      return false;
    }
  }

  /// \brief Converts the InetAddress object to a string representation.
  /// \details The returned string contains the IP address in the standard IPv4 or IPv6 format.
  /// \return A string representing the InetAddress object.
  [[nodiscard]] auto toString() const -> std::string {
    return endpoint_.address().to_string();
  }

  [[nodiscard]] boost::asio::ip::tcp::endpoint endpoint() const {
    return endpoint_;
  }

private:
  boost::asio::ip::tcp::endpoint endpoint_{};
};
}
