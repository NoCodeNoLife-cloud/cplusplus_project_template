#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <type_traits>
#include <vector>

namespace common
{
    /// @brief Dijkstra's algorithm for finding the shortest paths from a single source node to all other nodes in a graph
    /// with non-negative edge weights.
    template <typename GraphType, typename DistanceType = int32_t>
    class Dijkstra
    {
    public:
        static_assert(std::is_arithmetic_v<DistanceType>, "DistanceType must be arithmetic");

        explicit Dijkstra(const GraphType& g);

        /// @brief Compute the shortest path from the start node to all nodes.
        /// @param start The start node.
        /// @param distanceFunc Function to extract distance from edge (default: returns edge.weight())
        template <typename DistanceFunc =
            std::function<DistanceType(const decltype(std::declval<GraphType>().getAdjList(0).front())&)>>
        auto compute(
            std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> start,
            DistanceFunc distanceFunc = [](const auto& edge) { return edge.weight(); })
            -> void;

        /// @brief Get the distance to the node.
        /// @param node The node.
        /// @return The distance to the node.
        [[nodiscard]] auto getDistance(std::decay_t<decltype(std::declval<GraphType>().getNodeCount())> node) const
            -> DistanceType;

        /// @brief Get all distances.
        /// @return All distances.
        [[nodiscard]] auto getDistances() const
            -> const std::vector<DistanceType>&;

    private:
        const GraphType& graph_;
        std::vector<DistanceType> distances_;
        const DistanceType INF = std::numeric_limits<DistanceType>::max();
    };
}
