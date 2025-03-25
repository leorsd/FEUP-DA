#ifndef DISPLAYBATCH_H
#define DISPLAYBATCH_H

#include <iostream>
#include <list>
#include <ostream>
#include <sstream>
#include <fstream>
#include "algorithms.h"


int openFile(std::ofstream& outputFile);

void displayBatchIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

void displayBatchRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

void displayBatchDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result);

void displayBatchAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2);

#endif //DISPLAYBATCH_H
