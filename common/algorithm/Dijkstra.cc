#include "Dijkstra.hpp"

#include <queue>

namespace common {
Dijkstra::Dijkstra(const Graph& g) : graph_(g) { distances_.resize(graph_.getNodeCount(), INF); }

auto Dijkstra::compute(int32_t start) -> void {
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

auto Dijkstra::getDistance(const int32_t node) const -> int32_t { return distances_[node]; }

auto Dijkstra::getDistances() const -> std::vector<int32_t> { return distances_; }
}  // namespace common
