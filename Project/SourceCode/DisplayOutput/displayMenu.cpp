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

void displayMenuRestrictedRoute(int source, int dest, std::list<int>* restrictedRoute, int restrictedRouteTime){
    std::stringstream ss;

    ss << "\n\n--- Result of Search ---" << std::endl;
    ss << "Source: " << source << std::endl;
    ss << "Destination: " << dest << std::endl;
    ss << std::endl;

    if (restrictedRoute->front() != source || restrictedRoute->back() != dest){
        ss << "There is no path between " << source << " and " << dest << " with the provided restrictions." << std::endl;
    } else {
        ss << "The best route acording to the restrictions is: " << restrictedRoute->front();
        for (auto it = std::next(restrictedRoute->begin()); it != restrictedRoute->end(); ++it) {
            ss << " -> " << *it;
        }
        ss << std::endl;
        ss << "Estimated time: " << restrictedRouteTime << " minutes." << std::endl;
    }
    std:: cout << ss.str();
}

void displayMenuDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, std::string message){
    std::stringstream ss;

    ss << "\n\n--- Result of Search ---" << std::endl;
    ss << "Source: " << source << std::endl;
    ss << "Destination: " << dest << std::endl;
    ss << std::endl;

    if (message.size() > 0){
        ss << message;
        std::cout << ss.str();
        return;
    }

    ss << "The best route with the provided restrictions and characteristics of this algorithm is: \n";
    ss << "Driving: " << drivingRoute->front();
    for (auto it = std::next(drivingRoute->begin()); it != drivingRoute->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;
    ss << "Parking at: " << walkingRoute->front()<<std::endl;

    ss << "Walking: " << walkingRoute->front();
    for (auto it = std::next(walkingRoute->begin()); it != walkingRoute->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;

    ss << "Estimated driving time of " << drivingTime << " minutes and estimated walking time of "<< walkingTime<<", ending with a total time of " <<(walkingTime + drivingTime) << " minutes." << std::endl;
    std::cout << ss.str();
}