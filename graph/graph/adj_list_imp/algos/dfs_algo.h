//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_DFS_ALGO_H
#define GRAPH_LAB_DFS_ALGO_H

#include "../graph_adjlist.h"
#include <vector>
#include "../edge.h"

void dfsVisit(const int& s, const AdjList& adj, int* parent, std::vector<Edge>& edges) {
    EdgeNode* p = adj[s].destListHead;
    while (p != nullptr) {
        if (parent[p->destId] == -1) {
            dfsVisit(p->destId, adj, parent, edges);
            parent[p->destId] = s;
            edges.push_back(Edge(s, p->destId, p->weight));
        }
        p = p->next;
    }
}

std::vector<Edge> dfs(const AdjList& adj, const int& totalVertices) {

    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));

    std::vector<Edge> edges;

    for (int i = 0; i < adj.entrySize(); i++) {
        if (parent[i] == -1 || i == 0)
            dfsVisit(i, adj, parent, edges);
    }

//    for (int i = 0; i < totalVertices; i++) {
//        std::cout << "<" << parent[i] << ", " << i << ">" << std::endl;
//    }


    std::reverse(edges.begin(), edges.end());

    return edges;
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
