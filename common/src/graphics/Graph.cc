#include "src/graphics/Graph.hpp"

#include <cstdint>
#include <vector>
#include <stdexcept>

#include "src/graphics/Edge.hpp"

namespace common
{
    Graph::Graph(const int32_t n) noexcept : num_nodes_(n)
    {
        adj_list_.resize(static_cast<size_t>(num_nodes_));
    }

    auto Graph::addEdge(const int32_t from, const int32_t to, const int32_t weight) -> void
    {
        if (from < 0 || from >= num_nodes_ || to < 0 || to >= num_nodes_)
        {
            throw std::out_of_range("Node index out of range");
        }
        Edge edge(to, weight);
        adj_list_[static_cast<size_t>(from)].emplace_back(edge);
    }

    auto Graph::getAdjList(const int32_t node) const -> const std::vector<Edge>&
    {
        if (node < 0 || node >= num_nodes_)
        {
            throw std::out_of_range("Node index out of range");
        }
        return adj_list_[static_cast<size_t>(node)];
    }

    auto Graph::getNodeCount() const noexcept -> int32_t
    {
        return num_nodes_;
    }
}
