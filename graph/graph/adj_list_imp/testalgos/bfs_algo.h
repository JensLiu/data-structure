//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_BFS_ALGO_H
#define GRAPH_LAB_BFS_ALGO_H

#include "../graph_adjlist.h"
#include "../edge.h"
#include <queue>



void bfs(const int& sourceVertexId, const AdjList& adj, const int& totalVertices) {
    std::queue<int> queue;
    std::vector<Edge> edges;
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));
    queue.push(sourceVertexId);
    while (!queue.empty()) {
        int cur = queue.front();
        queue.pop();
        EdgeNode* p = adj[cur].destListHead;
        while (p != nullptr) {
            if (parent[p->destId] == -1) {
                parent[p->destId] = cur;
                queue.push(p->destId);
                edges.push_back(Edge(cur, p->destId, p->weight));
            }
            p = p->next;
        }
    }

}

#endif //GRAPH_LAB_BFS_ALGO_H
