#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include <set>
#include "graph.h"
#include "mutablePriorityQueue.h"

enum RouteResult {
    NO_PARKING_AVAILABLE,
    WALKING_TIME_EXCEEDED,
    INVALID_ROUTE,
    NO_DRIVING_AVAILABLE,
    NO_WALKING_AVAILABLE,
    VALID_ROUTE,
};

bool relaxDriving(Edge *edge);

bool relaxWalking(Edge *edge);

void dijkstraDriving(Graph *g, Vertex *sourceNode, Vertex *destNode);

void dijkstraWalking(Graph *g, Vertex *sourceNode, Vertex *destNode);

void independentRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* bestRoute, int* bestRouteTime, std::list<int>* alternativeRoute, int* alternativeRouteTime);

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode, std::list<int>* restrictedRoute, int* restrictedRouteTime);

RouteResult bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime, std::list<int>* drivingRoute, int* drivingTime, std::list<int>* walkingRoute, int* walkingTime);

void aproximateSolution(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* drivingRoute1, int* drivingTime1, std::list<int>* walkingRoute1, int* walkingTime1, std::list<int>* drivingRoute2, int* drivingTime2, std::list<int>* walkingRoute2, int* walkingTime2);

#endif //ALGORITHMS_H
