#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;

/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
*/
template <typename T>
vector<T> topsort(Graph<T> *g) {
    vector<T> res;
    queue<Vertex<T>*> q;
    for (Vertex<T> *v : g->getVertexSet()) {
        for (Edge<T> *e : v->getAdj()) {
            e->getDest()->setIndegree(e->getDest()->getIndegree()+1);
        }
    }
    for (Vertex<T> *v : g->getVertexSet()) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }
    int counter = 0;
    while (!q.empty()) {
        Vertex<T> *u = q.front();
        for (Edge<T> *e : u->getAdj()) {
            e->getDest()->setIndegree(e->getDest()->getIndegree()-1);
            if (e->getDest()->getIndegree() == 0) {
                q.push(e->getDest());
            }
        }
        res.push_back(u->getInfo());
        q.pop();
        counter++;
    }
    if (counter != g->getNumVertex()) {
        return {};
    }
    return res;
}