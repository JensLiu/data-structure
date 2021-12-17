//
// Created by Jens on 15.12.2021.
//

#ifndef GRAPH_LAB_MINHEAP_H
#define GRAPH_LAB_MINHEAP_H
#include <vector>
template <typename T>
class MinHeap {
public:
    std::vector<T> heap;

    bool (*compare)(T self, T other);
    void setCompare(bool (*compare)(T self, T other)) {
        this->compare = compare;
    }

    int left(const int& i) { return i * 2 + 1; };
    int right(const int& i) { return i * 2 + 2; };
    int parent(const int& i) { return i / 2; };

    void minHeapify(const int& i) {
        int l = left(i);
        int r = right(i);
        int min = i;
        if (l < heap.size() && heap[l] < heap[min]) min = l;
        if (r < heap.size() && heap[r] < heap[min]) min = r;
        if (min != i) {
            T t = heap[i]; heap[i] = heap[min]; heap[min] = t;
            minHeapify(min);
        }
    }

    void insert(const T& key) {
        heap.push_back(key);
        int i = heap.size() - 1;
        while (i != 0 && heap[parent(i)] > heap[i]) {
            T t = heap[i]; heap[i] = heap[parent(i)]; heap[parent(i)] = t;
            i = parent(i);
        }
    }

    T extractMin() {
        T top = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        minHeapify(0);
        return top;
    }

    bool empty() {
        return heap.empty();
    }

};
#endif //GRAPH_LAB_MINHEAP_H
