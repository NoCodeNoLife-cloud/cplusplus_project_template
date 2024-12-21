#pragma once
#include <yaml-cpp/node/convert.h>

namespace common
{
    class IYamlSerializable abstract
    {
    public:
        virtual ~IYamlSerializable() = default;
        [[nodiscard]] virtual auto encode() const -> YAML::Node = 0;
        virtual auto decode(const YAML::Node& node) -> bool = 0;
    };
}

template <typename T>
struct YAML::convert
{
    static Node encode(const T& obj)
    {
        return obj.encode();
    }

    static bool decode(const Node& node, T& obj)
    {
        return obj.decode(node);
    }
};
