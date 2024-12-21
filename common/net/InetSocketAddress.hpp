#pragma once
#include <boost/asio.hpp>
#include <string>


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
}
