//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_GRAPH_ADJLIST_H
#define GRAPH_LAB_GRAPH_ADJLIST_H

#include <cstring>
#include <algorithm>
#include <iomanip>
#include "adj_list_inner/adjlist.h"
#include "../../helper_ds/minheap.h"
#include "../../helper_ds/findunion.h"
#include "edge.h"
#include "queue"

#define DBL_MAX __DBL_MAX__

template <typename VertexInfo, typename EdgeInfo>
class Graph {
public:
    std::vector<VertexInfo> vertexMap;
    AdjList<EdgeInfo> adjList;

public:
    bool addVertex(const VertexInfo& data) {
        vertexMap.push_back(data);
        return adjList.addVertex(vertexMap.size() - 1);
    }

    bool addEdgeById(const int& sourceId, const int& destId, EdgeInfo info = EdgeInfo(), double weight = 1) {
        return adjList.addEdge(sourceId, destId, info, weight);
    }

    bool removeVertexById(const int& vertexId) {
        if (vertexId < 0 || vertexId > vertexMap.size() - 1)
            return false;
        vertexMap.erase(vertexMap.begin() + vertexId);
        return adjList.removeVertex(vertexId);
    }

    int idOfVertex(const VertexInfo& data) {
        int id = -1;
        for (int i = 0; i < vertexMap.size(); i++) {
            if (vertexMap[i] == data) {
                id = i;
                break;
            }
        }
        return id;
    }

    bool removeVertex(const VertexInfo& vertex) {
        int vertexId = idOfVertex(vertex);
        std::cout << "[debug:] removeVertex: found vertex (" << "id=" << vertexId << "value=" << vertex << ")" << std::endl;
        return removeVertexById(vertexId);
    }

    bool addEdge(const VertexInfo& source, const VertexInfo& dest, EdgeInfo info, double weight = 1) {
        int sourceId = -1;
        int destId = -1;
        for (int i = 0; i < vertexMap.size(); i++) {
            if (vertexMap[i] == source) {
                sourceId = i;
            }
            if (vertexMap[i] == dest) {
                destId = i;
            }
        }
        return addEdgeById(sourceId, destId, info, weight);
    }

    int totalVertices() const {
        return vertexMap.size();
    }

    void printAdjList() {
        std::vector<ListEntry<EdgeInfo>>vlist = adjList.srcList;
        std::cout << "[" << std::endl;
        for (int i = 0; i < vlist.size(); i++) {
            std::cout << "((id=" << i << ", s=" << vertexMap[i] << "), [";
            EdgeNode<EdgeInfo>* p = vlist[i].destListHead;
            while (p != nullptr) {
                std::cout << "(id=" << p->destId << ", d=" << vertexMap[p->destId] << "), ";
                p = p->next;
            }
            std::cout << "]), " << std::endl;
        }
        std::cout << "]" << std::endl;
    }

public:
    std::vector<Edge<EdgeInfo>> static bfs(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        std::queue<int> queue;
        std::vector<Edge<EdgeInfo>> edges;
        int* parent = new int[totalVertices];
        memset(parent, -1, totalVertices * sizeof(int));
        parent[sourceVertexId] = -2;
        queue.push(sourceVertexId);
        while (!queue.empty()) {
            int cur = queue.front();
            queue.pop();
            EdgeNode<EdgeInfo>* p = adj[cur].destListHead;
            while (p != nullptr) {
                if (parent[p->destId] == -1) {
                    parent[p->destId] = cur;
                    queue.push(p->destId);
                    edges.push_back(Edge<EdgeInfo>(cur, p->destId, p->info, p->weight));
                }
                p = p->next;
            }
        }
        return edges;
    }

    void static dfsVisit(const int& s, const AdjList<EdgeInfo>& adj, int* parent, std::vector<Edge<EdgeInfo>>& edges) {
        EdgeNode<EdgeInfo>* p = adj[s].destListHead;
        while (p != nullptr) {
            if (parent[p->destId] == -1) {
                parent[p->destId] = s;
                dfsVisit(p->destId, adj, parent, edges);
                edges.push_back(Edge<EdgeInfo>(s, p->destId, p->info, p->weight));
            }
            p = p->next;
        }
    }

