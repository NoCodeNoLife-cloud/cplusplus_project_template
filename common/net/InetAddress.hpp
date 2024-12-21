#pragma once
#include <array>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <glog/logging.h>

namespace common::net
{
    class InetAddress
    {
    public:
        InetAddress(const std::string& host, const unsigned short port) : endpoint_(
            boost::asio::ip::make_address(host), port)
        {
        }

        explicit InetAddress(const std::string& host)
        {
            boost::asio::io_context io_context;
            boost::asio::ip::tcp::resolver resolver(io_context);
            const boost::asio::ip::tcp::resolver::results_type results = resolver.resolve(host, "");
            endpoint_.address() = results->endpoint().address();
        }

        [[nodiscard]] auto getAddress() const -> std::vector<unsigned char>
        {
            std::vector<unsigned char> result;
            if (endpoint_.address().is_v4())
            {
                const boost::asio::ip::address_v4 v4_address = endpoint_.address().to_v4();
                result.assign(v4_address.to_bytes().begin(), v4_address.to_bytes().end());
            }
            else if (endpoint_.address().is_v6())
            {
                const boost::asio::ip::address_v6 v6_address = endpoint_.address().to_v6();
                result.assign(v6_address.to_bytes().begin(), v6_address.to_bytes().end());
            }
            return result;
        }

        [[nodiscard]] auto getHostAddress() const -> std::string
        {
            return endpoint_.address().to_string();
        }

        static auto getLocalHost() -> InetAddress
        {
            const boost::asio::ip::address_v6 addr = boost::asio::ip::address_v6::loopback();
            return InetAddress(addr.to_string());
        }

        [[nodiscard]] auto equals(const InetAddress& other) const -> bool
        {
            return endpoint_.address() == other.endpoint_.address();
        }

        [[nodiscard]] auto getCanonicalHostName() const -> std::string
        {
            return endpoint_.address().to_string();
        }

        [[nodiscard]] auto getHostName() const -> std::string
        {
            return endpoint_.address().to_string();
        }

        [[nodiscard]] auto hashCode() const -> size_t
        {
            return std::hash<std::string>{}(endpoint_.address().to_string());
        }

        [[nodiscard]] auto isLoopbackAddress() const -> bool
        {
            return endpoint_.address().is_loopback();
        }

        [[nodiscard]] auto isMulticastAddress() const -> bool
        {
            return endpoint_.address().is_multicast();
        }

        [[nodiscard]] auto isReachable(const int timeout_ms) const -> bool
        {
            try
            {
                boost::asio::io_context io_context;
                boost::asio::ip::tcp::socket socket(io_context, endpoint_);
                boost::asio::steady_timer timer(io_context);
                timer.expires_from_now(std::chrono::milliseconds(timeout_ms));
                socket.async_connect(endpoint_, [&timer](const boost::system::error_code& error)
                {
                    if (!error)
                    {
                        timer.cancel();
                    }
                });
                timer.async_wait([&socket](const boost::system::error_code& ec)
                {
                    if (!ec)
                    {
                        socket.cancel();
                    }
                });
                io_context.run();
                return socket.is_open();
            }
            catch (const std::exception& e)
            {
                LOG(ERROR) << "Error: " << e.what();
                return false;
            }
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            return endpoint_.address().to_string();
        }

        [[nodiscard]] boost::asio::ip::tcp::endpoint endpoint() const
        {
            return endpoint_;
        }

    private:
        boost::asio::ip::tcp::endpoint endpoint_{};
    };
}
