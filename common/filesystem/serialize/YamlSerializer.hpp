#pragma once
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>

namespace common
{
    template <typename T>
    class YamlSerializer abstract
    {
    public:
        static auto serialize(const T& obj, const std::string& filename) -> void;
        static auto deserialize(const std::string& filename) -> T;
    };

    template <typename T>
    auto YamlSerializer<T>::serialize(const T& obj, const std::string& filename) -> void
    {
        const YAML::Node node = YAML::convert<T>::encode(obj);
        YAML::Emitter emitter;
        emitter << node;
        const std::string yaml_str = emitter.c_str();
        std::ofstream file_out(filename);
        if (!file_out.is_open())
        {
            throw std::runtime_error("Could not open file " + filename);
        }
        file_out << yaml_str;
        file_out.close();
        if (!file_out)
        {
            throw std::runtime_error("Could not write to file " + filename);
        }
    }

    template <typename T>
    auto YamlSerializer<T>::deserialize(const std::string& filename) -> T
    {
        YAML::Node node = YAML::LoadFile(filename);
        T obj;
        if (!YAML::convert<T>::decode(node, obj))
        {
            throw std::runtime_error("Failed to decode YAML file " + filename);
        }
        return obj;
    }
}
