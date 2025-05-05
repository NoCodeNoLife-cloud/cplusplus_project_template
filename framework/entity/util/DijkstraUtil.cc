#include <iostream>
#include <queue>
#include <entity/data_structure/graphics/Edge.hpp>
#include <entity/util/DijkstraUtil.hpp>
using framework::entity::data_structure::graphics::Edge;

namespace framework::entity::util {
  DijkstraUtil::DijkstraUtil(const Graph& g): graph(g) {
    dist.resize(graph.getNodeCount(), INF);
  }

  auto DijkstraUtil::compute(int32_t start) -> void {
    dist[start] = 0;
    using Pair = std::pair<int32_t, int32_t>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
      const int32_t currentDist = pq.top().first;
      const int32_t u = pq.top().second;
      pq.pop();

      if (currentDist > dist[u]) continue;

      for (const Edge& e : graph.getAdjList(u)) {
        int32_t v = e.to();
        if (int32_t newDist = currentDist + e.weight(); newDist < dist[v]) {
          dist[v] = newDist;
          pq.emplace(newDist, v);
        }
      }
    }
  }

  auto DijkstraUtil::getDistance(int32_t node) const -> int32_t {
    return dist[node];
  }

  auto DijkstraUtil::printDistances() const -> void {
    for (int32_t i = 0; i < graph.getNodeCount(); ++i) {
      std::cout << "Node " << i << ": ";
      if (dist[i] == INF) {
        std::cout << "INF" << std::endl;
      } else {
        std::cout << dist[i] << std::endl;
      }
    }
  }
}
