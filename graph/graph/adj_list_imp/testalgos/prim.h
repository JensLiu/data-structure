//
// Created by Jens on 15.12.2021.
//

#ifndef GRAPH_LAB_PRIM_H
#define GRAPH_LAB_PRIM_H

#include "../adj_list_inner/adjlist.h"

template <typename EdgeInfo>
void prim(const AdjList<EdgeInfo>& adj, const int& totalVertices) {
    using DistPair = std::pair<int, int>;
    using EdgeNode = EdgeNode<EdgeInfo>;
    using Edge = Edge<EdgeInfo>;
    double INF = DBL_MAX;

    bool* inMST = new bool[totalVertices];
    memset(inMST, false, totalVertices * sizeof(int));
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));
    double* mincost = new double[totalVertices];
    memset(mincost, 0x7f, totalVertices * sizeof(double));

    mincost[0] = 0;

    for (int i = 0; i < totalVertices; i++) {

        int minIdx = -1;
        double min = INF;
        for (int j = 0; j < totalVertices; j++) {
            if (!inMST[j] && mincost[j] < min) {
                min = mincost[j];
                minIdx = j;
            }
        }
        if (minIdx == -1)
            break;
        EdgeNode* p = adj[minIdx].destListHead;
        while (p != nullptr) {
            if (mincost[p->destId] > mincost[minIdx] + p->weight) {
                mincost[p->destId] = mincost[minIdx] + p->weight;
                parent[p->destId] = minIdx;
                inMST[p->destId] = true;
            }
            p = p->next;
        }
    }

    for (int i = 0; i < totalVertices; i++) {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < totalVertices; i++) {
        std::cout << std::setw(2) << parent[i] << " ";
    }

}

#endif //GRAPH_LAB_PRIM_H
