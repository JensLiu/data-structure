//
// Created by Jens on 16.12.2021.
//

#ifndef GRAPH_LAB_EDGE_H
#define GRAPH_LAB_EDGE_H
class Edge {
public:
    int sourceId;
    int destId;
    double pathLength;
    Edge() : sourceId(-1), destId(-1), pathLength(-1) {}
    Edge(int sourceId, int destId, double pathLength)
            : sourceId(sourceId), destId(destId), pathLength(pathLength) {}
    bool operator<(Edge other) const {
        return this->pathLength < other.pathLength;
    }
    bool operator>(Edge other) const {
        return this->pathLength > other.pathLength;
    }
};
#endif //GRAPH_LAB_EDGE_H
