#ifndef MUTABLEPRIORITYQUEUE_H
#define MUTABLEPRIORITYQUEUE_H

#include <vector>
#include "graph.h"

/**
 * @brief A class representing a mutable priority queue.
 * 
 * @details This class implements a mutable priority queue using a binary heap. It allows for efficient insertion, extraction of the minimum element, and decreasing the key of an element. It is used in  Dijkstra's algorithm to manage the vertices based on their distances.
 */
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
