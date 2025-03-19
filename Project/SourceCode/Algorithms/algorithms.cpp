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
        v->setDist(0);
        for (Edge *e : v->getAdj()) {
            e->setAvoid(false);
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