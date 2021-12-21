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
    double INF = DBL_MAX;
    int* parent = new int[totalVertices];
    memset(parent, -1, totalVertices * sizeof(int));
    double * dist = new double[totalVertices];
    memset(dist,0x7f,totalVertices * sizeof(double));
    dist[0] = 0;
    parent[0] = 0;

    using DistPair = std::pair<int, int>; // dist_pair <pathLength, destVertexId>
    using EdgeNode = EdgeNode<EdgeInfo>;
    std::priority_queue<DistPair, std::vector<DistPair>, std::greater<DistPair>> pq;
    pq.push(DistPair(0, 0));

    while (!pq.empty()) {
        DistPair min = pq.top();
        pq.pop();

        EdgeNode* p = adj[min.second].destListHead;
        while (p != nullptr) {
            if (dist[p->destId] > min.first + p->weight) {
                dist[p->destId] = min.first + p->weight;

                parent[p->destId] = min.second;

                pq.push(DistPair(min.first + p->weight, p->destId));
            }
            p = p->next;
        }
    }

    for (int i = 0; i < totalVertices; i++) {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < totalVertices; i++) {
        std::cout << std::setw(2) << dist[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < totalVertices; i++) {
        std::cout << std::setw(2) << parent[i] << " ";
    }
    std::cout << std::endl;


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
