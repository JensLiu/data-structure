//
// Created by Jens on 15.12.2021.
//

#ifndef GRAPH_LAB_FINDUNION_H
#define GRAPH_LAB_FINDUNION_H
#include <iostream>

class FindUnion {

    int* parent;
    int* size;
    int count;

public:
    FindUnion(const int& n) {
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
        count = n;
    }

    ~FindUnion() {
        delete parent;
        delete size;
    }

    int find(int n) {
        while (parent[n] != n) {
            n = parent[n];
        }
        return n;
    }

    void insert(const int& i) {
        parent[i] = i;
    }
    void unionElem(const int& m, const int& n) {
        int rootM = find(m);
        int rootN = find(n);
        if (size[rootM] <= size[rootN]) {
            parent[rootN] = rootM;
            size[rootM] += size[rootN];
        } else {
            parent[rootM] = rootN;
            size[rootN] += size[rootM];
        }
        count--;
    }

    bool connected(int m, int n) {
        return find(m) == find(n);
    }

};
#endif //GRAPH_LAB_FINDUNION_H
