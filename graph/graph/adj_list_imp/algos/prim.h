//
// Created by Jens on 15.12.2021.
//

#ifndef GRAPH_LAB_PRIM_H
#define GRAPH_LAB_PRIM_H

#include "../adj_list_inner/adjlist.h"

void prim(const AdjList& adj, const int& totalVertices) {
    const double INF = DBL_MAX;
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));

    int len = 0;
    int cur = 0;

    parent[cur] = cur;
    while (true) {

        if (parent[cur] == -1)
            break;

        EdgeNode* p = adj[cur].destListHead;
        double min = INF;
        int minIdx = -1;
        while (p != nullptr) {
            if (p->weight < min && parent[p->destId] == -1) {
                min = p->weight;
                minIdx = p->destId;
            }
            p = p->next;
        }
        if (minIdx == -1)
            break;

        parent[minIdx] = cur;
        cur = minIdx;
    }


    for (int j = 0; j < totalVertices; j++) {
        std::cout << parent[j] << ", " << j << std::endl;
    }
}

#endif //GRAPH_LAB_PRIM_H
