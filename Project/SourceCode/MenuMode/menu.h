#ifndef MENU_H
#define MENU_H

#include "graph.h"
#include "algorithms.h"
#include "displayMenu.h"
#include <sstream>

/**
 * @file menu.h
 * @brief Function declarations for the menu mode of the program.
 * 
 * The menu mode allows user interaction to gather parameters needed for running algorithms. 
 * The corresponding function implementations are in menu.cpp.
 */


/**
 * @brief Asks the user for the source node ID.
 * 
 * @details This function prompts the user to enter the source node ID. It validates the input and ensures the node exists in the graph. If the input is invalid or the node does not exist, the function will continue prompting until a valid source node ID is provided.
 * 
 * @param graph Pointer to the graph structure.
 * @return Vertex* Returns a pointer to the source node.
 */
Vertex* askSourceId(Graph* graph);


/**
 * @brief Asks the user for the destination node id.
 * 
 * @details The function prompts the user to enter the destination node id. It validates the input and ensures the node exists in the graph. If the input is invalid or the node does not exist, the function will continue prompting until a valid destination node id is provided.
 * 
 * @param graph Pointer to the graph structure.
 * @param sourceNode Pointer to the source node.
 * @return Vertex* Returns a pointer to the destination node.
 */
Vertex* askDestId(Graph* graph, Vertex* sourceNode);

/**
 * @brief Asks the user for nodes that should be avoided.
 * 
 * @details The function prompts the user to enter the node ids that should be avoided. It validates the input and ensures the nodes exist in the graph. If the input is invalid or the nodes do not exist, that input will be ignored.
 * 
 * @param graph Pointer to the graph structure.
 * @param sourceNode Pointer to the source node.
 * @param destNode Pointer to the destination node.
 * @return void
 */
void askAvoidNodes(Graph* graph, Vertex* sourceNode, Vertex* destNode);

/**
 * @brief Asks the user for edges that should be avoided.
 * 
 * @details The function prompts the user to enter the edges that should be avoided. It validates the input and ensures the edges exist in the graph. If the input is invalid or the edges do not exist, that input will be ignored.
 * 
 * @param graph Pointer to the graph structure.
 * @return void
 */
void askAvoidEdges(Graph* graph);

/**
 * @brief Asks the user for the node that needs to be included.
 * 
 * @details The function prompts the user to enter the node id that should be included. It validates the input and ensures the node exists in the graph. If the input is invalid or the nodes do not exist, that input will be ignored.
 * 
 * @param graph Pointer to the graph structure.
 * @param sourceNode Pointer to the source node.
 * @param destNode Pointer to the destination node.
 * @return Vertex* Returns a pointer to the included node.
 */
Vertex* askIncludeNode(Graph* graph, Vertex* sourceNode, Vertex* destNode);

/**
 * @brief Asks the user for the maximum walk time.
 * 
 * @details The function prompts the user to enter the maximum walk time. It validates the input and ensures the value is valid. If the input is invalid, the function will continue prompting until a valid maximum walk time is provided.
 * 
 * @param graph Pointer to the graph structure.
 * @return int Returns the maximum walk time.
 */
int askMaxWalkTime(Graph* graph);

/**
 * @brief Runs the menu mode of the program.    
 * 
 * @details The function controls the menu mode of the program. It displays the menu options and prompts the user to enter their choice. Based on the user's choice, it will call the appropriate function to perform the selected algorithm. After the execution of the algorithm, it will call the function to display the results.
 * 
 * @param graph Pointer to the graph structure.
 * @return void
 */
void runMenuMode(Graph* graph);

#endif //MENU_H