    std::vector<Edge<EdgeInfo>> static dfs(const AdjList<EdgeInfo>& adj, const int& totalVertices) {

        int* parent = new int[totalVertices];
        memset(parent, -1, totalVertices * sizeof(int));

        std::vector<Edge<EdgeInfo>> edges;

        for (int i = 0; i < adj.entrySize(); i++) {
            if (parent[i] == -1)
                dfsVisit(i, adj, parent, edges);
        }

        std::reverse(edges.begin(), edges.end());

        return edges;
    }

    std::vector<Edge<EdgeInfo>> static dijkstra(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        MinHeap<Edge<EdgeInfo>> heap;
        std::vector<Edge<EdgeInfo>> edges;
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
            heap.insert(Edge<EdgeInfo>(sourceVertexId, p->destId, p->info, p->weight));
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
                edges.push_back(minEdge);
            }
            p = adj[minEdge.destId].destListHead;
            while (p != nullptr) {
                if (!visited[p->destId]) {
                    heap.insert(Edge<EdgeInfo>(minEdge.destId, p->destId, p->info, p->weight));
                }
                p = p->next;
            }
        }

//        for (int i = 0; i < totalVertices; i++) {
//            std::cout << i << " ";
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < totalVertices; i++) {
//            std::cout << dist[i] << " ";
//        }

        return edges;
    }

    std::vector<Edge<EdgeInfo>> static kruskal(const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        FindUnion fu(totalVertices);
        MinHeap<Edge<EdgeInfo>> heap;
        std::vector<Edge<EdgeInfo>> edges;
        int len = 0;
        for (int i = 0; i < totalVertices; i++) {
            EdgeNode<EdgeInfo>* p = adj[i].destListHead;
            while (p != nullptr) {
                heap.insert(Edge<EdgeInfo>(i, p->destId, p->info, p->weight));
                p = p->next;
            }
            fu.insert(i);
        }

        while (!heap.empty()) {
            Edge<EdgeInfo> cur = heap.extractMin();
            if (fu.connected(cur.sourceId, cur.destId))
                continue;
            len += cur.edgeWeight;
            fu.unionElem(cur.sourceId, cur.destId);
            edges.push_back(cur);
        }

        return edges;
    }

    std::vector<Edge<EdgeInfo>> static prim(const int& sourceId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        std::vector<Edge<EdgeInfo>> edges;
        const double INF = DBL_MAX;
        int* parent = new int[totalVertices];
        memset(parent, -1, totalVertices * sizeof(int));

        int len = 0;
        int cur = 0;

        parent[cur] = cur;
        while (true) {
            if (parent[cur] == -1)
                break;

            EdgeNode<EdgeInfo>* p = adj[cur].destListHead;
            EdgeInfo eInfo = EdgeInfo();
            double min = INF;
            int minIdx = -1;
            while (p != nullptr) {
                if (p->weight < min && parent[p->destId] == -1) {
                    min = p->weight;
                    minIdx = p->destId;
                    eInfo = p->info;
                }
                p = p->next;
            }
            if (minIdx == -1)
                break;

            parent[minIdx] = cur;
            edges.push_back(Edge<EdgeInfo>(cur, minIdx, eInfo, min));
            cur = minIdx;
        }
        return edges;
    }

public:
    std::vector<Edge<EdgeInfo>> bfs(const int& sourceId = 0) {
        return bfs(sourceId, this->adjList, this->totalVertices());
    }

    std::vector<Edge<EdgeInfo>> dfs() {
        return dfs(this->adjList, this->totalVertices());
    }

    std::vector<Edge<EdgeInfo>> dijkstra(const int& sourceId = 0) {
        return dijkstra(sourceId, this->adjList, this->totalVertices());
    }

    std::vector<Edge<EdgeInfo>> kruskal() {
        return kruskal(this->adjList, this->totalVertices());
    }

    std::vector<Edge<EdgeInfo>> prim(const int& sourceId = 0) {
        return prim(sourceId, this->adjList, this->totalVertices());
    }


};

#endif //GRAPH_LAB_GRAPH_ADJLIST_H
