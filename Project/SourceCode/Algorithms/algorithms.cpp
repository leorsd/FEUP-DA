#include "algorithms.h"

bool relaxDriving(Edge *edge) {
    Vertex *org = edge->getOrig();
    Vertex *dest = edge->getDest();

    if (org->getDist() + edge->getDrivingTime() < dest->getDist()) {
        dest->setDist(org->getDist() + edge->getDrivingTime());
        dest->setPath(edge);
        return true;
    }
    return false;
}

bool relaxWalking(Edge *edge) {
    Vertex *org = edge->getOrig();
    Vertex *dest = edge->getDest();

    if (org->getDist() + edge->getWalkingTime() < dest->getDist()) {
        dest->setDist(org->getDist() + edge->getWalkingTime());
        dest->setPath(edge);
        return true;
    }
    return false;
}

void dijkstraDriving(Graph *g, Vertex *sourceNode, Vertex *destNode) {
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
            if (!e->getAvoid() && !e->getDest()->getAvoid() && relaxDriving(e)) {
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

void dijkstraWalking(Graph *g, Vertex *sourceNode, Vertex *destNode) {
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
            if (!e->getAvoid() && !e->getDest()->getAvoid() && relaxWalking(e)) {
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


    dijkstraDriving(graph, sourceNode, destNode);

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


    dijkstraDriving(graph, sourceNode, destNode);
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
      dijkstraDriving(graph, sourceNode, destNode);
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

      dijkstraDriving(graph, sourceNode, includeNode);
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

      dijkstraDriving(graph, includeNode, destNode);
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

void bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime, std::list<int>* drivingRoute, std::list<int>* walkingRoute, int* drivingTime, int* walkingTime) {
    std::vector<std::pair<std::list<int> *, int>> drivingRoutes;
    std::vector<std::pair<std::list<int> *, int>> walkingRoutes;

    std::set<Vertex *> parkingNodes;
    for ( Vertex *v : graph->getVertexSet()) {
        if (v->getParking()){
          parkingNodes.insert(v);
        }
    }

    dijkstraDriving(graph, sourceNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int>* tempDrivingRoute;
        int tempTime = 0;
        while(v->getPath()){
          tempDrivingRoute->push_front(v->getId());
          tempTime += v->getPath()->getDrivingTime();
          v = v->getPath()->getOrig();
        }
        drivingRoutes.push_back({tempDrivingRoute,tempTime});
    }

    dijkstraWalking(graph, sourceNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int>* tempWalkingRoute;
        int tempWalkingTime = 0;
        while(v->getPath()){
            tempWalkingRoute->push_front(v->getId());
            tempWalkingTime += v->getPath()->getWalkingTime();
            v = v->getPath()->getOrig();
        }
        walkingRoutes.push_back({tempWalkingRoute,tempWalkingTime});
    }

    for (auto driv : drivingRoutes) {
        for ( auto walk : walkingRoutes) {
            if (driv.first->back() == walk.first->front() && walk.second <= maxWalkTime){
                if ((driv.second+walk.second < (*walkingTime + *drivingTime)) || (driv.second+walk.second == (*walkingTime + *drivingTime) && walk.second>*walkingTime)){
                    *drivingTime = driv.second;
                    *walkingTime = walk.second;
                    drivingRoute = driv.first;
                    walkingRoute = walk.first;
                }
            }
        }
    }
}