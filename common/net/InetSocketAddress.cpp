#include "InetSocketAddress.hpp"
#include <stdexcept>
#include <utility>
#include <iostream>

namespace common::net
{
    InetSocketAddress::InetSocketAddress() = default;

    InetSocketAddress::InetSocketAddress(const std::string& host, const unsigned short port)
    {
        boost::asio::io_context ioContext;
        boost::asio::ip::tcp::resolver resolver(ioContext);
        const auto endpoints = resolver.resolve(host, std::to_string(port));
        if (endpoints.empty())
        {
            throw std::invalid_argument("Unable to resolve host and port");
        }
        mEndpoint = *endpoints.begin();
    }

    InetSocketAddress::InetSocketAddress(boost::asio::ip::tcp::endpoint endpoint): mEndpoint(std::move(endpoint)) {}

    auto InetSocketAddress::getAddress() const -> std::string
    {
        return mEndpoint.address().to_string();
    }

    auto InetSocketAddress::getPort() const -> unsigned short
    {
        return mEndpoint.port();
    }

    auto InetSocketAddress::fromString(const std::string& str) -> InetSocketAddress
    {
        const size_t colonPos = str.find(':');
        if (colonPos == std::string::npos)
        {
            throw std::invalid_argument("Invalid address format. Expected host:port");
        }
        std::string host = str.substr(0, colonPos);
        unsigned short port = std::stoi(str.substr(colonPos + 1));
        return {host, port};
    }

    auto InetSocketAddress::operator==(const InetSocketAddress& other) const -> bool
    {
        return mEndpoint == other.mEndpoint;
    }

    auto InetSocketAddress::operator!=(const InetSocketAddress& other) const -> bool
    {
        return !(*this == other);
    }

    auto InetSocketAddress::print() const -> void
    {
        std::cout << "Address: " << getAddress() << ", Port: " << getPort() << std::endl;
    }
}
