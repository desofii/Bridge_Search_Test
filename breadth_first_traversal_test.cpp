/**
 * @file breadth_first_traversal_test.cpp
 * @author Mikhail Lozhnikov
 *
 * Тесты для алгоритма обхода в ширину.
 */

#include <vector>
#include "test_core.hpp"
#include <breadth_first_traversal.hpp>
#include <graph.hpp>

using std::vector;
using graph::Graph;

static void SimpleTest();

void TestBreadthFirstTraversal() {
  TestSuite suite("TestBreadthFirstTraversal");

  RUN_TEST(suite, SimpleTest);
}


void SimpleTest() {
  Graph graph;

  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddVertex(5);

  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 4);
  graph.AddEdge(4, 5);

  vector<size_t> result;

  BreadthFirstTraversal(graph, 1, [&result](size_t v) {
    result.push_back(v);
  });

  // Не сработает т.к. может быть {1, 3, 2, 4, 5}.
//  REQUIRE_EQUAL(result, vector<size_t>({1, 2, 3, 4, 5}));

  REQUIRE(result == vector<size_t>({1, 2, 3, 4, 5}) ||
          result == vector<size_t>({1, 3, 2, 4, 5}));
}
