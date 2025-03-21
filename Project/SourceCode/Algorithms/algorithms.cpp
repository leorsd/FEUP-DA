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
        for (Edge *e : v->getAdj()) {
            e->setAvoid(false);
        }
    }
}

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode, std::list<int>* restrictedRoute, int* restrictedRouteTime) {
    *restrictedRouteTime = 0;

    if(includeNode == nullptr){
        dijkstraDriving(graph, sourceNode, destNode);

        Vertex *current = destNode;
        while(current->getPath()){
            restrictedRoute->push_front(current->getId());
            *restrictedRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }

        restrictedRoute->push_front(sourceNode->getId());
    } else{

        dijkstraDriving(graph, sourceNode, includeNode);

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

        dijkstraDriving(graph, includeNode, destNode);

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