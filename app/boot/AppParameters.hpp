#pragma once
#include <string>
#include <yaml-cpp/node/node.h>

namespace app
{
    class AppParameters
    {
    public:
        auto appType(const std::string& app_type) -> void;
        [[nodiscard]] auto appType() const -> std::string;

    private:
        std::string app_type_{};
    };
}

template <>
struct YAML::convert<app::AppParameters>
{
    static auto decode(const Node& node, app::AppParameters& rhs) -> bool
    {
        rhs.appType(node["app_type"].as<std::string>());
        return true;
    }

    static auto encode(const app::AppParameters& rhs) -> Node
    {
        Node node;
        node["app_type"] = rhs.appType();
        return node;
    }
};
