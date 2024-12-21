#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

namespace common::net
{
    class InetSocketAddress
    {
    public:
        InetSocketAddress();
        InetSocketAddress(const std::string& host, unsigned short port);
        explicit InetSocketAddress(boost::asio::ip::tcp::endpoint endpoint);
        [[nodiscard]] auto getAddress() const -> std::string;
        [[nodiscard]] auto getPort() const -> unsigned short;
        static auto fromString(const std::string& str) -> InetSocketAddress;
        auto operator==(const InetSocketAddress& other) const -> bool;
        auto operator!=(const InetSocketAddress& other) const -> bool;
        auto print() const -> void;
    private:
        boost::asio::ip::tcp::endpoint mEndpoint{};
    };

    inline InetSocketAddress::InetSocketAddress() = default;

    inline InetSocketAddress::InetSocketAddress(const std::string& host, const unsigned short port)
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

    inline InetSocketAddress::InetSocketAddress(boost::asio::ip::tcp::endpoint endpoint): mEndpoint(std::move(endpoint)) {}

    inline auto InetSocketAddress::getAddress() const -> std::string
    {
        return mEndpoint.address().to_string();
    }

    inline auto InetSocketAddress::getPort() const -> unsigned short
    {
        return mEndpoint.port();
    }

    inline auto InetSocketAddress::fromString(const std::string& str) -> InetSocketAddress
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

    inline auto InetSocketAddress::operator==(const InetSocketAddress& other) const -> bool
    {
        return mEndpoint == other.mEndpoint;
    }

    inline auto InetSocketAddress::operator!=(const InetSocketAddress& other) const -> bool
    {
        return !(*this == other);
    }

    inline auto InetSocketAddress::print() const -> void
    {
        std::cout << "Address: " << getAddress() << ", Port: " << getPort() << std::endl;
    }
}
