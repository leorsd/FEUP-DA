#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;

/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
template <class T>
vector<T> dfs(Graph<T> *g, const T & source) {
    vector<int> res;
    Vertex<T> *v = g->findVertex(source);
    dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void dfsVisit(Vertex<T> *v, vector<T> & res) {
    res.push_back(v->getInfo());
    v->setVisited(true);
    for (Edge<T> *e : v->getAdj()) {
        if (!e->getDest()->isVisited()) {
            dfsVisit(e->getDest(), res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph, starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <typename T>
vector<T> bfs(Graph<T> *g, const T & source) {
    vector<int> res;
    for (Vertex<T> *v : g->getVertexSet()) {
        v->setVisited(false);
    }
    Vertex<T> *v = g->findVertex(source);
    queue<Vertex<T> *> q;
    q.push(v);
    v->setVisited(true);
    while (!q.empty()) {
        Vertex<T> *u = q.front();
        res.push_back(u->getInfo());
        q.pop();
        for (Edge<T> *e : u->getAdj()) {
            if (!e->getDest()->isVisited()) {
                e->getDest()->setVisited(true);
                q.push(e->getDest());
            }
        }
    }
    return res;
}