//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_ADJLIST_H
#define GRAPH_LAB_ADJLIST_H

#include "listentry.h"

class AdjList {
public:
    std::vector<ListEntry> srcList;
    int edgeCount = 0;

    bool addVertex(const int& vertexId) {
        if (vertexId < srcList.size())
            return false;
        srcList.insert(srcList.begin() + vertexId, ListEntry(vertexId));
        return true;
    }

    bool addEdge(const int& sourceId, const int& destId, const double& weight = 0) {
        if (sourceId < 0 || sourceId >= srcList.size())
            return false;
        edgeCount++;
        return srcList[sourceId].addEdge(destId, weight);
    }

    bool removeEdge(const int& sourceId, const int& destId) {
        if (sourceId < 0 || sourceId >= srcList.size())
            return false;
        edgeCount--;
        return srcList[sourceId].removeEdge(destId);
    }

    bool removeVertex(const int& vertexId) {
        if (vertexId < 0 || vertexId > srcList.size() - 1)
            return false;
        srcList.erase(srcList.begin() + vertexId);
        for (ListEntry entry : srcList) {
            entry.removeVertex(vertexId);
        }
        return true;
    }

    int entrySize() const {
        return srcList.size();
    }

    ListEntry& operator[](const int& i) {
        return srcList[i];
    }

    const ListEntry& operator[](const int& i) const {
        return srcList[i];
    }

    int edges() const {
        return edgeCount;
    }

};

#endif //GRAPH_LAB_ADJLIST_H
