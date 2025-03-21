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

bool relaxDriving(Edge *edge);

bool relaxWalking(Edge *edge);

void dijkstraDriving(Graph *g, Vertex *sourceNode, Vertex *destNode);

void dijkstraWalking(Graph *g, Vertex *sourceNode, Vertex *destNode);

void independentRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* bestRoute, int* bestRouteTime, std::list<int>* alternativeRoute, int* alternativeRouteTime);

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode);

void bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime, std::list<int>* drivingRoute, std::list<int>* walkingRoute, int* drivingTime, int* walkingTime);

#endif //ALGORITHMS_H
