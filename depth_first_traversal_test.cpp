/**
 * @file depth_first_traversal_test.cpp
 * @author Mikhail Lozhnikov
 *
 * Тесты для алгоритма обхода в глубину.
 */

#include "test_core.hpp"
#include <depth_first_traversal.hpp>
#include <graph.hpp>

using std::vector;
using graph::Graph;

static void SimpleTest();

void TestDepthFirstTraversal() {
  TestSuite suite("TestDepthFirstTraversal");

  RUN_TEST(suite, SimpleTest);
}

static void SimpleTest() {
  Graph graph;

  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddVertex(5);

  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(1, 4);
  graph.AddEdge(4, 5);

  {
    vector<size_t> result;

    DepthFirstTraversal(graph, 1, [&result](size_t id) {
      result.push_back(id);
    });

    REQUIRE(result == vector<size_t>({ 1, 2, 3, 4, 5}) ||
            result == vector<size_t>({ 1, 4, 5, 2, 3}));
  }

  {
    vector<size_t> result;

    DepthFirstTraversal(graph, 3, [&result](size_t id) {
      result.push_back(id);
    });

    REQUIRE_EQUAL(result, vector<size_t>({ 3, 2, 1, 4, 5}));
  }
}
