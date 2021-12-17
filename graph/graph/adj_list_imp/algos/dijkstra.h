//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_DIJAKSTRA_H
#define GRAPH_LAB_DIJAKSTRA_H

#include "../graph_adjlist.h"
#include "../../../helper_ds/minheap.h"
#include "../edge.h"
#include <iomanip>

void print_dist(const int& totalVertices, double* dist, const double& INF) {
    for (int k = 0; k < totalVertices; k++) {
        std::cout << std::setw(3) << k << " ";
    }
    std::cout << std::endl;
    for (int k = 0; k < totalVertices; k++) {
        if (dist[k] == INF) {
            std::cout << std::setw(3) << "INF" << " ";
        } else {
            std::cout << std::setw(3) << dist[k] << " ";
        }
    }
    std::cout << std::endl;
}

void print_path(const int& id, int* parent) {
    if (id == -1) {
        std::cout << "x";
        return;
    }
    print_path(parent[id], parent);
    std::cout << "->" << id;
}

void dijkstra(const int& sourceVertexId, const AdjList& adj, const int& totalVertices) {
    double* dist = new double[totalVertices];
    const double INF = DBL_MAX;
    for (int i = 0; i < totalVertices; i++) dist[i] = INF;
    int* visited = new int[totalVertices];
    memset(visited, 0, totalVertices * sizeof(int));
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));

    dist[sourceVertexId] = 0;

    for (int i = 0; i < totalVertices; i++) {

        // extract min
        double minDist = INF;
        int idx = -1;
        for (int j = 0; j < totalVertices; j++) {
            if (visited[j] == 0 && dist[j] < minDist) {
                minDist = dist[j];
                idx = j;
            }
        }

        if (idx == -1) break;

        visited[idx] = 1;

        // relax
        EdgeNode *p = adj[idx].destListHead;
        while (p != nullptr) {
            if (dist[idx] + p->weight < dist[p->destId]) {
                dist[p->destId] = dist[idx] + p->weight;
                parent[p->destId] = idx;
            }
            p = p->next;
        }

    }

    print_dist(totalVertices, dist, INF);

    print_path(6, parent);
}

void dijkstra_minheap(const int& sourceVertexId, const AdjList& adj, const int& totalVertices) {

    MinHeap<Edge> heap;

    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));
    int* visited = new int[totalVertices];
    memset(visited, 0, totalVertices * sizeof(int));

    EdgeNode* p = adj[sourceVertexId].destListHead;
    while (p != nullptr) {
        heap.insert(Edge(sourceVertexId, p->destId, p->weight));
        p = p->next;
    }

    while (!heap.empty()) {
        Edge e = heap.extractMin();
        if (visited[e.sourceId])
            continue;
        visited[e.sourceId] = 1;
//        std::cout << e.sourceId << " " << e.destId << std::endl;
        parent[e.destId] = e.sourceId;
        p = adj[e.destId].destListHead;
        while (p != nullptr) {
            heap.insert(Edge(e.destId, p->destId, e.pathLength + p->weight));
            p = p->next;
        }
    }

    print_path(6, parent);
}


#endif //GRAPH_LAB_DIJAKSTRA_H
