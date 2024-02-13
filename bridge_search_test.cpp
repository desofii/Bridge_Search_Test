/**
 * @file bridge_search_test.cpp
 * @author Sofya Degtyareva
 *
 * Тесты для алгоритма поиска мостов в графе.
 */

#include <random>
#include <unordered_set>
#include "test_core.hpp"
#include <bridge_search.hpp>
#include <depth_first_traversal.hpp>
#include <graph.hpp>

using std::vector;
using graph::Graph;

using std::out_of_range;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

static void SimpleTest();
static void RemoveEdgeTest();
static void RandomTest();

/**
 * @brief Основная функция для тестирования алгоритма поиска.
 */

void TestBridgeSearch() {
  TestSuite suite("TestBridgeSearch");
  RUN_TEST(suite, SimpleTest);
  RUN_TEST(suite, RemoveEdgeTest);
  RUN_TEST(suite, RandomTest);
}

/**
 * @brief Набор простых тестов на поиск мостов.
 */
static void SimpleTest() {
  Graph graph;
  graph.AddVertex(1);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    REQUIRE_EQUAL(result.empty(), true);
  }

  graph.AddVertex(2);
  graph.AddEdge(1, 2);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res = {{1, 2}};
    REQUIRE(result == res);
  }

  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res = {{3, 4}};
    REQUIRE(result == res);
  }

  graph.AddVertex(5);
  graph.AddVertex(6);
  graph.AddVertex(7);
  graph.AddVertex(8);
  graph.AddEdge(3, 5);
  graph.AddEdge(5, 8);
  graph.AddEdge(6, 8);
  graph.AddEdge(6, 7);
  graph.AddEdge(2, 7);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res = {{3, 4}};
    REQUIRE(result == res);
  }

  graph.AddVertex(9);
  graph.AddEdge(8, 9);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res1 = {{3, 4}, {8, 9}};
    vector<std::pair<size_t, size_t>> res2 = {{8, 9}, {3, 4}};
    REQUIRE(result == res1 || result == res2);
  }

  graph.AddEdge(4, 9);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    REQUIRE_EQUAL(result.empty(), true);
  }
}

/**
 * @brief Набор тестов на удаление моста в графе.
 */
static void RemoveEdgeTest() {
  Graph graph;

  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddEdge(1, 2);
  graph.AddVertex(3);
  graph.AddEdge(1, 3);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res1 = {{1, 2}, {1, 3}};
    vector<std::pair<size_t, size_t>> res2 = {{1, 3}, {1, 2}};
    REQUIRE(result == res1 || result == res2);
  }

  graph.RemoveEdge(1, 2);

  {
    vector<size_t> result;
    DepthFirstTraversal(graph, 1, [&result](size_t id) {
      result.push_back(id);
    });
    REQUIRE_EQUAL(result.size(), 2);
  }

  graph.AddEdge(1, 2);
  graph.AddVertex(4);
  graph.AddVertex(5);
  graph.AddEdge(1, 4);
  graph.AddEdge(2, 5);
  graph.RemoveEdge(1, 2);

  {
    vector<size_t> result;
    DepthFirstTraversal(graph, 1, [&result](size_t id) {
      result.push_back(id);
    });
    REQUIRE_EQUAL(result.size(), 3);
  }

  graph.AddEdge(1, 2);
  graph.AddEdge(3, 5);
  graph.AddVertex(6);
  graph.AddEdge(2, 6);
  graph.AddVertex(7);
  graph.AddEdge(5, 7);
  graph.RemoveEdge(2, 5);
  graph.RemoveEdge(1, 3);

  {
     vector<size_t> result;
     DepthFirstTraversal(graph, 4, [&result](size_t id) {
       result.push_back(id);
     });
     REQUIRE_EQUAL(result.size(), 4);
  }

  graph.AddEdge(2, 5);
  graph.AddEdge(1, 3);
  graph.AddVertex(8);
  graph.AddVertex(9);
  graph.AddVertex(10);
  graph.AddVertex(11);
  graph.AddEdge(7, 8);
  graph.AddEdge(4, 9);
  graph.AddEdge(3, 9);
  graph.AddEdge(3, 7);
  graph.AddEdge(8, 10);
  graph.AddEdge(10, 11);
  graph.AddEdge(11, 8);

  {
    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, 1, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<std::pair<size_t, size_t>> res1 = {{2, 6}, {7, 8}};
    vector<std::pair<size_t, size_t>> res2 = {{7, 8}, {2, 6}};
    REQUIRE(result == res1 || result == res2);
  }

  graph.RemoveEdge(2, 6);

  {
    vector<size_t> result;
    DepthFirstTraversal(graph, 1, [&result](size_t id) {
      result.push_back(id);
    });
    REQUIRE_EQUAL(result.size(), 10);
  }

  graph.AddEdge(2, 6);
  graph.RemoveEdge(7, 8);

  {
    vector<size_t> result;
    DepthFirstTraversal(graph, 1, [&result](size_t id) {
      result.push_back(id);
    });
    REQUIRE_EQUAL(result.size(), 8);
  }
}

/**
 * @brief Набор случайных тестов на удаление моста из графа.
*/
static void RandomTest() {
  const int numTries = 100;
  const int numCommands = 30;
  const size_t maxId = 10;

  random_device rd;
  mt19937 generator(rd());
  uniform_int_distribution<int> commands(0, 1);
  uniform_int_distribution<size_t> ids(0, maxId);

  for (int i = 0; i < numTries; i++) {
    Graph graph;
    size_t tmp;

    for (int j = 0; j < numCommands; j++) {
      const int command = commands(generator);

      if (command == 0) {
        const size_t id = ids(generator);
        tmp = id;

        graph.AddVertex(id);
      } else if (command == 1) {
        const size_t id1 = ids(generator);
        const size_t id2 = ids(generator);
        tmp = id1;

        graph.AddEdge(id1, id2);
      } else {
        REQUIRE(false);
      }
    }

    vector<std::pair<size_t, size_t>> result;
    BridgeSearch(graph, tmp, [&result](std::pair<size_t, size_t> id) {
          result.push_back(id);
    });
    vector<size_t> vertices;
    DepthFirstTraversal(graph, tmp, [&vertices](size_t id) {
      vertices.push_back(id);
    });

    if (!result.empty()) {
      graph.RemoveEdge(result[0].first, result[0].second);

      vector<size_t> res;
      DepthFirstTraversal(graph, tmp, [&res](size_t id) {
        res.push_back(id);
      });

      REQUIRE(res.size() < vertices.size());
    }
  }
}
