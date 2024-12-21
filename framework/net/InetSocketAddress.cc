#include "InetSocketAddress.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>

namespace framework::net {
    InetSocketAddress::InetSocketAddress() = default;

    InetSocketAddress::InetSocketAddress(const std::string& host, const unsigned short port) {
        boost::asio::io_context ioContext;
        boost::asio::ip::tcp::resolver resolver(ioContext);
        const auto endpoints = resolver.resolve(host, std::to_string(port));
        if (endpoints.empty()) { throw std::invalid_argument("Unable to resolve host and port"); }
        m_endpoint_ = *endpoints.begin();
    }

    InetSocketAddress::InetSocketAddress(boost::asio::ip::tcp::endpoint endpoint) : m_endpoint_(std::move(endpoint)) {}

    auto InetSocketAddress::getAddress() const -> std::string { return m_endpoint_.address().to_string(); }

    auto InetSocketAddress::getPort() const -> unsigned short { return m_endpoint_.port(); }

    auto InetSocketAddress::fromString(const std::string& str) -> InetSocketAddress {
        const size_t colonPos = str.find(':');
        if (colonPos == std::string::npos) { throw std::invalid_argument("Invalid address format. Expected host:port"); }
        std::string host = str.substr(0, colonPos);
        unsigned short port = std::stoi(str.substr(colonPos + 1));
        return {host, port};
    }

    auto InetSocketAddress::operator==(const InetSocketAddress& other) const -> bool { return m_endpoint_ == other.m_endpoint_; }

    auto InetSocketAddress::operator!=(const InetSocketAddress& other) const -> bool { return !(*this == other); }

    auto InetSocketAddress::print() const -> void { std::cout << "Address: " << getAddress() << ", Port: " << getPort() << std::endl; }
} // namespace framework::net
