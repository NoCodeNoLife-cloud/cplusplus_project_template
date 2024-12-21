#pragma once
#include <utility>
#include <vector>
#include <boost/asio.hpp>

namespace common::net
{
    class DatagramPacket
    {
    public:
        DatagramPacket(const std::vector<char>& data, std::string host, const uint16_t port): data_(data),
                                                                                              host_(std::move(host)), port_(port)
        {
        }

        explicit DatagramPacket(const std::vector<char>& data): data_(data)
        {
        }

        [[nodiscard]] auto data() const -> const std::vector<char>&
        {
            return data_;
        }

        auto data() -> std::vector<char>&
        {
            return data_;
        }

        [[nodiscard]] auto host() const -> const std::string&
        {
            return host_;
        }

        [[nodiscard]] auto port() const -> uint16_t
        {
            return port_;
        }

        auto setHost(const std::string& host) -> void
        {
            host_ = host;
        }

        auto setPort(const uint16_t port) -> void
        {
            port_ = port;
        }

        [[nodiscard]] auto size() const -> size_t
        {
            return data_.size();
        }

    private:
        std::vector<char> data_{};
        std::string host_{};
        uint16_t port_{};
    };
}
