//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_ADJLIST_H
#define GRAPH_LAB_ADJLIST_H

#include "listentry.h"
#include "edge.h"

template <typename EdgeInfo>
class AdjList {
public:
    std::vector<ListEntry<EdgeInfo>> srcList;
    int edgeCount = 0;

    bool addVertex(const int& vertexId) {
        if (vertexId < srcList.size())
            return false;
        srcList.insert(srcList.begin() + vertexId, ListEntry<EdgeInfo>(vertexId));
        return true;
    }

    bool addEdge(const int& sourceId, const int& destId, EdgeInfo info = EdgeInfo(), const double& weight = 0) {
        if (sourceId < 0 || sourceId >= srcList.size())
            return false;
        edgeCount++;
        return srcList[sourceId].addEdge(destId, info, weight);
    }

    Edge<EdgeInfo> removeEdge(const int& sourceId, const int& destId) {
        if (sourceId < 0 || sourceId >= srcList.size())
            return Edge<EdgeInfo>();
        edgeCount--;
        return srcList[sourceId].removeEdge(sourceId, destId);
    }

    bool removeVertex(const int& vertexId,
                      std::vector<Edge<EdgeInfo>>& removedEdges = std::vector<Edge<EdgeInfo>>()) {
        if (vertexId < 0 || vertexId > srcList.size() - 1)
            return false;
        srcList.erase(srcList.begin() + vertexId);
        for (ListEntry<EdgeInfo>& entry : srcList) {
            entry.removeVertex(vertexId, removedEdges);
        }
        return true;
    }

    int entrySize() const {
        return srcList.size();
    }

    ListEntry<EdgeInfo>& operator[](const int& i) {
        return srcList[i];
    }

    const ListEntry<EdgeInfo>& operator[](const int& i) const {
        return srcList[i];
    }

    int edges() const {
        return edgeCount;
    }

};

#endif //GRAPH_LAB_ADJLIST_H
