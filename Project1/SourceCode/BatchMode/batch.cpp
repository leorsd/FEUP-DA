#include "batch.h"

/**
 * @file batch.cpp
 * @brief This file contains the implementation of the batch mode functions defined in batch.h
 */

bool startsWith(const std::string& line, const std::string& prefix) {
    return line.substr(0, prefix.length()) == prefix;
}

Vertex* getNode(const std::string& line, Graph* graph) {
	Vertex* node = nullptr;
	try{
		int id=std::stoi(line);
		node=graph->findVertex(id);
		if(node==nullptr){
			std::cout<<"ERROR: Vertex with id "<<id<<" not found in graph."<<std::endl;
			return nullptr;
		}else{
			return node;
		}
	}catch(...){
		std::cout<<"ERROR: Invalid input! Incorrect syntax in source or destination line - "<<line<<std::endl;
		return nullptr;
	}
}

bool avoidNodes(const std::string& line, Graph* graph, Vertex* source, Vertex* destination) {
  	std::istringstream iss(line);
    std::string word;
    while (std::getline(iss, word, ',')){
		try{
			int id=std::stoi(word);
			Vertex* node=graph->findVertex(id);
			if(node==nullptr){
				std::cout<<"ERROR: Vertex with id "<<id<<" not found in graph."<<std::endl;
				return false;
			}else if( node==source || node==destination){
                std::cout<<"ERROR: Cannot avoid the source or the destination node."<<std::endl;
                return false;
			}else{
                node->setAvoid(true);
			}
		}catch(...){
			std::cout<<"ERROR: Invalid input! Incorrect syntax in avoid nodes line."<<line<<std::endl;
			return false;
		}
    }
    return true;
}

bool avoidSegments(const std::string& line, Graph* graph) {
	std::istringstream iss(line);
	std::string word;

	while (std::getline(iss, word, ')')){
		if (word.front() == ',') word.erase(0, 1);
		if (word.front() != '(') {
	  		std::cout<<"ERROR: Invalid input! Incorrect syntax in avoid segments line."<<std::endl;
	        return false;
		}
		word.erase(0, 1);

		std::stringstream ss(word);
		std::string id1, id2;

		if (!std::getline(ss, id1, ',') || !std::getline(ss, id2, ',')) {
			std::cout<<"ERROR: Invalid input! Incorrect syntax in avoid segments line."<<std::endl;
            return false;
		}

		try {
	  		int node1 = std::stoi(id1);
	  		int node2 = std::stoi(id2);
	  		Vertex* source = graph->findVertex(node1);
	        if(source==nullptr){
	          std::cout<<"ERROR: Vertex with id "<<id1<<" not found in graph."<<std::endl;
	          return false;
	        }
	        Vertex* dest = graph->findVertex(node2);
	        if(dest==nullptr){
	          std::cout<<"ERROR: Vertex with id "<<id2<<" not found in graph."<<std::endl;
	          return false;
	        }

	        bool found=false;
	        for(Edge* edge: source->getAdj()){
		        if(edge->getDest() == dest){
	        		edge->setAvoid(true);
		            edge->getReverse()->setAvoid(true);
	        		found = true;
		        }
	        }
	        if(!found){
	          	std::cout<<"ERROR: Edge with source id "<<id1<<" and dest id "<<id2<<" not found in graph."<<std::endl;
                return false;
	        }
		} catch (...) {
			std::cout<<"ERROR: Invalid input! Incorrect syntax in avoid segments line."<<std::endl;
            return false;
		}
	}
	return true;
}

int getInt(const std::string& line) {
	try{
         return std::stoi(line);
	} catch(...) {
        std::cout<<"ERROR: Invalid input! Incorrect syntax in max walk time line."<<std::endl;
        return -1;
    }
}

bool includeNode(const std::string& line, Graph* graph, Vertex* &node) {
  	if (line.empty()){
		return true;
    }
	try{
		int id=std::stoi(line);
		node=graph->findVertex(id);
		if(node==nullptr){
			std::cout<<"ERROR: Vertex with id "<<id<<" not found in graph."<<std::endl;
			return false;
		}
	}catch(...){
		std::cout<<"ERROR: Invalid input! Incorrect syntax in include node line."<<line<<std::endl;
		return false;
	}
    return true;
}

