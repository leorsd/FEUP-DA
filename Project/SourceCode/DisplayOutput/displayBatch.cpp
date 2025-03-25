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

void displayBatchDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result){
    std::ofstream outFile;
    if ( openFile(outFile) != 0) return;

    std::ostringstream oss;
    oss << "Source:" << source << std::endl;
    oss << "Destination:" << dest << std::endl;

    if (result == VALID_ROUTE){

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
        oss << "Message:";
        switch (result){
            case WALKING_TIME_EXCEEDED:
                oss << "No possible path with the max. walking time provided." << std::endl;
                outFile << oss.str();
                outFile.close();
                return;
            case INVALID_ROUTE:
                oss << "No possible path with the restrictions provided." << std::endl;
                break;
            case NO_PARKING_AVAILABLE:
                oss << "No parking nodes available, impossible to find the desired path." << std::endl;
                break;
            default:
                break;
        }
    }
    outFile << oss.str();
    outFile.close();

    std::cout << "\nOutput file successfully created!" << std::endl;
}

void displayBatchAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2){
    std::ofstream outFile("../Data/output.txt", std::ios::app); // Abre em modo append para não apagar o que foi escrito pelo display do 3º algoritmo
    if (!outFile) {
        std::cerr << "Error opening output.txt file." << std::endl;
        return;
    }
    std::ostringstream oss;
    oss << "\n--- Approximate Route ---\n\n";
    oss << "Source:" << source << std::endl;
    oss << "Destination:" << dest << std::endl;

    // Primeira alternativa
    oss << "DrivingRoute1:" << drivingRoute1->front();
    for (auto it = std::next(drivingRoute1->begin()); it != drivingRoute1->end(); ++it) {
        oss << "," << *it;
    }
    oss << "(" << drivingTime1 << ")" << std::endl;
    oss << "ParkingNode1:" << walkingRoute1->front() << std::endl;
    oss << "WalkingRoute1:" << walkingRoute1->front();
    for (auto it = std::next(walkingRoute1->begin()); it != walkingRoute1->end(); ++it) {
        oss << "," << *it;
    }
    oss << "(" << walkingTime1 << ")" << std::endl;
    oss << "TotalTime1:" << (walkingTime1 + drivingTime1) << std::endl;

    // Segunda alternativa
    oss << "DrivingRoute2:" << drivingRoute2->front();
    for (auto it = std::next(drivingRoute2->begin()); it != drivingRoute2->end(); ++it) {
        oss << "," << *it;
    }
    oss << "(" << drivingTime2 << ")" << std::endl;
    oss << "ParkingNode2:" << walkingRoute2->front() << std::endl;
    oss << "WalkingRoute2:" << walkingRoute2->front();
    for (auto it = std::next(walkingRoute2->begin()); it != walkingRoute2->end(); ++it) {
        oss << "," << *it;
    }
    oss << "(" << walkingTime2 << ")" << std::endl;
    oss << "TotalTime2:" << (walkingTime2 + drivingTime2) << std::endl;

    outFile << oss.str();
    outFile.close();

    std::cout << "\nOutput file successfully created!" << std::endl;
}