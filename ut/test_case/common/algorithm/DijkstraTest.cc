#include <gtest/gtest.h>

#include "algorithm/Dijkstra.hpp"
#include "type/data_structure/graphics/Graph.hpp"

namespace gtest_case
{
TEST(DijkstraAlgorithmTest, SimpleGraph)
{
    fox::Graph graph(5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 4, 20);
    graph.addEdge(1, 2, 30);
    graph.addEdge(1, 3, 40);
    graph.addEdge(2, 3, 50);
    graph.addEdge(3, 4, 60);

    fox::Dijkstra<fox::Graph> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 10);
    EXPECT_EQ(dijkstra.getDistance(2), 40);
    EXPECT_EQ(dijkstra.getDistance(3), 50);
    EXPECT_EQ(dijkstra.getDistance(4), 20);
}

TEST(DijkstraAlgorithmTest, DisconnectedGraph)
{
    fox::Graph graph(5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 30);

    fox::Dijkstra<fox::Graph> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 10);
    EXPECT_EQ(dijkstra.getDistance(2), 40);
    EXPECT_EQ(dijkstra.getDistance(3), std::numeric_limits<int32_t>::max());
    EXPECT_EQ(dijkstra.getDistance(4), std::numeric_limits<int32_t>::max());
}

TEST(DijkstraAlgorithmTest, FloatWeights)
{
    fox::Graph graph(3);
    graph.addEdge(0, 1, 15);
    graph.addEdge(1, 2, 25);
    graph.addEdge(0, 2, 50);

    fox::Dijkstra<fox::Graph, float> dijkstra(graph);
    dijkstra.compute(0);

    EXPECT_FLOAT_EQ(dijkstra.getDistance(0), 0.0f);
    EXPECT_FLOAT_EQ(dijkstra.getDistance(1), 15.0f);
    EXPECT_FLOAT_EQ(dijkstra.getDistance(2), 40.0f);
}

TEST(DijkstraAlgorithmTest, CustomDistanceFunction)
{
    fox::Graph graph(3);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);
    graph.addEdge(0, 2, 50);

    fox::Dijkstra<fox::Graph, int32_t> dijkstra(graph);
    // Custom distance function that doubles the weight
    dijkstra.compute(0, [](const fox::Edge &edge) { return edge.weight() * 2; });

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 20); // 10 * 2
    EXPECT_EQ(dijkstra.getDistance(2), 60); // (10 * 2) + (20 * 2)
}
} // namespace gtest_case
