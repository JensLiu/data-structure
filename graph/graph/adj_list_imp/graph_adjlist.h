//
// Created by Jens on 14.12.2021.
//

#ifndef GRAPH_LAB_GRAPH_ADJLIST_H
#define GRAPH_LAB_GRAPH_ADJLIST_H

#include "adj_list_inner/adjlist.h"

template <typename T>
class Graph {
public:
    std::vector<T> vertexMap;
    AdjList adjList;

public:

    bool constructFromAdjMat(const int** adjMat) {

    }

    bool addVertex(const T& data) {
        vertexMap.push_back(data);
        return adjList.addVertex(vertexMap.size() - 1);
    }

    bool addEdgeById(const int& sourceId, const int& destId, double weight = 0) {
        return adjList.addEdge(sourceId, destId, weight);
    }

    bool removeVertexById(const int& vertexId) {
        if (vertexId < 0 || vertexId > vertexMap.size() - 1)
            return false;
        vertexMap.erase(vertexMap.begin() + vertexId);
        return adjList.removeVertex(vertexId);
    }

    bool addEdge(const T& source, const T& dest, double weight = 0) {
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
        return addEdgeById(sourceId, destId, weight);
    }

    bool removeVertex(const T& vertex) {
        int vertexId = -1;
        for (int i = 0; i < vertexMap.size(); i++) {
            if (vertexMap[i] == vertex) {
                vertexId = i;
                break;
            }
        }
        return removeVertexById(vertexId);
    }

    int totalVertices() const {
        return vertexMap.size();
    }

    void printAdjList() {
        std::vector<ListEntry>vlist = adjList.srcList;
        for (int i = 0; i < vlist.size(); i++) {
            std::cout << vertexMap[i] << "->";
            EdgeNode* p = vlist[i].destListHead;
            while (p != nullptr) {
                std::cout << vertexMap[p->destId] << " ";
                p = p->next;
            }
            std::cout << std::endl;
        }
    }

};
#endif //GRAPH_LAB_GRAPH_ADJLIST_H
