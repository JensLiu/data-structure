//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_GRAPH_ADJLIST_H
#define GRAPH_LAB_GRAPH_ADJLIST_H

#include <cstring>
#include <algorithm>
#include <iomanip>
#include "adjlist.h"
#include "minheap.h"
#include "findunion.h"
#include "edge.h"
#include "queue"

#ifndef DBL_MAX
#define DBL_MAX __DBL_MAX__
#endif

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

    std::vector<Edge<EdgeInfo>> removeVertexById(const int& vertexId) {
        if (vertexId < 0 || vertexId > vertexMap.size() - 1)
            return std::vector<Edge<EdgeInfo>>();
        std::vector<Edge<EdgeInfo>> removedEdges;

        EdgeNode<EdgeInfo>* p = adjList[vertexId].destListHead;
        while (p != nullptr) {
            removedEdges.push_back(Edge<EdgeInfo>(vertexId, p->destId, p->info, p->weight));
            p = p->next;
        }

        vertexMap.erase(vertexMap.begin() + vertexId);
        if (adjList.removeVertex(vertexId, removedEdges))
            return removedEdges;

        return std::vector<Edge<EdgeInfo>>();
    }

    Edge<EdgeInfo> removeEdgeById(const int& sourceId, const int& destId) {
        return adjList.removeEdge(sourceId, destId);
    }

    int inDegreeOfVertexById(const int& vertexId) {
        if (vertexId < 0 || vertexId >= adjList.entrySize())
            return -1;
        return adjList[vertexId].getInDegree();
    }

    int outDegreeOfVertexById(const int& vertexId) {
        if (vertexId < 0 || vertexId >= adjList.entrySize())
            return -1;
        return adjList[vertexId].getOutDegree();
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

    int inDegreeOfVertex(const VertexInfo& vertex) {
        return inDegreeOfVertexById(idOfVertex(vertex));
    }

    int outDegreeOfVertex(const VertexInfo& vertex) {
        return outDegreeOfVertexById(idOfVertex(vertexMap));
    }

    std::vector<Edge<EdgeInfo>> removeVertex(const VertexInfo& vertex) {
        int vertexId = idOfVertex(vertex);
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

    Edge<EdgeInfo> removeEdge(const VertexInfo& source, const VertexInfo& dest) {
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
        return removeEdgeById(sourceId, destId);
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
                std::cout << "(id=" << p->destId << ", d=" << vertexMap[p->destId] << ", info=" << p->info << "), ";
                p = p->next;
            }
            std::cout << "]), " << std::endl;
        }
        std::cout << "]" << std::endl;
    }

    Edge<EdgeInfo> findEdge(const int& sourceId, const int& destId) {
        if (sourceId < 0 || sourceId >= adjList.srcList.size()) {
            return Edge<EdgeInfo>();
        }
        EdgeNode<EdgeInfo>* p = adjList[sourceId].destListHead;
        while (p != nullptr) {
            if (p->destId == destId) {
                return Edge<EdgeInfo>(sourceId, destId, p->info, p->weight);
            }
            p = p->next;
        }
        return Edge<EdgeInfo>();
    }

    std::pair<int, int> degreeOfVertexById(const int& vertexId) {
        int inDegree = 0;
        int outDegree = 0;
        for (int i = 0; i < adjList.entrySize(); i++) {
            EdgeNode<EdgeInfo>* p = adjList[i].destListHead;
            if (i == vertexId) {
                while (p != nullptr) {
                    outDegree++;
                }
            } else {
                while (p != nullptr) {
                    if (p->destId == vertexId) {
                        inDegree++;
                    }
                    p = p->next;
                }
            }
        }
        return std::make_pair(inDegree, outDegree);
    }

    std::pair<int, int> degreeOfVertex(VertexInfo vertex) {
        return degreeOfVertexById(idOfVertex(vertex));
    }

