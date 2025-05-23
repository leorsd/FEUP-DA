#include "../data_structures/Graph.h"
#include <limits>
#include <math.h>

// Function to perform DFS and find an augmenting path
template <class T>
bool dfsFindAugmentingPath(Vertex<T>* v, Vertex<T>* t, double& flow) {
    if (v == t ) {
        return true;
    }
    v->setVisited(true);
    for (Edge<T>* edge : v->getAdj()) {
        if (edge->getFlow() < edge->getWeight() && !edge->getDest()->isVisited() ) {
            double remain_flow = edge->getWeight() - edge->getFlow();
            flow = std::min(flow, remain_flow);
            if (dfsFindAugmentingPath(edge->getDest(), t, flow)) {
                edge->setFlow(edge->getFlow() + flow);
                edge->getReverse()->setFlow(edge->getReverse()->getFlow() + flow);
                return true;
            }
        }
    }
    for (Edge<T>* edge : v->getIncoming()) {
        if (edge->getReverse()->getFlow()>0 && !edge->getReverse()->getDest()->isVisited()) {
            double remain_flow = edge->getReverse()->getFlow();
            flow = std::min(flow, remain_flow);
            if (dfsFindAugmentingPath(edge->getOrig(), t, flow)) {
                edge->setFlow(edge->getFlow() - flow);
                edge->getReverse()->setFlow(edge->getReverse()->getFlow() - flow);
                return true;
            }
        }
    }
    return false;
}

// Ford-Fulkerson algorithm
template <class T>
void fordFulkerson(Graph<T>* g, int source, int target) {
    Vertex<T>* src = g->findVertex(source);
    Vertex<T>* trg = g->findVertex(target);
    double flow = INFINITY;

    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
        for (Edge<T>* edge : v->getAdj()) {
            edge->setFlow(0);
            Edge<T>* e2 = new Edge<T>(edge->getDest(),edge->getOrig(),0);
            edge->setReverse(e2);;
            e2->setReverse(edge);
            e2->setFlow(0);
        }
    }
    while (dfsFindAugmentingPath(src, trg, flow)) {
        flow = INFINITY;
        for (Vertex<T>* v : g->getVertexSet()) {
            v->setVisited(false);
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex6, test_fordFulkerson) {
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

    fordFulkerson(&myGraph, 1, 6);

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
