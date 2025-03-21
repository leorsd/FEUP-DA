#include "algorithms.h"

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

void dijkstra(Graph *g, Vertex *sourceNode, Vertex *destNode) {
    auto *pq = new MutablePriorityQueue();
    for (Vertex *v : g->getVertexSet()) {
        if (!v->getAvoid()){
            v->setPath(nullptr);
            v->setDist(INF);
            pq->insert(v);
        }
    }
    sourceNode->setDist(0);
    pq->decreaseKey(sourceNode);

    while (!pq->empty()) {
        Vertex *v = pq->extractMin();

        for (Edge *e : v->getAdj()) {
            if (!e->getAvoid() && !e->getDest()->getAvoid() && relax(e)) {
                pq->decreaseKey(e->getDest());
            }
        }
        if(v == destNode){
          delete pq;
          return;
        }
    }
    delete pq;
}

void independentRoute(Graph *graph, Vertex *sourceNode, Vertex *destNode, std::list<int>* bestRoute, int* bestRouteTime, std::list<int>* alternativeRoute, int* alternativeRouteTime) {
    *bestRouteTime = 0;
    *alternativeRouteTime = 0;


    dijkstra(graph, sourceNode, destNode);

    Vertex *current = destNode;
    while (current->getPath()) {

        current->getPath()->setAvoid(true);
        current->getPath()->getOrig()->setAvoid(true);

        bestRoute->push_front(current->getId());
        *bestRouteTime += current->getPath()->getDrivingTime();

        current = current->getPath()->getOrig();
    }
    bestRoute->push_front(sourceNode->getId());
    sourceNode->setAvoid(false);

    if(bestRoute->size() == 1) {
      return;
    }

        // Alternarive route


    dijkstra(graph, sourceNode, destNode);
    current = destNode;
    while (current && current->getPath()) {
        alternativeRoute->push_front(current->getId());
        *alternativeRouteTime += current->getPath()->getDrivingTime();
        current = current->getPath()->getOrig();
    }
    alternativeRoute->push_front(sourceNode->getId());

    for (Vertex *v : graph->getVertexSet()) {
        v->setAvoid(false);
        v->setPath(nullptr);
        for (Edge *e : v->getAdj()) {
            e->setAvoid(false);
        }
    }
}

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode, std::list<int>* restrictedRoute, int* restrictedRouteTime) {
    *restrictedRouteTime = 0;

    if(includeNode == nullptr){

        dijkstra(graph, sourceNode, destNode);

        Vertex *current = destNode;
        while(current->getPath()){
            restrictedRoute->push_front(current->getId());
            *restrictedRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }

        restrictedRoute->push_front(sourceNode->getId());
    } else{

        dijkstra(graph, sourceNode, includeNode);

        Vertex *current = includeNode;
        while(current->getPath()){
            restrictedRoute->push_front(current->getId());
            *restrictedRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }
        restrictedRoute->push_front(sourceNode->getId());

        if (restrictedRoute->size() == 1) {
          return;
        }

        dijkstra(graph, includeNode, destNode);

        std::list<int> secondPartOfPath;
        current = destNode;

        while(current->getPath()){
            secondPartOfPath.push_front(current->getId());
            *restrictedRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }

        restrictedRoute->splice(restrictedRoute->end(), secondPartOfPath);
    }
}

void bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime){
  //Implement task T3.1
  std::cout<<"Best Route "<<std::endl;
}