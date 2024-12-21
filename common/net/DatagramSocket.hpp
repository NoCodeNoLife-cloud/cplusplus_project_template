#pragma once
#include <boost/asio.hpp>
#include <vector>
#include "DatagramPacket.hpp"

namespace common::net {
/// <brief> A class for sending and receiving datagram packets over UDP.
/// \details This class provides methods to send and receive datagram packets over UDP.
/// It is a concrete implementation of the UDPSocket interface.
class DatagramSocket {
public:
  explicit DatagramSocket(boost::asio::io_context& io_context): socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)) {}

  /// \brief Send a datagram packet over UDP.
  /// \details This method sends a datagram packet over UDP to the specified host and port.
  auto send(const DatagramPacket& packet) -> void {
    const boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(packet.host()), packet.port());
    socket_.send_to(boost::asio::buffer(packet.data()), endpoint);
  }

  /// \brief Receive a datagram packet from UDP.
  /// \details This method receives a datagram packet from UDP and returns a DatagramPacket with the data and sender's host and port.
  auto receive() -> DatagramPacket {
    boost::asio::ip::udp::endpoint sender_endpoint;
    std::vector<char> buffer(1024);
    socket_.receive_from(boost::asio::buffer(buffer), sender_endpoint);
    DatagramPacket packet(buffer);
    packet.setHost(sender_endpoint.address().to_string());
    packet.setPort(sender_endpoint.port());
    return packet;
  }

private:
  boost::asio::ip::udp::socket socket_;
};
}
