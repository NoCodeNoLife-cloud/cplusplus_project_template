#include <gtest/gtest.h>
#include <vector>
#include <limits>

#include "algorithm/Dijkstra.hpp"

// Mock graph implementation for testing Dijkstra's algorithm
class SimpleGraph
{
public:
    struct Edge
    {
        int to_;
        int weight_;

        [[nodiscard]] int to() const { return to_; }
        [[nodiscard]] int weight() const { return weight_; }
    };


    explicit SimpleGraph(int nodeCount) : adjList(nodeCount)
    {
    }

    void addEdge(int from, int to, int weight)
    {
        adjList[from].emplace_back(Edge{to, weight});
    }

    [[nodiscard]] auto getAdjList(int node) const -> const std::vector<Edge>&
    {
        return adjList[node];
    }

    [[nodiscard]] auto getNodeCount() const -> int
    {
        return static_cast<int>(adjList.size());
    }

private:
    std::vector<std::vector<Edge>> adjList;
};

/// @test Basic shortest path computation
/// @details Test Dijkstra's algorithm on a simple graph with known shortest paths
/// @param None
TEST(DijkstraTest, BasicShortestPath)
{
    SimpleGraph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(1, 3, 7);

    fox::Dijkstra<SimpleGraph, int> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 8); // 0 -> 2 -> 1
    EXPECT_EQ(dijkstra.getDistance(2), 5); // 0 -> 2
    EXPECT_EQ(dijkstra.getDistance(3), 7); // 0 -> 2 -> 3
}

/// @test Single node graph
/// @details Test Dijkstra's algorithm on a graph with only one node
/// @param None
TEST(DijkstraTest, SingleNodeGraph)
{
    SimpleGraph graph(1);

    fox::Dijkstra<SimpleGraph, int> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
}

/// @test Disconnected graph
/// @details Test Dijkstra's algorithm when some nodes are unreachable
/// @param None
TEST(DijkstraTest, DisconnectedGraph)
{
    SimpleGraph graph(3);
    graph.addEdge(0, 1, 5); // Node 2 is unreachable from node 0

    fox::Dijkstra<SimpleGraph, int> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 5);
    EXPECT_EQ(dijkstra.getDistance(2), std::numeric_limits<int>::max());
}

/// @test Custom distance function
/// @details Test Dijkstra's algorithm with a custom distance function
/// @param None
TEST(DijkstraTest, CustomDistanceFunction)
{
    SimpleGraph graph(3);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);

    fox::Dijkstra<SimpleGraph, int> dijkstra(graph);

    // Use a custom distance function that doubles the weight
    dijkstra.compute(0, [](const auto& edge) { return edge.weight() * 2; });

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 20); // 10 * 2
    EXPECT_EQ(dijkstra.getDistance(2), 60); // (10 + 20) * 2
}

/// @test Get all distances
/// @details Test retrieving all distances after computation
/// @param None
TEST(DijkstraTest, GetAllDistances)
{
    SimpleGraph graph(3);
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);

    fox::Dijkstra<SimpleGraph, int> dijkstra(graph);
    dijkstra.compute(0);

    const auto& distances = dijkstra.getDistances();
    ASSERT_EQ(distances.size(), 3);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 5);
    EXPECT_EQ(distances[2], 8);
}

/// @test Large weights
/// @details Test Dijkstra's algorithm with large edge weights
/// @param None
TEST(DijkstraTest, LargeWeights)
{
    SimpleGraph graph(3);
    constexpr long long largeWeight = 1000000000LL;
    graph.addEdge(0, 1, largeWeight);
    graph.addEdge(1, 2, largeWeight);

    fox::Dijkstra<SimpleGraph, long long> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), largeWeight);
    EXPECT_EQ(dijkstra.getDistance(2), 2 * largeWeight);
}
