#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <glog/logging.h>

namespace common::net
{
    class InetAddress
    {
    public:
        InetAddress(const std::string& host, unsigned short port);
        explicit InetAddress(const std::string& host);
        [[nodiscard]] auto getAddress() const -> std::vector<unsigned char>;
        [[nodiscard]] auto getHostAddress() const -> std::string;
        static auto getLocalHost() -> InetAddress;
        [[nodiscard]] auto equals(const InetAddress& other) const -> bool;
        [[nodiscard]] auto getCanonicalHostName() const -> std::string;
        [[nodiscard]] auto getHostName() const -> std::string;
        [[nodiscard]] auto hashCode() const -> size_t;
        [[nodiscard]] auto isLoopbackAddress() const -> bool;
        [[nodiscard]] auto isMulticastAddress() const -> bool;
        [[nodiscard]] auto isReachable(int32_t timeout_ms) const -> bool;
        [[nodiscard]] auto toString() const -> std::string;
        [[nodiscard]] boost::asio::ip::tcp::endpoint endpoint() const;
    private:
        boost::asio::ip::tcp::endpoint endpoint_{};
    };
}
