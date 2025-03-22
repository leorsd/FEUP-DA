#ifndef BATCH_H
#define BATCH_H

#include "graph.h"
#include "algorithms.h"
#include "displayBatch.h"
#include <sstream>
#include <fstream>
#include <string>

bool startsWith(const std::string& line, const std::string& prefix);

Vertex* getNode(const std::string& line, Graph* graph);

bool avoidNodes(const std::string& line, Graph* graph);

bool avoidSegments(const std::string& line, Graph* graph);

int getInt(const std::string& line);

bool includeNode(const std::string& line, Graph* graph, Vertex* &node);

void runBatchMode(Graph* graph);

#endif //BATCH_H
