// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include <unordered_map>
#include <valarray>

#include "../data_structures/Graph.h"

// Function to test the given vertex 'w' and visit it if conditions are met
template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
    }
    std::queue< Vertex<T>* > q;
    s->setVisited(true);
    q.push(s);
    while (!q.empty()) {
        Vertex<T> *v = q.front();
        q.pop();
        if (v == t) return true;
        for (Edge<T> *adj1 : v->getAdj()) {
            Vertex<T> *dest1 = adj1->getDest();
            double residual = adj1->getWeight() - adj1->getFlow();
            testAndVisit(q, adj1, dest1, residual);
        }
        for (Edge<T> *e : v->getIncoming()) {
            Edge<T> *adj2 = e->getReverse();
            Vertex<T> *dest2 = adj2->getDest();
            testAndVisit(q, adj2, dest2, adj2->getFlow());
        }
    }
    return false;
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    for (auto v = t; v != s; v = v->getPath()->getOrig()) {
        f = std::min(f, std::abs(v->getPath()->getWeight() - v->getPath()->getFlow()));
    }
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    for (auto v = t; v != s; v = v->getPath()->getOrig()) {
        if ( v->getPath()->isSelected()) {
            v->getPath()->setFlow(v->getPath()->getFlow() + f);
            v->getPath()->getReverse()->setFlow(v->getPath()->getReverse()->getFlow() + f);
        }else {
            v->getPath()->setFlow(v->getPath()->getFlow() - f);
            v->getPath()->getReverse()->setFlow(v->getPath()->getReverse()->getFlow() - f);
        }
    }
}

// Function implementing the Edmonds-Karp algorithm
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    for (Vertex<T> *v : g->getVertexSet()) {
        for (Edge<T> *e : v->getAdj()) {
            Edge<T>* reverse = new Edge<T>(e->getDest(), e->getOrig(),0);
            e->setReverse(reverse);
            reverse->setReverse(e);
            e->setFlow(0);
            reverse->setFlow(0);
            e->setSelected(true);
            reverse->setSelected(false);
        }
    }
    Vertex<T> *src = g->findVertex(source);
    Vertex<T> *trg = g->findVertex(target);
    while (findAugmentingPath(g,src,trg)) {
        int minflow = findMinResidualAlongPath(src,trg);
        augmentFlowAlongPath(src,trg,minflow);
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex5, test_edmondsKarp) {
    Graph<int> myGraph;

    for(int i = 1; i <= 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);

    edmondsKarp(&myGraph, 1, 6);

    std::stringstream ss;
    for(auto v : myGraph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());

}