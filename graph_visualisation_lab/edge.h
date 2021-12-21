//
// Created by Jens on 16.12.2021.
//

#ifndef GRAPH_LAB_EDGE_H
#define GRAPH_LAB_EDGE_H

template <typename EdgeInfo>
class Edge {
public:
    int sourceId;
    int destId;
    double edgeWeight;
    EdgeInfo info;
    Edge() : sourceId(-1), destId(-1), edgeWeight(-1) {}
    Edge(int sourceId, int destId, EdgeInfo info, double pathLength)
            : sourceId(sourceId), destId(destId), info(info), edgeWeight(pathLength) {}
    bool operator<(Edge other) const {
        return this->edgeWeight < other.edgeWeight;
    }
    bool operator>(Edge other) const {
        return this->edgeWeight > other.edgeWeight;
    }
    friend std::ostream& operator<<(std::ostream & os, const Edge<EdgeInfo>& e) {
        os << "(edge=<" << e.sourceId << ", " << e.destId << ">, w=" << e.edgeWeight << ", info=" << e.info << ")";
        return os;
    }
};

#endif //GRAPH_LAB_EDGE_H
