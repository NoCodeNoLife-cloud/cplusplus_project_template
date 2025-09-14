#pragma once

#include <yaml-cpp/node/convert.h>

namespace fox
{
/// @brief Interface for YAML serializable objects.
/// @details This interface provides methods to encode and decode objects to and from YAML nodes.
/// @note This interface is intended to be implemented by classes that need YAML serialization.
class IYamlSerializable
{
  public:
    /// @brief Virtual destructor to ensure proper cleanup of derived classes
    virtual ~IYamlSerializable() = default;

    /// @brief Encode the object to YAML node.
    /// This method serializes the object's data into a YAML node representation.
    /// @return YAML node containing the serialized object data
    [[nodiscard]] virtual auto encode() const -> YAML::Node = 0;

    /// @brief Decode the object from YAML node.
    /// This method deserializes data from a YAML node into the object.
    /// @param node YAML node containing the data to deserialize
    /// @return True if decoding is successful, false otherwise
    virtual auto decode(const YAML::Node &node) -> bool = 0;
};
} // namespace fox

/// @brief YAML convert template specialization for IYamlSerializable objects.
/// @tparam T Type of the object that implements IYamlSerializable
template <typename T> struct YAML::convert
{
    /// @brief Encode an object to a YAML node.
    /// @param obj The object to encode
    /// @return YAML node containing the encoded object
    static Node encode(const T &obj)
    {
        return obj.encode();
    }

    /// @brief Decode an object from a YAML node.
    /// @param node YAML node containing the data to decode
    /// @param obj Reference to the object to populate with decoded data
    /// @return True if decoding is successful, false otherwise
    static bool decode(const Node &node, T &obj)
    {
        return obj.decode(node);
    }
};
