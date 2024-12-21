#include "DatagramPacket.hpp"
#include <utility>

namespace framework::net {
    DatagramPacket::DatagramPacket(const std::vector<char>& data, std::string host, const uint16_t port) : data_(data), host_(std::move(host)), port_(port) {}

    DatagramPacket::DatagramPacket(const std::vector<char>& data) : data_(data) {}

    auto DatagramPacket::data() const -> const std::vector<char>& { return data_; }

    auto DatagramPacket::data() -> std::vector<char>& { return data_; }

    auto DatagramPacket::host() const -> const std::string& { return host_; }

    auto DatagramPacket::port() const -> uint16_t { return port_; }

    auto DatagramPacket::setHost(const std::string& host) -> void { host_ = host; }

    auto DatagramPacket::setPort(const uint16_t port) -> void { port_ = port; }

    auto DatagramPacket::size() const -> size_t { return data_.size(); }
} // namespace framework::net
