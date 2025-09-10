#pragma once
#include <cstdint>

namespace fox {
/// @brief Data structure for representing an edge in a graph
/// @details This class stores information about an edge, including
///          the target vertex and the weight of the edge. It provides
///          methods to get and set these values.
class Edge {
 public:
  /// @brief Construct an Edge with target vertex and weight
  /// @param to Target vertex
  /// @param weight Edge weight
  Edge(const int32_t to, const int32_t weight) : to_(to), weight_(weight) {}

  /// @brief Get target vertex
  /// @return Target vertex
  [[nodiscard]] auto to() const -> int32_t { return to_; }

  /// @brief Get edge weight
  /// @return Edge weight
  [[nodiscard]] auto weight() const -> int32_t { return weight_; }

  /// @brief Set target vertex
  /// @param to Target vertex
  auto setTo(const int32_t to) -> void { to_ = to; }

  /// @brief Set edge weight
  /// @param weight Edge weight
  auto setWeight(const int32_t weight) -> void { weight_ = weight; }

 private:
  int32_t to_{0};
  int32_t weight_{0};
};
}  // namespace fox