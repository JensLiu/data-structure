//
// Created by Jens on 16.12.2021.
//

#ifndef GRAPH_LAB_KRUSKAL_H
#define GRAPH_LAB_KRUSKAL_H

#include "../graph_adjlist.h"
#include "../../../helper_ds/findunion.h"
#include "../edge.h"
#include "../../../helper_ds/minheap.h"

void kruskal(const AdjList& adj, const int& totalVertices, const int& totalEdges) {
    int* connected = new int[totalVertices];
    for (int i = 0; i < totalVertices; i++) {
        connected[i] = i;
    }

    Edge* edgeList = new Edge[totalEdges];
    int insertIdx = 0;
    for (int i = 0; i < totalVertices; i++) {
        EdgeNode* p = adj[i].destListHead;
        while (p != nullptr) {
            edgeList[insertIdx] = Edge(i, p->destId, p->weight);
            insertIdx++;
            p = p->next;
        }
    }


}

void kruskal_minheap_findunion(const AdjList& adj, const int& totalVertices) {
    FindUnion fu(totalVertices);
    MinHeap<Edge> heap;
    std::vector<Edge> edges;
    int len = 0;
    for (int i = 0; i < totalVertices; i++) {
        EdgeNode* p = adj[i].destListHead;
        while (p != nullptr) {
            heap.insert(Edge(i, p->destId, p->weight));
            p = p->next;
        }
        fu.insert(i);
    }

    while (!heap.empty()) {
        Edge cur = heap.extractMin();
        if (fu.connected(cur.sourceId, cur.destId))
            continue;
        len += cur.pathLength;
        fu.unionElem(cur.sourceId, cur.destId);
        edges.push_back(cur);
    }


}

#endif //GRAPH_LAB_KRUSKAL_H
