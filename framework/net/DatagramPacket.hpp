#pragma once
#include <boost/asio.hpp>
#include <vector>

namespace framework::net {
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
} // namespace framework::net
