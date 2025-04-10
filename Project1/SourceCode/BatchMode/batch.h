#ifndef BATCH_H
#define BATCH_H

#include "graph.h"
#include "algorithms.h"
#include "displayBatch.h"
#include <sstream>
#include <fstream>
#include <string>

/**
 * @file batch.h
 * @brief Function declarations for the batch mode of the program.
 * 
 * This file contains the function declarations for the batch mode, which is used to read input from a file and process it to call the desired algorithms on the graph. 
 * These functions are implemented in the batch.cpp file.
 */

/**
 * @brief Function to check if a string starts with a given prefix.
 * @param line The string to check.
 * @param prefix The prefix to check for.
 * @return True if the string starts with the prefix, false otherwise.
 */
bool startsWith(const std::string& line, const std::string& prefix);

/**
 * @brief Function to find a node in the graph based on a given input line.
 * 
 * @details This function parses the input line to extract the node id and then searches for that node in the graph. If the node is found, it returns a pointer to the node. If not, it prints an error message and returns nullptr.
 * 
 * @param line The input line containing the node id.
 * @param graph The graph in which to search for the node.
 * @return A pointer to the found node, or nullptr if not found.
 */
Vertex* getNode(const std::string& line, Graph* graph);

/**
 * @brief Function to avoid certain nodes in the graph based on a given input line.
 * 
 * @details This function parses the input line to extract node ids and marks them as avoided in the graph. It also checks if the source or destination nodes are included in the list of nodes to avoid.
 * 
 * @param line The input line containing the node ids to avoid.
 * @param graph The graph in which to mark nodes as avoided.
 * @param source The source node.
 * @param destination The destination node.
 * @return True if the operation was successful, false otherwise.
 */
bool avoidNodes(const std::string& line, Graph* graph, Vertex* sourceNode, Vertex* destNode);


/**
 * @brief Function to avoid certain segments in the graph based on a given input line.
 * 
 * @details This function parses the input line to extract segments to avoid and marks them as avoided in the graph.
 * 
 * @param line The input line containing the segments to avoid.
 * @param graph The graph in which to mark segments as avoided.
 * @return True if the operation was successful, false otherwise.
 */
bool avoidSegments(const std::string& line, Graph* graph);


/**
 * @brief Function to convert a string to an integer.
 * 
 * @details This function attempts to convert the input string to an integer. If the conversion fails, it prints an error message and returns -1.
 * 
 * @param line The input line containing the integer value.
 * @return The converted integer value, or -1 if the conversion failed.
 */
int getInt(const std::string& line);

/**
 * @brief Function to find the node that needs to be included based on a given input line.
 * 
 * @details This function parses the input line to extract the node id and then searches for that node in the graph. If the node is found, it returns a pointer to the node. If not, it prints an error message and returns false.
 * 
 * @param line The input line containing the node id.
 * @param graph The graph in which to search for the node.
 * @param node A reference to a pointer that will be set to the found node.
 * @return True if the node was found, false otherwise.
 */
bool includeNode(const std::string& line, Graph* graph, Vertex* &node);

/**
 * @brief Function to run the batch mode of the program.
 * 
 * @details This function reads input from a file and processes it to call the desired algorithms on the graph. After the processing, it calls the apropriate functions to display the results. 
 * 
 * @param graph The graph on which to perform the operations.
 */
void runBatchMode(Graph* graph);

#endif //BATCH_H
