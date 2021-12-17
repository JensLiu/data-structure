//
// Created by Jens on 13.12.2021.
//

#ifndef GRAPH_LAB_ADJMAT_H
#define GRAPH_LAB_ADJMAT_H


#include "../adj_list_imp/adj_list_inner/adjlist.h"
#include <vector>

class AdjMat {
public:
    double** mat;

    const double INF = DBL_MAX;

    AdjMat(const AdjList& list) {
        mat = new double*[list.entrySize()];
        for (int i = 0; i < list.entrySize(); i++) {
            mat[i] = new double[list.entrySize()];
            for (int j = 0; j < list.entrySize(); j++) {
                mat[i][j] = INF;
            }
        }
        _adjListToMat(list);
    }

    void _adjListToMat(AdjList list) {
        for (int i = 0; i < list.entrySize(); i++) {
           EdgeNode* p = list[i].destListHead;
           while (p != nullptr) {
               mat[i][p->destId] = p->weight;
               p = p->next;
           }
        }
    }

};

#endif //GRAPH_LAB_ADJMAT_H
