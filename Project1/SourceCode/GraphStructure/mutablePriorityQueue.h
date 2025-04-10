#ifndef MUTABLEPRIORITYQUEUE_H
#define MUTABLEPRIORITYQUEUE_H

#include <vector>
#include "graph.h"

/**
 * @file mutablePriorityQueue.h
 * @brief Defines the MutablePriorityQueue class.
 * 
 * This file contains the definition of the MutablePriorityQueue class, which is used to implement a priority queue for Dijkstra's algorithm.
 * The class is implemented in mutablePriorityQueue.cpp.
 */

/**
 * @brief A class representing a mutable priority queue.
 * 
 * This class implements a mutable priority queue using a binary heap. It provides efficient operations for inserting elements, extracting the minimum element, and decreasing the key of an element. 
 * It is used in Dijkstra's algorithm to manage vertices based on their distances from the source node.
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
