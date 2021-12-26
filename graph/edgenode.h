//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_EDGENODE_H
#define GRAPH_LAB_EDGENODE_H

template <typename EdgeInfo>
class EdgeNode {
public:
    int destId;
    double weight;
    EdgeInfo info;
    EdgeNode* next;
    EdgeNode* prev;
    EdgeNode(const int& destId)
            :destId(destId), weight(0), next(nullptr), prev(nullptr) {};
    EdgeNode(const int& destId, const double& weight)
        :destId(destId), weight(weight), next(nullptr), prev(nullptr) {};
    EdgeNode(const int& destId, const EdgeInfo& info, const double& weight)
        :destId(destId), info(info), weight(weight), next(nullptr), prev(nullptr) {};
};

#endif //GRAPH_LAB_EDGENODE_H
