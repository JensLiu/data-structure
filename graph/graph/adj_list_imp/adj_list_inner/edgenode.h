//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_EDGENODE_H
#define GRAPH_LAB_EDGENODE_H

class EdgeNode {
public:
    int destId;
    double weight;
    EdgeNode* next;
    EdgeNode* prev;
    EdgeNode(const int& destId)
            :destId(destId), weight(0), next(nullptr), prev(nullptr) {};
    EdgeNode(const int& destId, const double& weight)
        :destId(destId), weight(weight), next(nullptr), prev(nullptr) {};
};

#endif //GRAPH_LAB_EDGENODE_H
