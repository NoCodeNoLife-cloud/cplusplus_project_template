#pragma once
#include <string>
#include <yaml-cpp/node/node.h>

namespace coco
{
    class GLogParameters final
    {
    public:
        GLogParameters();
        ~GLogParameters();
        GLogParameters(const GLogParameters& other);
        GLogParameters& operator=(const GLogParameters& other);
        GLogParameters(GLogParameters&& other) noexcept;
        [[nodiscard]] auto minLogLevel() const -> int32_t;
        [[nodiscard]] auto logName() const -> std::string;
        [[nodiscard]] auto logToStderr() const -> bool;
        auto minLogLevel(int32_t min_log_level) -> void;
        auto logName(const std::string& log_name) -> void;
        auto logToStderr(bool log_to_stderr) -> void;

    private:
        int32_t min_log_level_{};
        std::string log_name_;
        bool log_to_stderr_{};
    };
}

template <>
struct YAML::convert<coco::GLogParameters>
{
    static auto decode(const Node& node, coco::GLogParameters& rhs) -> bool
    {
        rhs.minLogLevel(node["min_log_level"].as<int>());
        rhs.logName(node["log_name"].as<std::string>());
        rhs.logToStderr(node["log_to_stderr"].as<bool>());
        return true;
    }

    static auto encode(const coco::GLogParameters& rhs) -> Node
    {
        Node node;
        node["min_log_level"] = rhs.minLogLevel();
        node["log_name"] = rhs.logName();
        node["log_to_stderr"] = rhs.logName();
        return node;
    }
};
