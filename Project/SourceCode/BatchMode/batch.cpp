#include "batch.h"

bool startsWith(const std::string& line, const std::string& prefix) {
    return line.substr(0, prefix.length()) == prefix;
}

Vertex* getNode(std::string line, Graph* graph) {
  Vertex* node = nullptr;
  try{
    int id=std::stoi(line);
    node=graph->findVertex(id);
    if(node==nullptr){
      std::cout<<"Vertex with id "<<id<<" not found in graph"<<std::endl;
      return nullptr;
    }else{
      return node;
    }
  }catch(...){
    std::cout<<"Invalid input! It should be an integer: "<<line<<std::endl;
    return nullptr;
  }
}

void runBatchMode(Graph* graph){
	std::ifstream input_file("../Data/input.txt");

    if (!input_file.is_open()) {
        std::cerr << "Error opening input.txt.\n";
        exit(1);
    }

    std::string line;

    std::string mode = "";
    Vertex* sourceNode = nullptr;
    Vertex* destNode = nullptr;
    Vertex* includeNode = nullptr;


    while (std::getline(input_file, line)) {
      	if (startsWith(line, "Mode:")) {
          	mode = line.substr(5, line.length());
          	if (mode!=("driving") && mode!=("driving-walking")) {
            	std::cout<<"Invalid value for mode!"<<std::endl;
            	return;
          	}
      	}
    	else if (startsWith(line, "Source:")) {
          	sourceNode = getNode(line.substr(7,line.length()), graph);
          	if(sourceNode==nullptr){
            	return;
          	}
      	}
      	else if (startsWith(line, "Dest:")) {
			destNode = getNode(line.substr(5,line.length()), graph);
        	if(destNode==nullptr){
          		return;
        	}
      	}
    }
    input_file.close();
	std::cout<<"batch succes"<<std::endl;
    return;
}