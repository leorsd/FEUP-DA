#include "algorithms.h"

/**
 * @file algorithms.cpp
 * @brief Implementation of the algorithms declared in algorithms.h
 */

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

    // If the includeNode is not provided, we will find the route from sourceNode to destNode using a normal Dijkstra's algorithm
    if(includeNode == nullptr){
        dijkstraDriving(graph, sourceNode, destNode);

        Vertex *current = destNode;
        while(current->getPath()){
            restrictedRoute->push_front(current->getId());
            *restrictedRouteTime += current->getPath()->getDrivingTime();
            current = current->getPath()->getOrig();
        }

        restrictedRoute->push_front(sourceNode->getId());

    // If the includeNode is provided, we will find the route from sourceNode to includeNode and then from includeNode to destNode    
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

        // Stores the segment of the path from includeNode to destNode in the list that already contains the path from sourceNode to includeNode
        restrictedRoute->splice(restrictedRoute->end(), secondPartOfPath);
    }
}

RouteResult bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime, std::list<int>* drivingRoute, int* drivingTime, std::list<int>* walkingRoute, int* walkingTime) {
    std::vector<std::pair<std::list<int>, int>> drivingRoutes;
    std::vector<std::pair<std::list<int>, int>> walkingRoutes;

    std::set<Vertex *> parkingNodes;
    for ( Vertex *v : graph->getVertexSet()) {
        if (v->getParking()){
          parkingNodes.insert(v);
        }
    }

    if (parkingNodes.size() == 0) {
        return NO_PARKING_AVAILABLE;
    }

    // Finds the best driving segments from the source to each parking node and stores them in the drivingRoutes vector

    dijkstraDriving(graph, sourceNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int> tempDrivingRoute = {};
        int tempTime = 0;
        while(v->getPath()){
          tempDrivingRoute.push_front(v->getId());
          tempTime += v->getPath()->getDrivingTime();
          v = v->getPath()->getOrig();
        }
        if ( v == sourceNode) {
            tempDrivingRoute.push_front(v->getId());
            if (tempDrivingRoute.size() > 1) {
              drivingRoutes.push_back({tempDrivingRoute,tempTime});
            }
        }
    }

    if (drivingRoutes.size() == 0) {
        return NO_DRIVING_AVAILABLE;
    }

    // Finds the best walking segments from each parking node to the destination and stores them in the walkingRoutes vector

    dijkstraWalking(graph, destNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int> tempWalkingRoute;
        int tempWalkingTime = 0;
        while(v->getPath()){
            tempWalkingRoute.push_back(v->getId());
            tempWalkingTime += v->getPath()->getWalkingTime();
            v = v->getPath()->getOrig();
        }
        if ( v == destNode) {
            tempWalkingRoute.push_back(v->getId());
            if (tempWalkingRoute.size() > 1) {
              walkingRoutes.push_back({tempWalkingRoute,tempWalkingTime});
            }
        }
    }

    if (walkingRoutes.size() == 0) {
        return NO_WALKING_AVAILABLE;
    }

    bool foundPath = false;
    bool foundWithMaxTime = false;

    // Finds the best combinations of driving and walking routes
    *walkingTime = 1e6;
    *drivingTime = 1e6;
    for (auto driv : drivingRoutes) {
        for ( auto walk : walkingRoutes) {
            if (driv.first.back() == walk.first.front()){
                foundPath = true;
                if ( walk.second <= maxWalkTime ){
                    foundWithMaxTime = true;
                    if ((driv.second+walk.second < (*walkingTime + *drivingTime)) || (driv.second+walk.second == (*walkingTime + *drivingTime) && walk.second>*walkingTime)){
                        *drivingTime = driv.second;
                        *walkingTime = walk.second;
                        drivingRoute->assign(driv.first.begin(), driv.first.end());
                        walkingRoute->assign(walk.first.begin(), walk.first.end());
                    }
                }
            }
        }
    }

    if (!foundPath){
        return INVALID_ROUTE;
    }else if (!foundWithMaxTime){
        return WALKING_TIME_EXCEEDED;
    }

    return VALID_ROUTE;
}

void aproximateSolution(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* drivingRoute1, int* drivingTime1, std::list<int>* walkingRoute1, int* walkingTime1, std::list<int>* drivingRoute2, int* drivingTime2, std::list<int>* walkingRoute2, int* walkingTime2) {
    std::vector<std::pair<std::list<int>, int>> drivingRoutes;
    std::vector<std::pair<std::list<int>, int>> walkingRoutes;

    std::set<Vertex *> parkingNodes;
    for ( Vertex *v : graph->getVertexSet()) {
        if (v->getParking()){
          parkingNodes.insert(v);
        }
    }

    // Finds the best driving segments from the source to each parking node and stores them in the drivingRoutes vector
    dijkstraDriving(graph, sourceNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int> tempDrivingRoute = {};
        int tempTime = 0;
        while(v->getPath()){
          tempDrivingRoute.push_front(v->getId());
          tempTime += v->getPath()->getDrivingTime();
          v = v->getPath()->getOrig();
        }
        if ( v == sourceNode) {
            tempDrivingRoute.push_front(v->getId());
            if (tempDrivingRoute.size() > 1) {
              drivingRoutes.push_back({tempDrivingRoute,tempTime});
            }
        }
    }

    // Finds the best walking segments from each parking node to the destination and stores them in the walkingRoutes vector
    dijkstraWalking(graph, destNode, nullptr);

    for (Vertex *v : parkingNodes) {
        std::list<int> tempWalkingRoute;
        int tempWalkingTime = 0;
        while(v->getPath()){
            tempWalkingRoute.push_back(v->getId());
            tempWalkingTime += v->getPath()->getWalkingTime();
            v = v->getPath()->getOrig();
        }
        if ( v == destNode) {
            tempWalkingRoute.push_back(v->getId());
            if (tempWalkingRoute.size() > 1) {
              walkingRoutes.push_back({tempWalkingRoute,tempWalkingTime});
            }
        }
    }

    // Finds the best combinations of driving and walking routes
    *walkingTime1 = 1e6;
    *drivingTime1 = 1e6;
    *walkingTime2 = 1e6;
    *drivingTime2 = 1e6;
    for (auto driv : drivingRoutes) {
        for ( auto walk : walkingRoutes) {
            if (driv.first.back() == walk.first.front()){
                if ((driv.second+walk.second < (*walkingTime1 + *drivingTime1)) || (driv.second+walk.second == (*walkingTime1 + *drivingTime1) && walk.second>*walkingTime1)){
                    *drivingTime2 = *drivingTime1;
                    *walkingTime2 = *walkingTime1;
                    drivingRoute2->assign(drivingRoute1->begin(), drivingRoute1->end());
                    walkingRoute2->assign(walkingRoute1->begin(), walkingRoute1->end());

                    *drivingTime1 = driv.second;
                    *walkingTime1 = walk.second;
                    drivingRoute1->assign(driv.first.begin(), driv.first.end());
                    walkingRoute1->assign(walk.first.begin(), walk.first.end());
                }else if((driv.second+walk.second < (*walkingTime2 + *drivingTime2)) || (driv.second+walk.second == (*walkingTime2 + *drivingTime2) && walk.second>*walkingTime2)){
                    *drivingTime2 = driv.second;
                    *walkingTime2 = walk.second;
                    drivingRoute2->assign(driv.first.begin(), driv.first.end());
                    walkingRoute2->assign(walk.first.begin(), walk.first.end());
                }
            }
        }
    }
    return;
}