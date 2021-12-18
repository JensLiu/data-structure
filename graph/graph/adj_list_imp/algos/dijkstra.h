//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_DIJAKSTRA_H
#define GRAPH_LAB_DIJAKSTRA_H

#include "../graph_adjlist.h"
#include "../../../helper_ds/minheap.h"
#include "../edge.h"
#define DBL_MAX __DBL_MAX__
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
template <typename EdgeInfo>
void dijkstra(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
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
        EdgeNode<EdgeInfo> *p = adj[idx].destListHead;
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

template <typename EdgeInfo>
void dijkstra_minheap(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
    MinHeap<Edge<EdgeInfo>> heap;
    double* dist = new double[totalVertices];
    double INF = DBL_MAX;
    for (int i = 0; i < totalVertices; i++) {
        dist[i] = INF;
    }
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));
    int* visited = new int[totalVertices];
    memset(visited, 0, totalVertices * sizeof(int));
    visited[sourceVertexId] = 1;
    dist[sourceVertexId] = 0;

    EdgeNode<EdgeInfo>* p = adj[sourceVertexId].destListHead;
    while (p != nullptr) {
        heap.insert(Edge<EdgeInfo>(sourceVertexId, p->destId, p->weight));
        p = p->next;
    }

    while (!heap.empty()) {
        Edge<EdgeInfo> minEdge = heap.extractMin();
        if (visited[minEdge.destId]) {
            continue;
        }
        visited[minEdge.destId] = 1;
        if (dist[minEdge.destId] > dist[minEdge.sourceId] + minEdge.edgeWeight) {
            dist[minEdge.destId] = dist[minEdge.sourceId] + minEdge.edgeWeight;
            parent[minEdge.destId] = minEdge.sourceId;
        }
        p = adj[minEdge.destId].destListHead;
        while (p != nullptr) {
            if (!visited[p->destId]) {
                heap.insert(Edge<EdgeInfo>(minEdge.destId, p->destId, p->weight));
            }
            p = p->next;
        }
    }

    for (int i = 0; i < totalVertices; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < totalVertices; i++) {
        std::cout << dist[i] << " ";
    }
    print_path(6, parent);
}


#endif //GRAPH_LAB_DIJAKSTRA_H
