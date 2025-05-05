#pragma once
#include <entity/data_structure/graphics/Graph.hpp>
using framework::entity::data_structure::graphics::Graph;

namespace framework::entity::util {
  class DijkstraUtil {
  public:
    explicit DijkstraUtil(const Graph& g);
    auto compute(int32_t start) -> void;
    [[nodiscard]] auto getDistance(int32_t node) const -> int32_t;
    auto printDistances() const -> void;

  private:
    const Graph& graph;
    std::vector<int32_t> dist;
    const int32_t INF = std::numeric_limits<int32_t>::max();
  };
}
