#ifndef DISPLAYBATCH_H
#define DISPLAYBATCH_H

#include <iostream>
#include <list>
#include <ostream>
#include <sstream>
#include <fstream>


int openFile(std::ofstream& outputFile);

void displayBatchIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

void displayBatchRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime);

void displayBatchDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, std::string message);

#endif //DISPLAYBATCH_H
