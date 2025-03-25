#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <iostream>
#include <sstream>
#include <list>
#include "algorithms.h"

void displayMenuIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

void displayMenuRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

void displayMenuDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result);

void displayMenuAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2);

#endif //DISPLAYMENU_H
