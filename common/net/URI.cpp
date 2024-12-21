#include "URI.hpp"

namespace common::io
{
    URI::URI(const std::string& uri_str)
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

    auto URI::scheme() const -> std::string
    {
        return url_.scheme();
    }

    auto URI::host() const -> std::string
    {
        return url_.host();
    }

    auto URI::path() const -> std::string
    {
        return url_.path();
    }

    auto URI::query() const -> std::string
    {
        return url_.query();
    }

    auto URI::port() const -> std::string
    {
        return url_.port();
    }

    auto URI::toString() const -> std::string
    {
        std::string result;
        result += "Scheme: " + scheme() + "\n";
        result += "Host: " + host() + "\n";
        result += "Path: " + path() + "\n";
        result += "Query: " + query() + "\n";
        result += "Port: " + port() + "\n";
        return result;
    }

    auto URI::parse(const std::string& uri_str) -> URI
    {
        return URI(uri_str);
    }
}
