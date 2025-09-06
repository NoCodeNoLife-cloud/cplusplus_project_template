#include <gtest/gtest.h>

#include "algorithm/Dijkstra.hpp"
#include "type/data_structure/graphics/Graph.hpp"

namespace gtest_case {
TEST(DijkstraAlgorithmTest, SimpleGraph) {
  fox::Graph graph(5);
  graph.addEdge(0, 1, 10);
  graph.addEdge(0, 4, 20);
  graph.addEdge(1, 2, 30);
  graph.addEdge(1, 3, 40);
  graph.addEdge(2, 3, 50);
  graph.addEdge(3, 4, 60);

  fox::Dijkstra dijkstra(graph);
  dijkstra.compute(0);

  EXPECT_EQ(dijkstra.getDistance(0), 0);
  EXPECT_EQ(dijkstra.getDistance(1), 10);
  EXPECT_EQ(dijkstra.getDistance(2), 40);
  EXPECT_EQ(dijkstra.getDistance(3), 50);
  EXPECT_EQ(dijkstra.getDistance(4), 20);
}

TEST(DijkstraAlgorithmTest, DisconnectedGraph) {
  fox::Graph graph(5);
  graph.addEdge(0, 1, 10);
  graph.addEdge(1, 2, 30);

  fox::Dijkstra dijkstra(graph);
  dijkstra.compute(0);

  EXPECT_EQ(dijkstra.getDistance(0), 0);
  EXPECT_EQ(dijkstra.getDistance(1), 10);
  EXPECT_EQ(dijkstra.getDistance(2), 40);
  EXPECT_EQ(dijkstra.getDistance(3), std::numeric_limits<int32_t>::max());
  EXPECT_EQ(dijkstra.getDistance(4), std::numeric_limits<int32_t>::max());
}
}  // namespace gtest_case
