#pragma once
#include <utility>
#include <vector>
#include <boost/asio.hpp>

namespace common::net {
/// \brief Class for representing datagram packets.
/// \details This class provides an interface to create, send and receive datagram packets.
/// It contains methods to create a new datagram packet with a specified size,
/// to access the data of the packet, and to send the packet to a specified address and port using UDP.
class DatagramPacket {
public:
  DatagramPacket(const std::vector<char>& data, std::string host, const uint16_t port): data_(data), host_(std::move(host)), port_(port) {}

  explicit DatagramPacket(const std::vector<char>& data): data_(data) {}

  /// \brief Returns a constant reference to the data of the datagram packet.
  /// \details This method returns a constant reference to the data of the datagram packet.
  /// The data can be accessed for reading, but not modified.
  [[nodiscard]] auto data() const -> const std::vector<char>& {
    return data_;
  }

  /// \brief Returns a reference to the data of the datagram packet.
  /// \details This method returns a reference to the data of the datagram packet.
  /// The data can be accessed and modified.
  auto data() -> std::vector<char>& {
    return data_;
  }

  /// \brief Returns the host of the datagram packet.
  /// \details This method returns a constant reference to the host of the datagram packet.
  /// The host can be accessed for reading, but not modified.
  [[nodiscard]] auto host() const -> const std::string& {
    return host_;
  }

  /// \brief Returns the port of the datagram packet.
  /// \details This method returns a constant reference to the port of the datagram packet.
  /// The port can be accessed for reading, but not modified.
  [[nodiscard]] auto port() const -> uint16_t {
    return port_;
  }

  /// \brief Sets the host of the datagram packet.
  /// \details This method sets the host of the datagram packet.
  /// The host can be accessed for reading and modified.
  auto setHost(const std::string& host) -> void {
    host_ = host;
  }

  /// \brief Sets the port of the datagram packet.
  /// \details This method sets the port of the datagram packet to the specified value.
  /// The port can be accessed for reading and modified.
  auto setPort(const uint16_t port) -> void {
    port_ = port;
  }

  /// \brief Returns the size of the datagram packet in bytes.
  /// \details This method returns the size of the datagram packet in bytes.
  /// The size is the number of bytes in the data of the datagram packet.
  [[nodiscard]] auto size() const -> size_t {
    return data_.size();
  }

private:
  std::vector<char> data_{};
  std::string host_{};
  uint16_t port_{};
};
}
