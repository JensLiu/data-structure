//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_DFS_ALGO_H
#define GRAPH_LAB_DFS_ALGO_H

#include "../graph_adjlist.h"
#include <vector>
#include "../edge.h"

template <typename T>
void dfsVisit(const int& s, const AdjList<T>& adj, int* parent) {
    EdgeNode<T>* p = adj[s].destListHead;
    while (p != nullptr) {
        if (parent[p->destId] == -1) {
            parent[p->destId] = s;
            dfsVisit(p->destId, adj, parent);
        }
        p = p->next;
    }
}

template <typename T>
void dfs(const AdjList<T>& adj, const int& totalVertices) {

    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));


    for (int i = 0; i < adj.entrySize(); i++) {
        if (parent[i] == -1 || i == 0)
            dfsVisit(i, adj, parent);
    }

    for (int i = 0; i < totalVertices; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < totalVertices; i++) {
        std::cout << parent[i] << " ";
    }
}



//void dfsVisit_edgeDetect(const int& s, const AdjList& adj) {
//
//}
//
//template <typename T>
//void dfs_edgeDetect(const Graph<T>& g) {
//
//    int* parent = new int[g.totalVertices()];
//    memset(parent, -1, g.totalVertices() * sizeof(int));
//
//
//
//    int timestamp = 0;
//
//    for (int i = 0; i < g.adjList.entrySize(); i++) {
//        if (visit[i].first == -1)
//            dfsVisit_edgeDetect(g.adjList[i], g.adjList);
//    }
//
//}

#endif //GRAPH_LAB_DFS_ALGO_H
