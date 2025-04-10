#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <iostream>
#include <sstream>
#include <list>
#include "algorithms.h"

/**
 * @file displayMenu.h
 * @brief Function declarations for displaying the results in menu mode.
 * 
 * This file contains the function declarations for displaying the results of various algorithms in a user-friendly format. 
 * These functions are implemented in the displayMenu.cpp file.
 */

/**
 * @brief Displays the output for the independent route algorithm in the menu mode.ADJ_OFFSET_SINGLESHOT
 * 
 * @details The function displays the best route and its time, as well as an alternative route and its time. The display is done in a user-friendly format, showing the source and destination nodes, the best route, and the alternative route. The function also handles the case where no alternative route is found.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param bestRoute Pointer to the list of nodes in the best route.
 * @param bestRouteTime The time taken for the best route.
 * @param alternativeRoute Pointer to the list of nodes in the alternative route.
 * @param alternativeRouteTime The time taken for the alternative route.
 * @return void
 */
void displayMenuIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);


/**
 * @brief Displays the output for the restricted route algorithm in the menu mode.
 * 
 * @details The function displays a restricted route and its time. The display is done in a user-friendly format, showing the source and destination nodes and the restricted route. The function also handles the case where no restricted route is found.
 * 
 * @param source The source node id.
 * @param dest The destination node id.
 * @param restrictedRoute Pointer to the list of nodes in the restricted route.
 * @param restrictedRouteTime The time taken for the restricted route.
 * @return void
 */
void displayMenuRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

/**
 * @brief Displays the output for the driving and walking route algorithm in the menu mode.
 * 
 * @details The function displays the driving and walking routes, their times, and the total time. The display is done in a user-friendly format, showing the source and destination nodes, the driving route, the walking route, and the total time. The function also handles the case where no route is found.
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
void displayMenuDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result);


/**
 * @brief Displays the output for the approximate route algorithm in the menu mode.
 * 
 * @details The function displays the driving and walking routes, their times, and the total time for each one of the two possible routes. The display is done in a user-friendly format, showing the source and destination nodes, the driving route, the walking route, and the total time.
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
void displayMenuAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2);

#endif //DISPLAYMENU_H
