#include "menu.h"

/**
 * @file menu.cpp
 * @brief This file contains the implementation of the functions declared in menu.h
 */

Vertex* askSourceId(Graph* graph){
    std::string line;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What is the source node id?\n";

    while(true){
        std::cout << "Your choice: ";
        std::getline(std::cin, line);

        if (line.empty()){
            std::cout << "Invalid input! You need to include the source node.\n";
        }
        else{
            try{
                int destID = std::stoi(line);
                Vertex* sourceNode = graph->findVertex(destID);
                if (sourceNode == nullptr){
                    std::cout << "Invalid input! Source node not found in graph, please try again.\n";
                }else{
                    return sourceNode;
                }
            } catch (...){
                std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
            }
        }
    }
}

Vertex* askDestId(Graph* graph, Vertex* sourceNode){
    std::string line;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What is the destination node id?\n";

    while(true){
        std::cout << "Your choice: ";
        std::getline(std::cin, line);

        if (line.empty()){
            std::cout << "Invalid input! You need to include the destination node.\n";
        }
        else{
            try{
                int destID = std::stoi(line);
                Vertex* destNode = graph->findVertex(destID);
                if (destNode == sourceNode){
                    std::cout << "Source node and destination node must be different, please choose other destination node.\n";
                }else if (destNode == nullptr){
                    std::cout << "Invalid input! Destination node not found in graph, please try again.\n";
                }else{
                    return destNode;
                }
            } catch (...){
                std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
            }
        }
    }
}

void askAvoidNodes(Graph* graph, Vertex* sourceNode, Vertex* destNode){
    std::string line;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What are the avoid nodes? Use this method for input: id id id id etc...\n";
    std::cout << "Your choice: ";

    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::string word;

    while (ss >> word) {
        try {
            int id = std::stoi(word);
            Vertex *vertex = graph->findVertex(id);
            if (vertex == sourceNode){
                std::cout << "Warning: Cannot avoid the source node, it will not be ignored.\n";
            }else if (vertex == destNode){
                std::cout << "Warning: Cannot avoid the destination node, it will not be ignored.\n";
            }else if (vertex == nullptr){
                std::cout << "Warning: Not found any node with this id:'" << id << "', it will be ignored.\n";
            }else{
                vertex->setAvoid(true);
            }
        } catch (...) {
            std::cout << "Warning: '" << word << "' is not a valid number and will be ignored.\n";
        }
    }
}

void askAvoidEdges(Graph* graph){
    std::string line;
    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What are the avoid edges? Use this method for input: id-id id-id id-id etc...\n";
    std::cout << "Your choice: ";

    std::getline(std::cin, line);
    std::stringstream ss(line);

    std::string word;

    while (ss >> word) {
        int pos = word.find('-');
        if (pos == std::string::npos) {
            std::cout << "Warning: '" << word << "' is not in the correct format and will be ignored.\n";
            continue;
        }

        try {
            int source = std::stoi(word.substr(0, pos));
            int dest = std::stoi(word.substr(pos + 1));

            Vertex* sourceVertex = graph->findVertex(source);
            Vertex* destVertex = graph->findVertex(dest);

            if (sourceVertex == nullptr || destVertex == nullptr){
                std::cout << "Warning: Not found any node with one of this ids:'" << word << "', it will be ignored.\n";
                continue;
            }
            bool edgeFound = false;
            for (Edge* edge : sourceVertex->getAdj()){
                if (edge->getDest()->getCode() == destVertex->getCode()){
                    edge->setAvoid(true);
                    edge->getReverse()->setAvoid(true);
                    edgeFound = true;
                }
            }
            if (!edgeFound){
                std::cout << "Warning: No edge found between nodes '" << source << "' and '" << dest << "', it will be ignored.\n";
            }
        } catch (...) {
            std::cout << "Warning: '" << word << "' contains invalid numbers and will be ignored, please try again.\n";
        }
    }
}

Vertex* askIncludeNode(Graph* graph, Vertex* sourceNode, Vertex* destNode){
    Vertex* includeNode = nullptr;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "Do you want to include some node in your path? If yes, type the id, if no, press enter.\n";

    while (true){
        std::cout << "Your choice: ";

        std::string line;

        std::getline(std::cin, line);
        if (line == ""){ break;}
        try{
            int id = std::stoi(line);
            includeNode = graph->findVertex(id);
            if (includeNode == sourceNode || includeNode == destNode){
                std::cout << "Warning: Including the source node or destination node is trivial, please try again.\n";
            }else if (includeNode == nullptr){
                std::cout << "Warning: No node found with this id:'" << id << "', it will be ignored, please try again.\n";
            }else{
                break;
            }
        }
        catch (...) {
              std::cout << "Warning: '" << line << "' contains invalid numbers and will be ignored, please try again.\n";
        }
    }
    return includeNode;
}

