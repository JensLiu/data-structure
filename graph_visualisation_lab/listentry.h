//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_LISTENTRY_H
#define GRAPH_LAB_LISTENTRY_H

#include "edgenode.h"
#include "edge.h"

template <typename EdgeInfo>
class ListEntry {
public:
    EdgeNode<EdgeInfo>* destListHead;

    ListEntry(const int& nodeId)
            : destListHead(nullptr) {};

    bool addEdge(const int& destId, EdgeInfo info = EdgeInfo(), const double& weight = 0) {
        if (destId < 0)
            return false;

        if (destListHead == nullptr) {
            destListHead = new EdgeNode<EdgeInfo>(destId, info, weight);
        } else {
            EdgeNode<EdgeInfo>* newEdge = new EdgeNode<EdgeInfo>(destId, info, weight);
            newEdge->next = destListHead;
            destListHead->prev = newEdge;
            destListHead = newEdge;
        }

        return true;
    }

    Edge<EdgeInfo> removeEdge(const int& sourceId, const int& destId) {
        if (destId < 0 || destListHead == nullptr)
            return Edge<EdgeInfo>();

        EdgeNode<EdgeInfo>* p = destListHead;
        while (p != nullptr) {
            if (p->destId == destId) {
                Edge<EdgeInfo> removedEdge(sourceId, destId, p->info, p->weight);
                removeNode(p);
                return removedEdge;
            }
            p = p->next;
        }
        return Edge<EdgeInfo>();
    }

    bool removeVertex(const int& vertexId,
                      std::vector<Edge<EdgeInfo>>& removedEdges = std::vector<Edge<EdgeInfo>>()) {
        if (vertexId < 0)
            return false;

        if (destListHead == nullptr)
            return false;

        EdgeNode<EdgeInfo>* p = destListHead;
        while (p != nullptr) {
            if (p->destId == vertexId) {
                EdgeNode<EdgeInfo>* next = p->next;
                removedEdges.push_back(Edge<EdgeInfo>(vertexId, p->destId, p->info, p->weight));
                removeNode(p);
                p = next;
                continue;
            }
            else if (p->destId > vertexId) // decrease value
                p->destId--;
            p = p->next;
        }
        return true;
    }

private:
    bool removeNode(EdgeNode<EdgeInfo>* p) {
        if (p == nullptr) {
            return false;
        } else if (p == destListHead) {
            if (destListHead->next != nullptr) {
                destListHead->next->prev = nullptr;
            }
            destListHead = destListHead->next;
            delete p;
        } else {
            if (p->next != nullptr) {
                p->next->prev = p->prev;
                p->prev->next = p->next;
            } else {
                p->prev->next = nullptr;
            }
            delete p;
        }
        return true;
    }

};


#endif //GRAPH_LAB_LISTENTRY_H
