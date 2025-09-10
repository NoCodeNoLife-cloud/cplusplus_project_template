#pragma once
#include <cstdint>
#include <vector>

#include "Edge.hpp"

namespace fox {
/// @brief A class representing a graph data structure
/// @details This class provides functionality to create a graph with a specified number of nodes,
///          add edges between nodes with weights, and retrieve adjacency information.
///          The graph is represented using an adjacency list.
class Graph {
 public:
  /// @brief Construct a graph with n nodes
  /// @param n Number of nodes
  explicit Graph(const int32_t n) : num_nodes_(n) { adj_list_.resize(num_nodes_); }

  /// @brief Add an edge to the graph
  /// @param from Source node
  /// @param to Destination node
  /// @param weight Edge weight
  auto addEdge(const int32_t from, const int32_t to, const int32_t weight) -> void {
    Edge edge(to, weight);
    adj_list_[from].emplace_back(edge);
  }

  /// @brief Get adjacency list of a node
  /// @param node Node index
  /// @return Reference to adjacency list
  [[nodiscard]] auto getAdjList(const int32_t node) const -> const std::vector<Edge>& { return adj_list_[node]; }

  /// @brief Get number of nodes
  /// @return Number of nodes
  [[nodiscard]] auto getNodeCount() const -> int32_t { return num_nodes_; }

 private:
  int32_t num_nodes_;
  std::vector<std::vector<Edge>> adj_list_{};
};
}  // namespace fox