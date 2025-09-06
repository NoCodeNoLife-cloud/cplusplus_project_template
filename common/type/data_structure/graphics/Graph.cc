#include "Graph.hpp"

namespace fox {
Graph::Graph(const int32_t n) : num_nodes_(n) { adj_list_.resize(num_nodes_); }

auto Graph::addEdge(const int32_t from, const int32_t to, const int32_t weight) -> void {
  Edge edge(to, weight);
  adj_list_[from].emplace_back(edge);
}

auto Graph::getAdjList(const int32_t node) const -> const std::vector<Edge>& { return adj_list_[node]; }

auto Graph::getNodeCount() const -> int32_t { return num_nodes_; }
}  // namespace fox
