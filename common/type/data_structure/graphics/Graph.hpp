#pragma once
#include <cstdint>
#include <vector>

#include "Edge.hpp"

namespace common {
class Graph {
 public:
  explicit Graph(int32_t n);
  auto addEdge(int32_t from, int32_t to, int32_t weight) -> void;
  [[nodiscard]] auto getAdjList(int32_t node) const -> const std::vector<Edge>&;
  [[nodiscard]] auto getNodeCount() const -> int32_t;

 private:
  int32_t num_nodes_;
  std::vector<std::vector<Edge>> adj_list_{};
};
}  // namespace common
