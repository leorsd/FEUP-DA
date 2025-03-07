// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include <math.h>
#include <stack>

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> *dest = edge->getDest();
    Vertex<T> *src = edge->getOrig();
    if (src->getDist() + edge->getWeight() < dest->getDist()) {
        dest->setDist(src->getDist() + edge->getWeight());
        dest->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    MutablePriorityQueue<Vertex<T>> pq;
    for (Vertex<T>* v:g->getVertexSet()) {
        v->setDist(INFINITY);
        v->setPath(nullptr);
        pq.insert(v);
    }
    Vertex<T>* orig = g->findVertex(origin);
    orig->setDist(0);
    pq.decreaseKey(orig);
    while (!pq.empty()) {
        Vertex<T> *v = pq.extractMin();
        for (Edge<T> *e:v->getAdj()) {
            if (relax(e)) {
                pq.decreaseKey(e->getDest());
            }
        }
    }
}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<T> res;
    stack<T> s;
    Vertex<T> *d = g->findVertex(dest);
    Vertex<T> *v = g->findVertex(origin);
    while (d->getPath()->getOrig() != v) {
        s.push(d->getInfo());
        d=d->getPath()->getOrig();
    }
    s.push(d->getInfo());
    s.push(origin);
    while (!s.empty()) {
        T top = s.top();
        s.pop();
        res.push_back(top);
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

template <class T>
 static void checkAllPaths(Graph<T> &g, std::string expected) {
    std::stringstream ss;
    std::vector<Vertex<T> *> vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != nullptr ) {
            ss << vs[i]->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}


static void checkSinglePath(std::vector<int> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    EXPECT_EQ(expected, ss.str());
}

TEST(TP3_Ex4, test_dijkstra) {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    dijkstra(&myGraph, 3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    dijkstra(&myGraph, 1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(getPath(&myGraph, 1, 7), "1 2 4 5 7 ");

    dijkstra(&myGraph,5);
    checkSinglePath(getPath(&myGraph, 5, 6), "5 7 6 ");

    dijkstra(&myGraph, 7);
    checkSinglePath(getPath(&myGraph, 7, 1), "7 6 4 3 1 ");

}