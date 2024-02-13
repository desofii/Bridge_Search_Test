/**
 * @file main.cpp
 * @author Mikhail Lozhnikov
 *
 * Файл с функией main().
 */

#include "test.hpp"
#include "test_core.hpp"

int main() {
  TestGraph();
  TestOrientedGraph();
  TestWeightedGraph();
  TestWeightedOrientedGraph();
  TestBreadthFirstTraversal();
  TestBridgeSearch();
  TestDepthFirstTraversal();

  return TestSuite::Status();
}
