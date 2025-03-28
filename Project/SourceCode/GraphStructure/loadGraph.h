#ifndef LOADGRAPH_H
#define LOADGRAPH_H

#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

/**
 * @brief Loads the graph from CSV files.
 * 
 * @details The function reads the vertex and edge data from the specified CSV files and populates the graph structure. It handles errors related to file reading and data parsing.
 * 
 * @param vertex_filename The name of the vertex CSV file.
 * @param edge_filename The name of the edge CSV file.
 * @param g Pointer to the graph structure to be populated.
 */
void loadGraph(const std::string& vertex_filename, const std::string& edge_filename, Graph* g);

#endif
