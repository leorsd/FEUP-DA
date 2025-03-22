#include "displayBatch.h"

int openFile(std::ofstream& outputFile){
  outputFile.open("../Data/output.txt");
  if (!outputFile){
    std::cout << "Error opening output.txt file." << std::endl;
    return 1;
  }
  return 0;
}

void displayBatchIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime){
    std::ofstream outFile;
    if ( openFile(outFile) != 0) return;

    std::ostringstream oss;
    oss << "Source:" << source << std::endl;
    oss << "Destination:" << dest << std::endl;

    if (bestRoute->size() <= 1){
    	oss << "BestDrivingRoute:none" << std::endl;
    }else{
      	oss << "BestDrivingRoute:" << bestRoute->front();
        for (auto it = std::next(bestRoute->begin()); it != bestRoute->end(); ++it) {
            oss << "," << *it;
        }
        oss << "(" << bestRouteTime << ")" << std::endl;
    }

    if (alternativeRoute->size() <= 1){
      	oss << "AlternativeDrivingRoute:none" << std::endl;
    }else{
      	oss << "AlternativeDrivingRoute:" << alternativeRoute->front();
        for (auto it = std::next(alternativeRoute->begin()); it != alternativeRoute->end(); ++it) {
            oss << "," << *it;
        }
        oss << "(" << alternativeRouteTime << ")" << std::endl;
    }
	outFile << oss.str();
    outFile.close();

    std::cout << "\nOutput file successfully created!" << std::endl;
}

void displayBatchRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime){
    std::ofstream outFile;
    if ( openFile(outFile) != 0) return;

    std::ostringstream oss;
    oss << "Source:" << source << std::endl;
    oss << "Destination:" << dest << std::endl;

    if (restrictedRoute->front() != source || restrictedRoute->back() != dest){
        oss << "RestrictedDrivingRoute:none" << std::endl;
    }else{
        oss << "RestrictedDrivingRoute:" << restrictedRoute->front();
        for (auto it = std::next(restrictedRoute->begin()); it != restrictedRoute->end(); ++it) {
            oss << "," << *it;
        }
        oss << "(" << restrictedRouteTime << ")" << std::endl;
    }
    outFile << oss.str();
    outFile.close();

    std::cout << "\nOutput file successfully created!" << std::endl;
}

void displayBatchDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, std::string message){
    std::ofstream outFile;
    if ( openFile(outFile) != 0) return;

    std::ostringstream oss;
    oss << "Source:" << source << std::endl;
    oss << "Destination:" << dest << std::endl;

    if (message.size() == 0){

        oss << "DrivingRoute:" << drivingRoute->front();
        for (auto it = std::next(drivingRoute->begin()); it != drivingRoute->end(); ++it) {
            oss << "," << *it;
        }
        oss << "(" << drivingTime << ")" << std::endl;

        oss << "ParkingNode:" << walkingRoute->front() << std::endl;

        oss << "WalkingRoute:" << walkingRoute->front();
        for (auto it = std::next(walkingRoute->begin()); it != walkingRoute->end(); ++it) {
            oss << "," << *it;
        }
        oss << "(" << walkingTime << ")" << std::endl;

        oss << "TotalTime:" <<(walkingTime+drivingTime) <<std::endl;
    }else{
        oss << "DrivingRoute:none\n";
        oss << "ParkingNode:none\n";
        oss << "WalkingRoute:none\n";
        oss << "TotalTime:\n";
        oss << message;
    }
    outFile << oss.str();
    outFile.close();

    std::cout << "\nOutput file successfully created!" << std::endl;
}