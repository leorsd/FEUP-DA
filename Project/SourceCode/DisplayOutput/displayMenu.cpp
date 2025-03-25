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

void displayMenuDrivingWalkingRoute(int source, int dest, std::list<int>* drivingRoute, int drivingTime, std::list<int>* walkingRoute, int walkingTime, RouteResult result){
    std::stringstream ss;

    ss << "\n\n--- Result of Search ---" << std::endl;
    ss << "Source: " << source << std::endl;
    ss << "Destination: " << dest << std::endl;
    ss << std::endl;

    switch (result){
        case WALKING_TIME_EXCEEDED:
            ss << "No possible path with the maximum walk time provided." << std::endl;
            std::cout << ss.str();
            return;
        case INVALID_ROUTE:
            ss << "No possible path with the restrictions provided." << std::endl;
            std::cout << ss.str();
            return;
        case NO_PARKING_AVAILABLE:
            ss << "No parking nodes available, impossible to find the desired path." << std::endl;
            std::cout << ss.str();
            return;
        default:
            break;
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

void displayMenuAproximateRoute(int source, int dest, std::list<int>* drivingRoute1, int drivingTime1, std::list<int>* walkingRoute1, int walkingTime1, std::list<int>* drivingRoute2, int drivingTime2, std::list<int>* walkingRoute2, int walkingTime2){
    std::stringstream ss;

    ss << "\n\n--- Result of Search ---" << std::endl;
    ss << "Source: " << source << std::endl;
    ss << "Destination: " << dest << std::endl;
    ss << std::endl;
    ss << "The max walk time for the aproximate solutions is "<< walkingTime2 << " minutes." << std::endl;
    ss << std::endl;
    ss << "The best aproximate solutions is: \n";
    ss << "Driving: " << drivingRoute1->front();
    for (auto it = std::next(drivingRoute1->begin()); it != drivingRoute1->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;
    ss << "Parking at: " << walkingRoute1->front()<<std::endl;

    ss << "Walking: " << walkingRoute1->front();
    for (auto it = std::next(walkingRoute1->begin()); it != walkingRoute1->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;

    ss << "Estimated driving time of " << drivingTime1 << " minutes and estimated walking time of "<< walkingTime1<<", ending with a total time of " <<(walkingTime1 + drivingTime1) << " minutes." << std::endl;

    ss << "The second best aproximate solutions is: \n";
    ss << "Driving: " << drivingRoute2->front();
    for (auto it = std::next(drivingRoute2->begin()); it != drivingRoute2->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;
    ss << "Parking at: " << walkingRoute2->front()<<std::endl;

    ss << "Walking: " << walkingRoute2->front();
    for (auto it = std::next(walkingRoute2->begin()); it != walkingRoute2->end(); ++it) {
        ss << " -> " << *it;
    }
    ss << std::endl;

    ss << "Estimated driving time of " << drivingTime2 << " minutes and estimated walking time of "<< walkingTime2<<", ending with a total time of " <<(walkingTime2 + drivingTime2) << " minutes." << std::endl;
    std::cout << ss.str();
}