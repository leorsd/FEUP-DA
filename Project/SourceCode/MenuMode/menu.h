#ifndef MENU_H
#define MENU_H

#include "graph.h"
#include "algorithms.h"
#include "displayMenu.h"
#include <sstream>

Vertex* askSourceId(Graph* graph);

Vertex* askDestId(Graph* graph, Vertex* sourceNode);

void askAvoidNodes(Graph* graph, Vertex* sourceNode, Vertex* destNode);

void askAvoidEdges(Graph* graph);

Vertex* askIncludeNode(Graph* graph, Vertex* sourceNode, Vertex* destNode);

int askMaxWalkTime(Graph* graph);

void runMenuMode(Graph* graph);

#endif //MENU_H
