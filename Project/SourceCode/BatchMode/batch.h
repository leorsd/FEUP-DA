#ifndef BATCHREADER_H
#define BATCHREADER_H

#include "graph.h"
#include "algorithms.h"
#include <sstream>
#include <fstream>

bool startsWith(const std::string& line, const std::string& prefix);

Vertex* getNode(const std::string& line, Graph* graph);

bool avoidNodes(const std::string& line, Graph* graph);

bool avoidSegments(const std::string& line, Graph* graph);

int getInt(const std::string& line);

bool includeNode(const std::string& line, Graph* graph, Vertex* node);

void runBatchMode(Graph* graph);

#endif //BATCHREADER_H
