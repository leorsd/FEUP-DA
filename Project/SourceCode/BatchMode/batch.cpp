#include "batch.h"

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
    std::cout<<"ERROR: Invalid input! Incorrect sintax in source or destination line."<<line<<std::endl;
    return nullptr;
  }
}

bool avoidNodes(const std::string& line, Graph* graph) {
  	std::istringstream iss(line);
    std::string word;
    while (std::getline(iss, word, ',')){
      try{
        int id=std::stoi(word);
        Vertex* node=graph->findVertex(id);
        if(node==nullptr){
          std::cout<<"ERROR: Vertex with id "<<id<<" not found in graph."<<std::endl;
          return false;
        }else{
          node->setAvoid(true);
        }
      }catch(...){
        std::cout<<"ERROR: Invalid input! Incorrect sintax in avoid nodes line."<<line<<std::endl;
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
	  		std::cout<<"ERROR: Invalid input! Incorrect sintax in avoid segments line."<<std::endl;
	        return false;
		}
		word.erase(0, 1);

		std::stringstream ss(word);
		std::string id1, id2;

		if (!std::getline(ss, id1, ',') || !std::getline(ss, id2, ',')) {
			std::cout<<"ERROR: Invalid input! Incorrect sintax in avoid segments line."<<std::endl;
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
			std::cout<<"ERROR: Invalid input! Incorrect sintax in avoid segments line."<<std::endl;
            return false;
		}
	}
	return true;
}

int getInt(const std::string& line) {
	try{
         return std::stoi(line);
	} catch(...) {
        std::cout<<"ERROR: Invalid input! Incorrect sintax in max walk time line."<<std::endl;
        return -1;
    }
}

bool includeNode(const std::string& line, Graph* graph, Vertex* node) {
	try{
		int id=std::stoi(line);
		node=graph->findVertex(id);
		if(node==nullptr){
			std::cout<<"ERROR: Vertex with id "<<id<<" not found in graph."<<std::endl;
			return false;
		}
	}catch(...){
		std::cout<<"ERROR: Invalid input! Incorrect sintax in include node line."<<line<<std::endl;
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

    bool modeProvided = false;
    bool sourceProvided = false;
    bool destProvided = false;
    bool incProvided = false;
    bool avoidNodesProvided = false;
    bool avoidSegmentsProvided = false;
    bool maxWalkTimeProvided = false;

    while (std::getline(input_file, line)) {
      	if (startsWith(line, "Mode:")) {
          	mode = line.substr(5);
          	if (mode!=("driving") && mode!=("driving-walking")) {
            	std::cout<<"ERROR: Invalid input! Incorrect sintax in mode line."<<std::endl;
            	return;
          	}
			modeProvided = true;
      	}
    	else if (startsWith(line, "Source:")) {
          	sourceNode = getNode(line.substr(7), graph);
          	if(sourceNode==nullptr){
            	return;
          	}
            sourceProvided = true;
      	}
      	else if (startsWith(line, "Destination:")) {
			destNode = getNode(line.substr(12), graph);
        	if(destNode==nullptr){
          		return;
        	}
            sourceProvided = true;
      	}
        else if (startsWith(line, "AvoidNodes:")) {
			if(!avoidNodes(line.substr(11),graph)){
                return;
			}
            avoidNodesProvided = true;
        }
        else if (startsWith(line, "AvoidSegments:")) {
			if(!avoidSegments(line.substr(14),graph)){
                return;
			}
            avoidSegmentsProvided = true;
        }
        else if (startsWith(line, "IncludeNode:")) {
			if(!includeNode(line.substr(12),graph,incNode)){
                return;
			}
            incProvided = true;
        }else if (startsWith(line, "MaxWalkTime:")) {
          	maxWalkTime = getInt(line.substr(12));
          	if(maxWalkTime == -1) {
                return;
          	}
            maxWalkTimeProvided = true;
        }else{
          	std::cout<<"ERROR: Invalid input! Line not known: "<<line<<std::endl;
          	return;
        }
    }
    input_file.close();
	if(!sourceNode){
		std::cout<<"ERROR: Invalid input! Source node not provided."<<std::endl;
		return;
	}
	if(!destNode){
		std::cout<<"ERROR: Invalid input! Destination node not provided."<<std::endl;
		return;
	}
    if (mode=="driving" && !maxWalkTimeProvided) {
		if (incProvided && avoidNodesProvided && avoidSegmentsProvided) {
        	restrictedRoute(graph, sourceNode, destNode, incNode);
		}else if(!incProvided && !avoidNodesProvided && !avoidSegmentsProvided){
            independentRoute(graph, sourceNode, destNode);
		}else{
            std::cout<<"ERROR: Invalid sintax in input.txt, missing some statements."<<std::endl;
            return;
        }
    }else if (mode=="driving-walking" && !incProvided) {
      	if(maxWalkTimeProvided && avoidNodesProvided && avoidSegmentsProvided) {
      		bestRouteDrivingWalking(graph, sourceNode, destNode, maxWalkTime);
      	}else{
        	std::cout<<"ERROR: Invalid sintax in input.txt, missing some statements."<<std::endl;
        	return;
        }
    }else{
      	std::cout<<"ERROR: Invalid sintax in input.txt, to much statements provided."<<std::endl;
    }
    return;
}