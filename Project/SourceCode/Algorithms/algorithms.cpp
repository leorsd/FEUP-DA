// algorithms.cpp
#include "algorithms.h"
#include <stack>
#include "MutablePriorityQueue.h"
#include <iostream>
#include <sstream>
#include <iomanip>

bool relax(Edge *edge) {
    Vertex *org = edge->getOrig();
    Vertex *dest = edge->getDest();

    if (org->getDist() + edge->getDrivingTime() < dest->getDist()) {
        dest->setDist(org->getDist() + edge->getDrivingTime());
        dest->setPath(edge);
        return true;
    }
    return false;
}

void dijkstra(Graph *g, Vertex *sourceNode, Vertex *destNode = nullptr) {
    auto *pq = new MutablePriorityQueue();
    for (Vertex *v : g->getVertexSet()) {
        v->setPath(nullptr);
        v->setDist(INF);
        pq->insert(v);
    }
    sourceNode->setDist(0);
    pq->decreaseKey(sourceNode);

    while (!pq->empty()) {
        Vertex *v = pq->extractMin();

        if(v->getAvoid()) continue;

        for (Edge *e : v->getAdj()) {
            if (!e->getAvoid() && relax(e)) {
                pq->decreaseKey(e->getDest());
            }
        }
        if(destNode && v == destNode){
          delete pq;
          return;
        }
    }
    delete pq;
}

void independentRoute(Graph *graph, Vertex *sourceNode, Vertex *destNode) {
    std::stringstream bestRouteStr;
    std::stringstream alternativeRouteStr;
    int bestRouteTime = 0;
    int alternativeRouteTime = 0;


    dijkstra(graph, sourceNode);
    std::stack<Vertex *> bestRouteStack;
    Vertex *current = destNode;
    while (current && current->getPath()) {
        bestRouteStack.push(current);
        bestRouteTime += current->getPath()->getDrivingTime();
        current = current->getPath()->getOrig();
    }
    bestRouteStack.push(sourceNode);

    if (bestRouteStack.size() == 1 && bestRouteStack.top() != destNode) {
        // output para quando não há melhor caminho e, por consequência não há caminho alternativo
    } else {
        std::vector<Vertex *> bestRoute;
        while (!bestRouteStack.empty()) {
            bestRoute.push_back(bestRouteStack.top());
            bestRouteStack.pop();
        }

        for (std::size_t i = 0; i < bestRoute.size(); ++i) {
            bestRoute[i]->setAvoid(true);
        }

        for (std::size_t i = 0; i < bestRoute.size() - 1; i++) {
            for (Edge *edge : bestRoute[i]->getAdj()) {
                if (edge->getDest()->getId() == bestRoute[i + 1]->getId()) {
                    edge->setAvoid(true);
                }
            }
        }

        // 


        dijkstra(graph, sourceNode);
        std::stack<Vertex *> alternativeRouteStack;
        current = destNode;
        while (current && current->getPath()) {
            alternativeRouteStack.push(current);
            alternativeRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }
        alternativeRouteStack.push(sourceNode);

        if (alternativeRouteStack.size() == 1 && alternativeRouteStack.top() != destNode) {
               // não há caminho alternativo
        } else {
            std::vector<Vertex *> alternativeRoute;
            while (!alternativeRouteStack.empty()) {
                alternativeRoute.push_back(alternativeRouteStack.top());
                alternativeRouteStack.pop();
            }
        }


        for (Vertex *v : bestRoute) {
            v->setAvoid(false);
        }
        for (std::size_t i = 0; i < bestRoute.size() - 1; i++) {
            for (Edge *edge : bestRoute[i]->getAdj()) {
                if (edge->getDest()->getId() == bestRoute[i + 1]->getId()) {
                    edge->setAvoid(false);
                }
            }
        }
    }

}

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode){
    int total_time = 0;
    std::vector<Vertex *> route;

    if(includeNode == nullptr){
      dijkstra(graph, sourceNode, destNode);
      if(destNode->getDist() == INF){
          // not found
          return;
      }

      std::stack<Vertex *> path;
      Vertex *current = destNode;
      while(current && current->getPath()){
        path.push(current);
        total_time += current->getPath()->getDrivingTime();
        current = current->getPath()->getOrig();
      }

      path.push(sourceNode);
      while(!path.empty()){
        route.push_back(path.top());
        path.pop();
      }


    } else{

      dijkstra(graph, sourceNode, includeNode);
      if(includeNode->getDist() == INF){
        // n encontrou o includeNode
        return;
      }

      std::stack<Vertex *> path1;
      Vertex *current = includeNode;
      while(current && current->getPath()){
        path1.push(current);
        total_time += current->getPath()->getDrivingTime();
        current = current->getPath()->getOrig();
      }
      path1.push(sourceNode);

      dijkstra(graph, includeNode, destNode);
      if(destNode->getDist() == INF){
        // n encontrou o destNode
        return;
      }
      std::stack<Vertex *> path2;
      current = destNode;
      while(current && current->getPath()){
        path2.push(current);
        total_time += current->getPath()->getDrivingTime();
        current = current->getPath()->getOrig();
      }

      while(!path1.empty()){
        route.push_back(path1.top());
        path1.pop();
      }
      path2.pop(); // evitar que o includedNode apareça duas vezes
      while(!path2.empty()){
        route.push_back(path2.top());
        path2.pop();
      }
    }
}

void bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime){
  //Implement task T3.1
  std::cout<<"Best Route "<<std::endl;
}