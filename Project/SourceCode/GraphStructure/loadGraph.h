#ifndef LOADGRAPH_H
#define LOADGRAPH_H

#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

void loadGraph(const std::string& vertex_filename, const std::string& edge_filename, Graph* g);

#endif
