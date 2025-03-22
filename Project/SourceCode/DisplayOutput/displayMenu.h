#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <iostream>
#include <sstream>
#include <list>

void displayMenuIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

void displayMenuRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

void displayMenuDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, std::string message);

#endif //DISPLAYMENU_H
