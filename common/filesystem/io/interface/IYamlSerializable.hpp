#pragma once
#include <yaml-cpp/node/convert.h>

namespace common {
/// @brief Interface for YAML serializable objects.
/// @details This interface provides methods to encode and decode objects to and from YAML nodes.
/// @note This interface is intended to be implemented by classes that need YAML serialization.
class IYamlSerializable {
 public:
  virtual ~IYamlSerializable() = default;

  /// @brief Encode the object to YAML node.
  /// @return YAML node.
  [[nodiscard]] virtual auto encode() const -> YAML::Node = 0;

  /// @brief Decode the object from YAML node.
  /// @param node YAML node.
  /// @return True if decoding is successful.
  virtual auto decode(const YAML::Node& node) -> bool = 0;
};
}  // namespace common

template <typename T>
struct YAML::convert {
  static Node encode(const T& obj) { return obj.encode(); }

  static bool decode(const Node& node, T& obj) { return obj.decode(node); }
};
