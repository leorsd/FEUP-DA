#ifndef MENU_H
#define MENU_H

#include "graph.h"
#include "algorithms.h"
#include "displayMenu.h"
#include <sstream>

Vertex* askSourceId(Graph* graph);

Vertex* askDestId(Graph* graph);

void askAvoidNodes(Graph* graph);

void askAvoidEdges(Graph* graph);

Vertex* askIncludeNode(Graph* graph);

int askMaxWalkTime(Graph* graph);

void runMenuMode(Graph* graph);

#endif //MENU_H
