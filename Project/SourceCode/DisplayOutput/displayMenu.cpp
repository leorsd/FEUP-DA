#include "displayMenu.h"

void displayMenuIndependentRoute(int source, int dest, std::list<int>* bestRoute, int bestRouteTime, std::list<int>* alternativeRoute, int alternativeRouteTime){
    std::stringstream ss;

    ss << "\n\n--- Result of Search ---" << std::endl;
    ss << "Source: " << source << std::endl;
    ss << "Destination: " << dest << std::endl;
    ss << std::endl;

    if (bestRoute->size() <= 1){
        ss << "There is no path between " << source << " and " << dest << "." << std::endl;
    } else {
        ss << "The best route is: " << bestRoute->front();
        for (auto it = std::next(bestRoute->begin()); it != bestRoute->end(); ++it) {
            ss << " -> " << *it;
        }
        ss << std::endl;
        ss << "Estimated time: " << bestRouteTime << " minutes." << std::endl;
    }
    ss << std::endl;

    if (alternativeRoute->size() <= 1){
        ss << "There is no alternative path available." << std::endl;
    } else {
        ss << "An alternative route is: " << alternativeRoute->front();
        for (auto it = std::next(alternativeRoute->begin()); it != alternativeRoute->end(); ++it) {
            ss << " -> " << *it;
        }
        ss << std::endl;
        ss << "Estimated time: " << alternativeRouteTime << " minutes." << std::endl;
    }

    std:: cout << ss.str();
}