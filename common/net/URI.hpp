#pragma once
#include <string>
#include <boost/url.hpp>

namespace common::io
{
    class URI
    {
    public:
        explicit URI(const std::string& uri_str)
        {
            try
            {
                url_ = boost::urls::url(uri_str);
            }
            catch (const std::exception& e)
            {
                throw std::invalid_argument("Invalid URI: " + std::string(e.what()));
            }
        }

        [[nodiscard]] auto scheme() const -> std::string
        {
            return url_.scheme();
        }

        [[nodiscard]] auto host() const -> std::string
        {
            return url_.host();
        }

        [[nodiscard]] auto path() const -> std::string
        {
            return url_.path();
        }

        [[nodiscard]] auto query() const -> std::string
        {
            return url_.query();
        }

        [[nodiscard]] auto port() const -> std::string
        {
            return url_.port();
        }

        [[nodiscard]] auto toString() const -> std::string
        {
            std::string result;
            result += "Scheme: " + scheme() + "\n";
            result += "Host: " + host() + "\n";
            result += "Path: " + path() + "\n";
            result += "Query: " + query() + "\n";
            result += "Port: " + port() + "\n";
            return result;
        }

        static auto parse(const std::string& uri_str) -> URI
        {
            return URI(uri_str);
        }
    private:
        boost::urls::url url_;
    };
}
