#pragma once

#include <filesystem>
#include <string>

namespace common
{
    /// @brief Abstract base class for serializing and deserializing objects to and from YAML format.
    /// @tparam T The type of object to be serialized/deserialized.
    template <typename T>
    class YamlObjectSerializer
    {
    public:
        /// @brief Serializes an object to a YAML file.
        /// @param obj The object to serialize.
        /// @param filename The path to the file where the YAML data will be saved.
        /// @throws std::invalid_argument If filename is empty.
        /// @throws std::runtime_error If file cannot be opened or written to.
        static auto serialize(const T& obj, const std::string& filename) -> void;

        /// @brief Deserializes an object from a YAML file.
        /// @param filename The path to the YAML file to deserialize from.
        /// @return The deserialized object.
        /// @throws std::runtime_error If file cannot be opened or decoded.
        [[nodiscard]] static auto deserialize(const std::string& filename) -> T;
    };
}