void runBatchMode(Graph* graph){
	std::ifstream input_file("../Data/input.txt");

    if (!input_file.is_open()) {
        std::cerr << "ERROR: Was not able to open input.txt.\n";
        return;
    }

    std::string line;

    std::string mode = "";
    Vertex* sourceNode = nullptr;
    Vertex* destNode = nullptr;
    Vertex* incNode = nullptr;
    int maxWalkTime;

	std::getline(input_file, line);
	if (startsWith(line, "Mode:")) {
		mode = line.substr(5);
	}else{
		std::cout<<"ERROR: Invalid input! 1st line needs to contain the mode with the defined syntax."<<std::endl;
        return;
	}

	if (mode=="driving") {

		std::getline(input_file, line);
		if (startsWith(line, "Source:")) {
			sourceNode = getNode(line.substr(7), graph);
			if(sourceNode==nullptr){
				return;
			}
		}else {
			std::cout<<"ERROR: Invalid input! 2nd line needs to contain the source node with the defined syntax."<<std::endl;
            return;
		}

        std::getline(input_file, line);
		if (startsWith(line, "Destination:")) {
			destNode = getNode(line.substr(12), graph);
			if(destNode==nullptr){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 3th line needs to contain the destination node with the defined syntax."<<std::endl;
			return;
		}

        std::getline(input_file, line);

        if (input_file.eof()){
        	std::list<int> bestRoute = {};
        	std::list<int> alternativeRoute = {};
        	int bestRouteTime;
        	int alternativeRouteTime;

        	independentRoute(graph, sourceNode, destNode, &bestRoute, &bestRouteTime, &alternativeRoute, &alternativeRouteTime);

        	displayBatchIndependentRoute(sourceNode->getId(), destNode->getId(), &bestRoute, bestRouteTime, &alternativeRoute, alternativeRouteTime);
            return;
        }else{
        	if (startsWith(line, "AvoidNodes:")) {
        		if(!avoidNodes(line.substr(11),graph, sourceNode, destNode)){
        			return;
        		}
        	}else{
        		std::cout<<"ERROR: Invalid input! 4th line needs to contain the avoid nodes with the defined syntax."<<std::endl;
        		return;
        	}
        }

        std::getline(input_file, line);
		if (startsWith(line, "AvoidSegments:")) {
			if(!avoidSegments(line.substr(14),graph)){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 5th line needs to contain the avoid segments with the defined syntax."<<std::endl;
			return;
		}

        std::getline(input_file, line);
		if (startsWith(line, "IncludeNode:")) {
			if(!includeNode(line.substr(12),graph,incNode)){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 6th line needs to contain the include node with the defined syntax."<<std::endl;
			return;
		}

        std::getline(input_file, line);
        if (!input_file.eof()){
        	std::cout<<"ERROR: Invalid input! There should not be more than 6 lines."<<std::endl;
        	return;
        }

		std::list<int> restrictedRouteList = {};
		int restrictedRouteTime;

		restrictedRoute(graph, sourceNode, destNode, incNode, &restrictedRouteList, &restrictedRouteTime);

		displayBatchRestrictedRoute(sourceNode->getId(), destNode->getId(), &restrictedRouteList, restrictedRouteTime);
        return;

	}else if (mode=="driving-walking"){

		std::getline(input_file, line);
		if (startsWith(line, "Source:")) {
			sourceNode = getNode(line.substr(7), graph);
			if(sourceNode==nullptr){
				return;
			}
		}else {
			std::cout<<"ERROR: Invalid input! 2nd line needs to contain the source node with the defined syntax."<<std::endl;
			return;
		}

		std::getline(input_file, line);
		if (startsWith(line, "Destination:")) {
			destNode = getNode(line.substr(12), graph);
			if(destNode==nullptr){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 3th line needs to contain the destination node with the defined syntax."<<std::endl;
			return;
		}

        std::getline(input_file, line);
		if (startsWith(line, "MaxWalkTime:")) {
			maxWalkTime = getInt(line.substr(12));
			if(maxWalkTime == -1) {
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 4th line needs to contain the maximum walking time with the defined syntax."<<std::endl;
			return;
		}

		std::getline(input_file, line);
		if (startsWith(line, "AvoidNodes:")) {
			if(!avoidNodes(line.substr(11),graph, sourceNode, destNode)){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 5th line needs to contain the avoid nodes with the defined syntax."<<std::endl;
			return;
		}

		std::getline(input_file, line);
		if (startsWith(line, "AvoidSegments:")) {
			if(!avoidSegments(line.substr(14),graph)){
				return;
			}
		}else{
			std::cout<<"ERROR: Invalid input! 6th line needs to contain the avoid segments with the defined syntax."<<std::endl;
			return;
		}

        std::getline(input_file, line);
        if (!input_file.eof()){
        	std::cout<<"ERROR: Invalid input! There should not be more than 6 lines."<<std::endl;
        	return;
        }

		std::list<int> drivingRoute = {};
		std::list<int> walkingRoute = {};
		int drivingRouteTime;
		int walkingRouteTime;

		RouteResult result = bestRouteDrivingWalking(graph, sourceNode, destNode, maxWalkTime, &drivingRoute, &drivingRouteTime, &walkingRoute, &walkingRouteTime);
		displayBatchDrivingWalkingRoute(sourceNode->getId(), destNode->getId(), &drivingRoute, drivingRouteTime, &walkingRoute, walkingRouteTime, result);
        if ( result == WALKING_TIME_EXCEEDED){
            std::list<int> drivingRoute2 = {};
            std::list<int> walkingRoute2 = {};
            int drivingRouteTime2;
            int walkingRouteTime2;
        	aproximateSolution(graph, sourceNode, destNode, &drivingRoute, &drivingRouteTime, &walkingRoute, &walkingRouteTime, &drivingRoute2, &drivingRouteTime2, &walkingRoute2, &walkingRouteTime2);
			displayBatchAproximateRoute(sourceNode->getId(), destNode->getId(), &drivingRoute, drivingRouteTime, &walkingRoute, walkingRouteTime, &drivingRoute2, drivingRouteTime2, &walkingRoute2, walkingRouteTime2);
        }
        return;
	}else{
        std::cout<<"ERROR: Invalid input! Unknown mode value."<<std::endl;
	}
    return;
}