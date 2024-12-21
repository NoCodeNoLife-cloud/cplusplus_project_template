#pragma once
#include <boost/asio.hpp>
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
}