public:
    std::vector<Edge<EdgeInfo>> bfs(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
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

    void dfsVisit(const int& s, const AdjList<EdgeInfo>& adj, int* parent, std::vector<Edge<EdgeInfo>>& edges) {
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

    std::vector<Edge<EdgeInfo>> dfs(const AdjList<EdgeInfo>& adj, const int& totalVertices) {

        int* parent = new int[totalVertices];
        memset(parent, -1, totalVertices * sizeof(int));
        parent[0] = -2;

        std::vector<Edge<EdgeInfo>> edges;

        for (int i = 0; i < adj.entrySize(); i++) {
            if (parent[i] == -1 || parent[i] == -2)
                dfsVisit(i, adj, parent, edges);
        }

        std::reverse(edges.begin(), edges.end());

        return edges;
    }

    std::vector<std::vector<Edge<EdgeInfo>>> dijkstra(const int& sourceVertexId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        using ResultSet = std::vector<std::vector<Edge<EdgeInfo>>>;
        using DistPair = std::pair<int, int>;
        using EdgeNode = EdgeNode<EdgeInfo>;
        using Edge = Edge<EdgeInfo>;
        double INF = DBL_MAX;

        int* parent = new int[totalVertices];
        double* dist = new double[totalVertices];
        std::priority_queue<DistPair, std::vector<DistPair>, std::greater<DistPair>> pq;

        memset(parent, -1, totalVertices * sizeof(int));
        memset(dist, 0x7f, totalVertices* sizeof(double));

        dist[sourceVertexId] = 0;
        parent[sourceVertexId] = -2;

        pq.push(DistPair(0, sourceVertexId));

        while (!pq.empty()) {

            DistPair minPair = pq.top();
            pq.pop();
            int len = minPair.first;
            int src = minPair.second;

            EdgeNode* p = adj[src].destListHead;
            while (p != nullptr) {
                if (dist[p->destId] > len + p->weight) {
                    dist[p->destId] = len + p->weight;
                    parent[p->destId] = src;
                    pq.push(DistPair(len + p->weight, p->destId));
                }
                p = p->next;
            }
        }
        ResultSet resultSet;
        dijkstraPackResult(parent, totalVertices,resultSet);
        return resultSet;
    }

    std::vector<Edge<EdgeInfo>> kruskal(const AdjList<EdgeInfo>& adj, const int& totalVertices) {
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

    std::vector<Edge<EdgeInfo>> prim(const int& sourceId, const AdjList<EdgeInfo>& adj, const int& totalVertices) {
        using EdgeNode = EdgeNode<EdgeInfo>;
        using Edge = Edge<EdgeInfo>;
        double INF = DBL_MAX;

        std::vector<Edge> result;

        double * mincost = new double [totalVertices];
        int* parent = new int[totalVertices];

        memset(mincost, 0x7f, totalVertices * sizeof(double));
        memset(parent, -1, totalVertices * sizeof(int));

        parent[sourceId] = -1;
        mincost[sourceId] = 0;

        EdgeNode* p0 = adj[sourceId].destListHead;
        while (p0 != nullptr) {
            mincost[p0->destId] = p0->weight;
            parent[p0->destId] = sourceId;
            p0 = p0->next;
        }

        while (true) {
            double min = INF;
            int minIdx = -1;
            for (int i = 0; i < totalVertices; i++) {
                if (mincost[i] != 0 && mincost[i] < min) {
                    minIdx = i;
                    min = mincost[i];
                }
            }
            if (minIdx == -1)
                break;
            mincost[minIdx] = 0;
            EdgeNode* p = adj[minIdx].destListHead;
            while (p != nullptr) {
                if (mincost[p->destId] > mincost[minIdx] + p->weight) {
                    parent[p->destId] = minIdx;
                    mincost[p->destId] = mincost[minIdx] + p->weight;
                }
                p = p->next;
            }
        }

        primPackResult(sourceId, parent, totalVertices, result);
        std::reverse(result.begin(), result.end());
        return result;

    }


    void dijkstraPackResult(int* parent, int totalVertices, std::vector<std::vector<Edge<EdgeInfo>>>& resultSet) {
        using EachPath = std::vector<Edge<EdgeInfo>>;
        for (int i = 0; i < totalVertices; i++) {
            EachPath result;
            int k = i;
            while (k != -2) {
                if (k >= 0 && k < totalVertices && parent[k] >= 0 && parent[k] < totalVertices) {
                    result.push_back(findEdge(parent[k], k));
                    k = parent[k];
                } else {
                    break;
                }
            }
            std::reverse(result.begin(), result.end());
            resultSet.push_back(result);
        }
    }


    void primPackResult(int s, int* parent, int totalVertices, std::vector<Edge<EdgeInfo>>& result) {
        for (int i = 0; i < totalVertices; i++) {
            if (parent[i] == s) {
                primPackResult(i, parent, totalVertices, result);
            }
        }
        if (parent[s] != -1)
             result.push_back(findEdge(parent[s], s));
    }

public:
    std::vector<Edge<EdgeInfo>> bfs(const int& sourceId = 0) {
        return bfs(sourceId, this->adjList, this->totalVertices());
    }

    std::vector<Edge<EdgeInfo>> dfs() {
        return dfs(this->adjList, this->totalVertices());
    }

    std::vector<std::vector<Edge<EdgeInfo>>> dijkstra(const int& sourceId = 0) {
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
