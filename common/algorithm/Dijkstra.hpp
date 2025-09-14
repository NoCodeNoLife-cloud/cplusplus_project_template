#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <type_traits>
#include <vector>

namespace fox {
/// @brief Dijkstra's algorithm for finding the shortest paths from a single source node to all other nodes in a graph with non-negative edge weights.
template <typename GraphType, typename DistanceType = int32_t>
class Dijkstra {
  const GraphType& graph_;
  std::vector<DistanceType> distances_;
  const DistanceType INF = std::numeric_limits<DistanceType>::max();

 public:
  using distance_type = DistanceType;
  using graph_type = GraphType;
  using node_type = typename std::decay_t<decltype(std::declval<GraphType>().getNodeCount())>;

  static_assert(std::is_arithmetic_v<DistanceType>, "DistanceType must be arithmetic");

  explicit Dijkstra(const GraphType& g) : graph_(g) { distances_.resize(graph_.getNodeCount(), INF); }

  /// @brief Compute the shortest path from the start node to all nodes.
  /// @param start The start node.
  /// @param distanceFunc Function to extract distance from edge (default: returns edge.weight())
  template <typename DistanceFunc = std::function<DistanceType(const decltype(std::declval<GraphType>().getAdjList(0).front())&)>>
  auto compute(node_type start, DistanceFunc distanceFunc = [](const auto& edge) { return edge.weight(); }) -> void {
    std::fill(distances_.begin(), distances_.end(), INF);
    distances_[start] = DistanceType{0};

    std::priority_queue<std::pair<DistanceType, node_type>, std::vector<std::pair<DistanceType, node_type>>, std::greater<>> pq;

    pq.emplace(DistanceType{0}, start);

    while (!pq.empty()) {
      const DistanceType currentDist = pq.top().first;
      const node_type u = pq.top().second;
      pq.pop();

      if (currentDist > distances_[u]) continue;

      for (const auto& e : graph_.getAdjList(u)) {
        node_type v = e.to();
        DistanceType edgeWeight = distanceFunc(e);
        if (DistanceType newDist = currentDist + edgeWeight; newDist < distances_[v]) {
          distances_[v] = newDist;
          pq.emplace(newDist, v);
        }
      }
    }
  }

  /// @brief Get the distance to the node.
  /// @param node The node.
  /// @return The distance to the node.
  [[nodiscard]] auto getDistance(const node_type node) const -> DistanceType { return distances_[node]; }

  /// @brief Get all distances.
  /// @return All distances.
  [[nodiscard]] auto getDistances() const -> const std::vector<DistanceType>& { return distances_; }
};
}  // namespace fox
