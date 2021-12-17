#include <iostream>
#include <vector>

#include "graph/adj_list_imp/graph_adjlist.h"
#include "graph/adj_list_imp/algos/dfs_algo.h"
#include "graph/adj_list_imp/algos/bfs_algo.h"
#include "graph/adj_list_imp/algos/dijkstra.h"
#include "graph/adj_list_imp/algos/prim.h"
#include "graph/adj_list_imp/algos/kruskal.h"

using namespace std;

int main() {
    Graph<char> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');
    g.addVertex('G');

    // forward
    g.addEdgeById(0, 1, 4);
    g.addEdgeById(0, 2, 6);
    g.addEdgeById(0, 3, 6);
    g.addEdgeById(1, 4, 7);
    g.addEdgeById(1, 2, 1);
    g.addEdgeById(2, 4, 6);
    g.addEdgeById(2, 5, 4);
    g.addEdgeById(3, 2, 2);
    g.addEdgeById(3, 5, 5);
    g.addEdgeById(4, 6, 6);
    g.addEdgeById(5, 4, 1);
    g.addEdgeById(5, 6, 8);

    // backward
    g.addEdgeById(1, 0, 4);
    g.addEdgeById(2, 0, 6);
    g.addEdgeById(3, 0, 6);
    g.addEdgeById(4, 1, 7);
    g.addEdgeById(2, 1, 1);
    g.addEdgeById(2, 4, 6);
    g.addEdgeById(5, 2, 4);
    g.addEdgeById(2, 3, 2);
    g.addEdgeById(5, 3, 5);
    g.addEdgeById(6, 4, 6);
    g.addEdgeById(4, 5, 1);
    g.addEdgeById(6, 5, 8);

//    g.printAdjList();
//    g.removeVertex('B');
    // or g.ramoveVertexById(1);
    cout << endl;
    g.printAdjList();


//    vector<Edge> dfsEdge = dfs(g.adjList, g.totalVertices());
//
//    for (int i = 0; i < dfsEdge.size(); i++) {
//        cout << " <" << dfsEdge[i].sourceId << ", " << dfsEdge[i].destId << "> " << dfsEdge[i].pathLength << '\n';
//    }

//    vector<Edge> bfsEdge = bfs(0, g.adjList, g.totalVertices());
//
//    for (int i = 0; i < bfsEdge.size(); i++) {
//        cout << " <" << bfsEdge[i].sourceId << ", " << bfsEdge[i].destId << "> " << bfsEdge[i].pathLength << '\n';
//    }

//    dijkstra(2, g.adjList, g.totalVertices());
//    cout << '\n';
//    dijkstra_minheap(2, g.adjList, g.totalVertices());

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

//    dfs(g.adjList, g.totalVertices());

//    g.printAdjList();

//    bfs(0, g.adjList, g.totalVertices());

//    prim(g.adjList, g.totalVertices());
    vector<Edge> edge = kruskal_minheap_findunion(g.adjList, g.totalVertices());
    for (int i = 0; i < edge.size(); i++) {
        cout << "(" << edge[i].sourceId << ", " << edge[i].destId << ")" << endl;
    }
}
