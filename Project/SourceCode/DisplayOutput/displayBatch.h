#ifndef DISPLAYBATCH_H
#define DISPLAYBATCH_H

#include <iostream>
#include <list>
#include <ostream>
#include <sstream>
#include <fstream>
#include "algorithms.h"

/**
 * @file This file contains the function declarations for displaying the output in batch mode.
 * The functions are used to display the results of the algorithms in a predefined format.
 * The functions are implemented in the displayBatch.cpp file.
 */

/**
 * @brief Function that opens the output file for writing.
 * 
 * @details The function attempts to open the output file for writing. If the file cannot be opened, it will display an error message and return -1. If the file is opened successfully, it returns 0.
 * 
 * @param outputFile Reference to the ofstream object representing the output file.
 * @return int Returns 0 if the file is opened successfully, -1 otherwise.
 */
int openFile(std::ofstream& outputFile);

/**
 * @bried Displays the output for the independent route algorithm in batch mode.
 * 
 * @details The function displays the best route and its time, as well as an alternative route and its time. The display is done by writing to the output file, showing the source and destination nodes, the best route, and the alternative route in the predefined format. The function also handles the case where no alternative route is found.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param bestRoute Pointer to the list of nodes in the best route.
 * @param bestRouteTime The time taken for the best route.
 * @param alternativeRoute Pointer to the list of nodes in the alternative route.
 * @param alternativeRouteTime The time taken for the alternative route.
 * @return void
 */
void displayBatchIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

/**
 * @brief Displays the output for the restricted route algorithm in batch mode.
 * 
 * @details The function displays a restricted route and its time. The display is done by writing to the output file, showing the source and destination nodes and the restricted route in the predefined format. The function also handles the case where no restricted route is found.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param restrictedRoute Pointer to the list of nodes in the restricted route.
 * @param restrictedRouteTime The time taken for the restricted route.
 * @return void
 */
void displayBatchRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

/**
 * @brief Displays the output for the driving and walking route algorithm in batch mode.
 * 
 * @details The function displays the driving and walking routes, their times, and the total time. The display is done by writing to the output file, showing the source and destination nodes, the driving route, the walking route, and the total time in the predefined format. The function also handles the case where no route is found.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param drivingRoute Pointer to the list of nodes in the driving route.
 * @param drivingTime The time taken for the driving route.
 * @param walkingRoute Pointer to the list of nodes in the walking route.
 * @param walkingTime The time taken for the walking route.
 * @param result The result of the route calculation (success or failure). Used to know if the aproximate route is possible.
 * @return void
 */
void displayBatchDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result);

/**
 * @brief Displays the output for the approximate route algorithm in batch mode.
 * 
 * @details The function displays the driving and walking routes, their times, and the total time for each one of the two possible routes. The display is done by writing to the output file, showing the source and destination nodes, the driving route, the walking route, and the total time in the predefined format.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param drivingRoute1 Pointer to the list of nodes in the first driving route.
 * @param drivingTime1 The time taken for the first driving route.
 * @param walkingRoute1 Pointer to the list of nodes in the first walking route.
 * @param walkingTime1 The time taken for the first walking route.
 * @param drivingRoute2 Pointer to the list of nodes in the second driving route.
 * @param drivingTime2 The time taken for the second driving route.
 * @param walkingRoute2 Pointer to the list of nodes in the second walking route.
 * @param walkingTime2 The time taken for the second walking route.
 * @return void
 */
void displayBatchAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2);

#endif //DISPLAYBATCH_H
