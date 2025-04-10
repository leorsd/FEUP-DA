#include "mutablePriorityQueue.h"

/**
 * @file mutablePriorityQueue.cpp
 * @brief Implementation of a mutable priority queue using a binary heap declared in the mutablePriorityQueue.h
 */

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

MutablePriorityQueue::MutablePriorityQueue() {
    H.push_back(nullptr);
}

bool MutablePriorityQueue::empty() {
    return H.size() == 1;
}

Vertex* MutablePriorityQueue::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

void MutablePriorityQueue::insert(Vertex *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

void MutablePriorityQueue::decreaseKey(Vertex *x) {
    heapifyUp(x->queueIndex);
}

void MutablePriorityQueue::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void MutablePriorityQueue::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size()) break;
        if (k + 1 < H.size() && *H[k + 1] < *H[k]) ++k;
        if (!(*H[k] < *x)) break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

void MutablePriorityQueue::set(unsigned i, Vertex *x) {
    H[i] = x;
    x->queueIndex = i;
}