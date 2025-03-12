#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

void independentRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode);

void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode);

void bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime);

#endif //ALGORITHMS_H
