#pragma once
#include <utility>
#include <vector>
#include <boost/asio.hpp>

namespace common::net
{
    class DatagramPacket
    {
    public:
        DatagramPacket(const std::vector<char>& data, std::string host, uint16_t port);
        explicit DatagramPacket(const std::vector<char>& data);
        [[nodiscard]] auto data() const -> const std::vector<char>&;
        auto data() -> std::vector<char>&;
        [[nodiscard]] auto host() const -> const std::string&;
        [[nodiscard]] auto port() const -> uint16_t;
        auto setHost(const std::string& host) -> void;
        auto setPort(uint16_t port) -> void;
        [[nodiscard]] auto size() const -> size_t;
    private:
        std::vector<char> data_{};
        std::string host_{};
        uint16_t port_{};
    };

    inline DatagramPacket::DatagramPacket(const std::vector<char>& data, std::string host, const uint16_t port): data_(data), host_(std::move(host)), port_(port) {}

    inline DatagramPacket::DatagramPacket(const std::vector<char>& data): data_(data) {}

    inline auto DatagramPacket::data() const -> const std::vector<char>&
    {
        return data_;
    }

    inline auto DatagramPacket::data() -> std::vector<char>&
    {
        return data_;
    }

    inline auto DatagramPacket::host() const -> const std::string&
    {
        return host_;
    }

    inline auto DatagramPacket::port() const -> uint16_t
    {
        return port_;
    }

    inline auto DatagramPacket::setHost(const std::string& host) -> void
    {
        host_ = host;
    }

    inline auto DatagramPacket::setPort(const uint16_t port) -> void
    {
        port_ = port;
    }

    inline auto DatagramPacket::size() const -> size_t
    {
        return data_.size();
    }
}
