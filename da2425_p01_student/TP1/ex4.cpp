#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Kosaraju-Sharir algorithm
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;

    stack<T> s;
    dfs_helper(g,&s);

    Graph<T> scc_graph;
    for (Vertex<T>* v: g->getVertexSet()) {
        scc_graph.addVertex(v->getInfo());
    }
    for (Vertex<T>* v: g->getVertexSet()) {
        for (Edge<T>* e: v->getAdj()) {
            scc_graph.addEdge(e->getDest()->getInfo(),v->getInfo(),e->getWeight() );
        }
    }
    for (Vertex<T>* v: scc_graph.getVertexSet()) {
        v->setVisited(false);
    }

    while (!s.empty()) {
        Vertex<T>* v = scc_graph.findVertex(s.top());
        if (!v->isVisited()) {
            vector<T> r;
            dfs2(v,&r);
            sccs.push_back(r);
        }
        s.pop();
    }
    return sccs;
}

template <typename T>
void dfs2(Vertex<T>* v, vector<T>* ve) {
    v->setVisited(true);
    ve->push_back(v->getInfo());
    for (Edge<T>* e: v->getAdj()) {
        Vertex<T>* u = e->getDest();
        if (!u->isVisited()) {
            dfs2(u, ve);
        }
    }
}

template <typename T>
void dfs(Vertex<T>* v, stack<T>* s) {
    v->setVisited(true);
    for (Edge<T>* e: v->getAdj()) {
        Vertex<T>* u = e->getDest();
        if (!u->isVisited()) {
            dfs(u, s);
        }
    }
    s->push(v->getInfo());
}

template <typename T>
void dfs_helper(Graph<T>* graph, stack<T>* s) {
    for (Vertex<T>* v: graph->getVertexSet()) {
        v->setVisited(false);
    }
    for (Vertex<T>* v: graph->getVertexSet()) {
        if (!v->isVisited()) {
            dfs(v,s);
        }
    }
}