int askMaxWalkTime(Graph* graph){
    int maxWalkTime;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What is the max walk time?\n";

    std::string  line;

    while(true){
        std::cout << "Your choice: ";
        std::getline(std::cin, line);

        if (line.empty()){
            std::cout << "Invalid input! You need to include the max walk time.\n";
        }
        else{
            try{
                int walkTime = std::stoi(line);
                return walkTime;
            } catch (...){
                std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
            }
        }
    }
}

bool askForAproximateSolution(){
    std::cout << "\nDo you want a aproximate solution? 1 for yes, 0 for no\n";
    int choice;
    while(true){

        std::cout << "Your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) {
            std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else if (choice != 1 && choice != 0){
            std::cout << "Invalid input! Please enter 0 or 1.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else{
            break;
        }
    }
    return (choice == 1);
}

void runMenuMode(Graph* graph){
    int alg;
    std::string line;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "1. Independent Route Planning\n";
    std::cout << "2. Restricted Route Planning\n";
    std::cout << "3. Best route for driving and walking\n";
    std::cout << "4. Exit\n";

    while (true) {
        std::cout << "Enter Choice: ";
        getline(std::cin, line);

        if (line.empty()) {
            std::cout << "Invalid input! You need to choose an algorithm or exit, please try again.\n";
        }else{
            try{
                alg = std::stoi(line);
                if (alg < 1 || alg > 4){
                    std::cout << "Invalid choice, please try again.\n";
                }else{
                    break;
                }
            }catch (...){
                std::cout << "You entered a non-integer value, please try again.\n";
            }
        }
    }

    // Initializing variables that will be passed to the algorithms to store the results

    Vertex* sourceNode,*destNode, *includeNode;
    int maxWalkTime = 0;
    std::list<int> bestRoute = {};
    std::list<int> alternativeRoute = {};
    int bestRouteTime = 0;
    int alternativeRouteTime = 0;
    std::list<int> drivingRoute = {};
    std::list<int> walkingRoute = {};
    int walkingRouteTime = 0;
    int drivingRouteTime = 0;

    RouteResult result;


    // Depending on the algorithm chosen, the corresponding questions are made, the algorithm is executed and the results are displayed
    switch (alg) {
        case 1:
            sourceNode = askSourceId(graph);
            destNode = askDestId(graph, sourceNode);

            independentRoute(graph, sourceNode, destNode, &bestRoute, &bestRouteTime, &alternativeRoute, &alternativeRouteTime);

            displayMenuIndependentRoute(sourceNode->getId(), destNode->getId(), &bestRoute, bestRouteTime, &alternativeRoute, alternativeRouteTime);

            break;
        case 2:
            sourceNode = askSourceId(graph);
            destNode = askDestId(graph, sourceNode);

            askAvoidNodes(graph, sourceNode, destNode);
            askAvoidEdges(graph);
            includeNode = askIncludeNode(graph, sourceNode, destNode);

            restrictedRoute(graph, sourceNode, destNode, includeNode, &bestRoute, &bestRouteTime);

            displayMenuRestrictedRoute(sourceNode->getId(), destNode->getId(), &bestRoute, bestRouteTime);

            break;
        case 3:

            sourceNode = askSourceId(graph);
            destNode = askDestId(graph, sourceNode);

            askAvoidNodes(graph, sourceNode, destNode);
            askAvoidEdges(graph);
            maxWalkTime = askMaxWalkTime(graph);

            result = bestRouteDrivingWalking(graph, sourceNode, destNode, maxWalkTime, &bestRoute, &bestRouteTime, &alternativeRoute, &alternativeRouteTime);
            displayMenuDrivingWalkingRoute(sourceNode->getId(), destNode->getId(), &bestRoute, bestRouteTime, &alternativeRoute, alternativeRouteTime, result);

            // If the result of the driving-walking algorithm is WALKING_TIME_EXCEEDED, the aroximate solution is possible and the user is asked if he wants it
            if (result == WALKING_TIME_EXCEEDED){
                if (askForAproximateSolution()){
                    aproximateSolution(graph, sourceNode, destNode,&bestRoute, &bestRouteTime, &alternativeRoute, &alternativeRouteTime, &drivingRoute, &drivingRouteTime, &walkingRoute, &walkingRouteTime );
                    displayMenuAproximateRoute(sourceNode->getId(), destNode->getId(), &bestRoute, bestRouteTime, &alternativeRoute, alternativeRouteTime, &drivingRoute, drivingRouteTime, &walkingRoute, walkingRouteTime);
                }
            }
            break;
        default:
            break;
    }
}