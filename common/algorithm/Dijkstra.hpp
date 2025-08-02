#pragma once
#include "type/data_structure/graphics/Graph.hpp"

namespace common {
class Dijkstra {
 public:
  explicit Dijkstra(const Graph& g);

  /// @brief Compute the shortest path from the start node to all nodes.
  /// @param start The start node.
  auto compute(int32_t start) -> void;

  /// @brief Get the distance to the node.
  /// @param node The node.
  /// @return The distance to the node.
  [[nodiscard]] auto getDistance(int32_t node) const -> int32_t;

  /// @brief Get all distances.
  /// @return All distances.
  [[nodiscard]] auto getDistances() const -> std::vector<int32_t>;

 private:
  const Graph& graph_;
  std::vector<int32_t> distances_;
  const int32_t INF = std::numeric_limits<int32_t>::max();
};
}  // namespace common
