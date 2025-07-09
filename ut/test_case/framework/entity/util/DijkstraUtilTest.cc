#include <algorithm/DijkstraAlgorithm.hpp>
#include <gtest/gtest.h>
#include <type/data_structure/graphics/Graph.hpp>

namespace gtest_case
{
    TEST(DijkstraAlgorithmTest, SingleEdgeComputeDistance)
    {
        coco::Graph graph(2);
        graph.addEdge(0, 1, 5);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        EXPECT_EQ(dijkstra.getDistance(1), 5);
    }

    TEST(DijkstraAlgorithmTest, MultiEdgesChooseShortest)
    {
        coco::Graph graph(3);
        graph.addEdge(0, 1, 4);
        graph.addEdge(0, 2, 1);
        graph.addEdge(1, 2, 2);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        EXPECT_EQ(dijkstra.getDistance(2), 1);
    }

    TEST(DijkstraAlgorithmTest, DisconnectedNode)
    {
        coco::Graph graph(3);
        graph.addEdge(0, 1, 3);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        constexpr auto INF = std::numeric_limits<int32_t>::max();
        EXPECT_EQ(dijkstra.getDistance(2), INF);
    }

    TEST(DijkstraAlgorithmTest, NegativeWeightEdge)
    {
        coco::Graph graph(2);
        graph.addEdge(0, 1, -2);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        EXPECT_EQ(dijkstra.getDistance(1), -2);
    }

    TEST(DijkstraAlgorithmTest, MultiplePaths)
    {
        coco::Graph graph(4);
        graph.addEdge(0, 1, 1);
        graph.addEdge(0, 2, 4);
        graph.addEdge(1, 2, 2);
        graph.addEdge(1, 3, 6);
        graph.addEdge(2, 3, 3);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        EXPECT_EQ(dijkstra.getDistance(3), 6);
    }

    TEST(DijkstraAlgorithmTest, AllNodesVisited)
    {
        coco::Graph graph(3);
        graph.addEdge(0, 1, 2);
        graph.addEdge(1, 2, 3);
        graph.addEdge(0, 2, 6);
        coco::DijkstraAlgorithm dijkstra(graph);
        dijkstra.compute(0);
        EXPECT_EQ(dijkstra.getDistance(2), 5);
    }
}
