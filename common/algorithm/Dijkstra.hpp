#pragma once
#include <queue>

#include "type/data_structure/graphics/Graph.hpp"

namespace fox {
/// @brief Dijkstra's algorithm for finding the shortest paths from a single source node to all other nodes in a graph with non-negative edge weights.
class Dijkstra {
 public:
  explicit Dijkstra(const Graph& g) : graph_(g) { distances_.resize(graph_.getNodeCount(), INF); }

  /// @brief Compute the shortest path from the start node to all nodes.
  /// @param start The start node.
  auto compute(int32_t start) -> void {
    distances_[start] = 0;
    std::priority_queue<std::pair<int32_t, int32_t>, std::vector<std::pair<int32_t, int32_t>>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
      const int32_t currentDist = pq.top().first;
      const int32_t u = pq.top().second;
      pq.pop();

      if (currentDist > distances_[u]) continue;

      for (const Edge& e : graph_.getAdjList(u)) {
        int32_t v = e.to();
        if (int32_t newDist = currentDist + e.weight(); newDist < distances_[v]) {
          distances_[v] = newDist;
          pq.emplace(newDist, v);
        }
      }
    }
  }

  /// @brief Get the distance to the node.
  /// @param node The node.
  /// @return The distance to the node.
  [[nodiscard]] auto getDistance(const int32_t node) const -> int32_t { return distances_[node]; }

  /// @brief Get all distances.
  /// @return All distances.
  [[nodiscard]] auto getDistances() const -> std::vector<int32_t> { return distances_; }

 private:
  const Graph& graph_;
  std::vector<int32_t> distances_;
  const int32_t INF = std::numeric_limits<int32_t>::max();
};
}  // namespace fox
