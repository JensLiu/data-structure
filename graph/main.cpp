#include <iostream>
#include <vector>

#include "graph/adj_list_imp/graph_adjlist.h"
using namespace std;

int main() {
    Graph<char, string> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');

    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');

    g.addVertex('G');

    g.addEdgeById(0, 1, "ab", 4);
    g.addEdgeById(0, 2, "ac", 6);
    g.addEdgeById(0, 3, "ad", 6);
    g.addEdgeById(1, 4, "be", 7);
    g.addEdgeById(1, 2, "bc", 1);
    g.addEdgeById(2, 4, "ce", 6);
    g.addEdgeById(2, 5, "cf", 4);
    g.addEdgeById(3, 2, "dc", 2);
    g.addEdgeById(3, 5, "df", 5);
    g.addEdgeById(4, 6, "eg", 6);
    g.addEdgeById(5, 4, "fe", 1);
    g.addEdgeById(5, 6, "fg", 8);

    // backward
    g.addEdgeById(1, 0, "ba", 4);
    g.addEdgeById(2, 0, "ca", 6);
    g.addEdgeById(3, 0, "da", 6);
    g.addEdgeById(4, 1, "eb", 7);
    g.addEdgeById(2, 1, "cb", 1);
    g.addEdgeById(4, 2, "ec", 6);
    g.addEdgeById(5, 2, "fc", 4);
    g.addEdgeById(2, 3, "dc", 2);
    g.addEdgeById(5, 3, "fd", 5);
    g.addEdgeById(6, 4, "ge", 6);
    g.addEdgeById(4, 5, "ef", 1);
    g.addEdgeById(6, 5, "gf", 8);

//    g.printAdjList();
//    cout << "removed edge: " << g.removeEdgeById(1, 0) << endl;
//    g.printAdjList();

//    g.printAdjList();
//    cout << "removed edges" << endl;
//    for (Edge<string> e : g.removeVertex('B')) {
//        cout << e << endl;
//    }
//    g.printAdjList();
//    g.printAdjList();
//    cout << "removed edges" << endl;
//    for (Edge<string> e : g.removeVertex('A')) {
//        cout << e << endl;
//    }
//    g.printAdjList();
//    g.printAdjList();
//    cout << "removed edges: [" << endl;
//    for (Edge<string> e : g.removeVertex('C')) {
//        cout << e << endl;
//    }
//    cout << "]" << endl;
//    cout << "adj list: " << endl;
//    g.printAdjList();


//    for (const Edge<string>& e : g.dijkstra()) {
//        cout << e << endl;
//    }

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

    for (int i = 1; i < g.totalVertices(); i++) {
        for (vector<Edge<string>> result: g.dijkstra(i)) {
            for (Edge<string> e: result) {
                cout << e << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

//    for (Edge<string> e : g.prim()) {
//        cout << e << " ";
//    }

}
