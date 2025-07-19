#include "AppParameters.hpp"

namespace app
{
    auto AppParameters::appType(const std::string& app_type) -> void
    {
        app_type_ = app_type;
    }

    auto AppParameters::appType() const -> std::string
    {
        return app_type_;
    }
}

auto YAML::convert<app::AppParameters>::decode(const Node& node, app::AppParameters& rhs) -> bool
{
    rhs.appType(node["app_type"].as<std::string>());
    return true;
}

auto YAML::convert<app::AppParameters>::encode(const app::AppParameters& rhs) -> Node
{
    Node node;
    node["app_type"] = rhs.appType();
    return node;
}
