#include <iostream>
#include <vector>

#include "graph/adj_list_imp/graph_adjlist.h"
#include "graph/adj_list_imp/algos/dijkstra.h"
#include "graph/adj_list_imp/algos/dfs_algo.h"

using namespace std;

int main() {
    Graph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');
    g.addVertex('G');

    // forward
    g.addEdgeById(0, 1, 20, 4);
    g.addEdgeById(0, 2, 20, 6);
    g.addEdgeById(0, 3, 20, 6);
    g.addEdgeById(1, 4, 20, 7);
    g.addEdgeById(1, 2, 20, 1);
    g.addEdgeById(2, 4, 20, 6);
    g.addEdgeById(2, 5, 20, 4);
    g.addEdgeById(3, 2, 20, 2);
    g.addEdgeById(3, 5, 20, 5);
    g.addEdgeById(4, 6, 20, 6);
    g.addEdgeById(5, 4, 20, 1);
    g.addEdgeById(5, 6, 20, 8);

    // backward
    g.addEdgeById(1, 0, 20, 4);
    g.addEdgeById(2, 0, 20, 6);
    g.addEdgeById(3, 0, 20, 6);
    g.addEdgeById(4, 1, 20, 7);
    g.addEdgeById(2, 1, 20, 1);
    g.addEdgeById(4, 2, 20, 6);
    g.addEdgeById(5, 2, 20, 4);
    g.addEdgeById(2, 3, 20, 2);
    g.addEdgeById(5, 3, 20, 5);
    g.addEdgeById(6, 4, 20, 6);
    g.addEdgeById(4, 5, 20, 1);
    g.addEdgeById(6, 5, 20, 8);

//    g.printAdjList();
//    g.removeVertex('B');
//    g.printAdjList();
//    g.removeVertex('A'); // equivalent to g.removeVertexById(g.idOfVertex('A'))
//    g.printAdjList();
//    g.removeVertex('C');
//    g.printAdjList();


//    MinHeap<int> heap;
//    for (int i = 0; i < 100; i++) {
//        heap.insert((i * 2 + 1000) % 7);
//    }
//    for (int i = 0; i < 100; i++) {
//
//        cout << heap.heap[i] << " " ;
//    }
//    cout << endl;
//    for (int i = 0; i < 100; i++) {
//        cout << heap.extractMin() << " ";
//    }

//    dijkstra(0, g.adjList, g.totalVertices());
//    cout << endl;

//    for (int i = 0; i < g.totalVertices(); i++) {
//        cout << g.adjList[i].destListHead << " ";
//    }

    for (Edge<int> e : g.dijkstra()) {
        cout << e << endl;
    }
}
