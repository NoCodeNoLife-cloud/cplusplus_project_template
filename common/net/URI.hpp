#pragma once
#include <string>
#include <boost/url.hpp>

namespace common::io
{
    class URI
    {
    public:
        explicit URI(const std::string& uri_str);
        [[nodiscard]] auto scheme() const -> std::string;
        [[nodiscard]] auto host() const -> std::string;
        [[nodiscard]] auto path() const -> std::string;
        [[nodiscard]] auto query() const -> std::string;
        [[nodiscard]] auto port() const -> std::string;
        [[nodiscard]] auto toString() const -> std::string;
        static auto parse(const std::string& uri_str) -> URI;
    private:
        boost::urls::url url_;
    };
}
