#ifndef MUTABLEPRIORITYQUEUE_H
#define MUTABLEPRIORITYQUEUE_H

#include <vector>
#include "graph.h"

class MutablePriorityQueue {
    std::vector<Vertex *> H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, Vertex * x);
public:
    MutablePriorityQueue();
    void insert(Vertex * x);
    Vertex * extractMin();
    void decreaseKey(Vertex * x);
    bool empty();
};

#endif /* MUTABLEPRIORITYQUEUE_H */
