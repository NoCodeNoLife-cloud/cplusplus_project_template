#pragma once
#include <cstdint>
#include <vector>

#include "Edge.hpp"

namespace common
{
    /// @brief A class representing a graph data structure
    /// @details This class provides functionality to create a graph with a specified number of nodes,
    ///          add edges between nodes with weights, and retrieve adjacency information.
    ///          The graph is represented using an adjacency list.
    class Graph
    {
    public:
        /// @brief Construct a graph with n nodes
        /// @param n Number of nodes
        explicit Graph(int32_t n) noexcept;

        /// @brief Add an edge to the graph
        /// @param from Source node
        /// @param to Destination node
        /// @param weight Edge weight
        /// @throws std::out_of_range If node indices are out of valid range
        auto addEdge(int32_t from, int32_t to, int32_t weight) -> void;

        /// @brief Get adjacency list of a node
        /// @param node Node index
        /// @return Reference to adjacency list
        /// @throws std::out_of_range If node index is out of valid range
        [[nodiscard]] auto getAdjList(int32_t node) const -> const std::vector<Edge>&;

        /// @brief Get number of nodes
        /// @return Number of nodes
        [[nodiscard]] auto getNodeCount() const noexcept -> int32_t;

    private:
        int32_t num_nodes_{0};
        std::vector<std::vector<Edge>> adj_list_{};
    };
}
