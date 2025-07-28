#include <gtest/gtest.h>

#include "algorithm/Dijkstra.hpp"
#include "type/data_structure/graphics/Graph.hpp"

namespace gtest_case {
TEST(DijkstraAlgorithmTest, SingleEdgeComputeDistance) {
  common::Graph graph(2);
  graph.addEdge(0, 1, 5);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  EXPECT_EQ(dijkstra.getDistance(1), 5);
}

TEST(DijkstraAlgorithmTest, MultiEdgesChooseShortest) {
  common::Graph graph(3);
  graph.addEdge(0, 1, 4);
  graph.addEdge(0, 2, 1);
  graph.addEdge(1, 2, 2);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  EXPECT_EQ(dijkstra.getDistance(2), 1);
}

TEST(DijkstraAlgorithmTest, DisconnectedNode) {
  common::Graph graph(3);
  graph.addEdge(0, 1, 3);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  constexpr auto INF = std::numeric_limits<int32_t>::max();
  EXPECT_EQ(dijkstra.getDistance(2), INF);
}

TEST(DijkstraAlgorithmTest, NegativeWeightEdge) {
  common::Graph graph(2);
  graph.addEdge(0, 1, -2);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  EXPECT_EQ(dijkstra.getDistance(1), -2);
}

TEST(DijkstraAlgorithmTest, MultiplePaths) {
  common::Graph graph(4);
  graph.addEdge(0, 1, 1);
  graph.addEdge(0, 2, 4);
  graph.addEdge(1, 2, 2);
  graph.addEdge(1, 3, 6);
  graph.addEdge(2, 3, 3);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  EXPECT_EQ(dijkstra.getDistance(3), 6);
}

TEST(DijkstraAlgorithmTest, AllNodesVisited) {
  common::Graph graph(3);
  graph.addEdge(0, 1, 2);
  graph.addEdge(1, 2, 3);
  graph.addEdge(0, 2, 6);
  common::Dijkstra dijkstra(graph);
  dijkstra.compute(0);
  EXPECT_EQ(dijkstra.getDistance(2), 5);
}
}  // namespace gtest_case
