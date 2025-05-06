#include <entity/data_structure/graphics/Graph.hpp>
#include <entity/util/DijkstraUtil.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(DijkstraUtilTest, SingleEdgeComputeDistance) {
    Graph graph(2);
    graph.addEdge(0, 1, 5);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    EXPECT_EQ(dijkstra.getDistance(1), 5);
  }

  TEST(DijkstraUtilTest, MultiEdgesChooseShortest) {
    Graph graph(3);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    EXPECT_EQ(dijkstra.getDistance(2), 1);
  }

  TEST(DijkstraUtilTest, DisconnectedNode) {
    Graph graph(3);
    graph.addEdge(0, 1, 3);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    constexpr auto INF = std::numeric_limits<int32_t>::max();
    EXPECT_EQ(dijkstra.getDistance(2), INF);
  }

  TEST(DijkstraUtilTest, NegativeWeightEdge) {
    Graph graph(2);
    graph.addEdge(0, 1, -2);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    EXPECT_EQ(dijkstra.getDistance(1), -2);
  }

  TEST(DijkstraUtilTest, MultiplePaths) {
    Graph graph(4);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 6);
    graph.addEdge(2, 3, 3);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    EXPECT_EQ(dijkstra.getDistance(3), 6);
  }

  TEST(DijkstraUtilTest, AllNodesVisited) {
    Graph graph(3);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(0, 2, 6);
    framework::DijkstraUtil dijkstra(graph);
    dijkstra.compute(0);
    EXPECT_EQ(dijkstra.getDistance(2), 5);
  }
}
