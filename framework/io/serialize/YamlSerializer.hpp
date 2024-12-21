#pragma once
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

namespace framework::io::serialize {
    template <typename T>
    class YamlSerializer abstract
    {
    public:
        static void serialize(const T& obj, const std::string& filename);

        static T deserialize(const std::string& filename);
    };

    template <typename T>
    void YamlSerializer<T>::serialize(const T& obj, const std::string& filename) {
        const YAML::Node node = YAML::convert<T>::encode(obj);
        YAML::Emitter emitter;
        emitter << node;
        const std::string yaml_str = emitter.c_str();
        std::ofstream fout(filename);
        if (!fout.is_open()) { throw std::runtime_error("Could not open file " + filename); }
        fout << yaml_str;
        fout.close();
        if (!fout) { throw std::runtime_error("Could not write to file " + filename); }
    }

    template <typename T>
    T YamlSerializer<T>::deserialize(const std::string& filename) {
        YAML::Node node = YAML::LoadFile(filename);
        T obj;
        if (!YAML::convert<T>::decode(node, obj)) { throw std::runtime_error("Failed to decode YAML file " + filename); }
        return obj;
    }
} // namespace framework::io::serialize
