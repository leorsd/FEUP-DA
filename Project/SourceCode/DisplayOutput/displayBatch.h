#ifndef DISPLAYBATCH_H
#define DISPLAYBATCH_H

#include <iostream>
#include <list>
#include <ostream>
#include <sstream>
#include <fstream>


int openFile(std::ofstream& outputFile);

void displayBatchIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime);

#endif //DISPLAYBATCH_H
