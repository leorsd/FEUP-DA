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