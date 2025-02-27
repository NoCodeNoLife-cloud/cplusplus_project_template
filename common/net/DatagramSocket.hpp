#pragma once
#include <boost/asio.hpp>
#include <vector>
#include "DatagramPacket.hpp"

namespace common::net
{
    class DatagramSocket
    {
    public:
        explicit DatagramSocket(boost::asio::io_context& io_context);
        auto send(const DatagramPacket& packet) -> void;
        auto receive() -> DatagramPacket;
    private:
        boost::asio::ip::udp::socket socket_;
    };

    inline DatagramSocket::DatagramSocket(boost::asio::io_context& io_context): socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)) {}

    inline auto DatagramSocket::send(const DatagramPacket& packet) -> void
    {
        const boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(packet.host()), packet.port());
        socket_.send_to(boost::asio::buffer(packet.data()), endpoint);
    }

    inline auto DatagramSocket::receive() -> DatagramPacket
    {
        boost::asio::ip::udp::endpoint sender_endpoint;
        std::vector<char> buffer(1024);
        socket_.receive_from(boost::asio::buffer(buffer), sender_endpoint);
        DatagramPacket packet(buffer);
        packet.setHost(sender_endpoint.address().to_string());
        packet.setPort(sender_endpoint.port());
        return packet;
    }
}
