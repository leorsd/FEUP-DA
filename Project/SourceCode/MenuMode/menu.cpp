#include "menu.h"

Vertex* askSourceId(Graph* graph){
  Vertex* sourceNode;
  int sourceId;

  std::cout << "\n--- Route Planner Menu ---\n";
  std::cout << "\n";
  std::cout << "What is the source node id?\n";

  while(true){

    std::cout << "Your choice: ";
    std::cin >> sourceId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
      std::cout << "Invalid input! You entered a non-integer value.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }else{
      sourceNode = graph->findVertex(sourceId);
      if (sourceNode != nullptr){
        break;
      }else{
        std::cout << "Source node id not found in the loaded graph, please try again.\n";
      }
    }
  }
  return sourceNode;
}

Vertex* askDestId(Graph* graph){
  Vertex* destNode;
  int destId;

  std::cout << "\n--- Route Planner Menu ---\n";
  std::cout << "\n";
  std::cout << "What is the destination node id?\n";

  while(true){
    std::cout << "Your choice: ";
    std::cin >> destId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
      std::cout << "Invalid input! You entered a non-integer value.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }else{
      destNode = graph->findVertex(destId);
      if (destNode != nullptr){
        break;
      }else{
        std::cout << "Destination node id not found in the loaded graph, please try again.\n";
      }
    }
  }
  return destNode;
}

void askAvoidNodes(Graph* graph){
  std::string line;

  std::cout << "\n--- Route Planner Menu ---\n";
  std::cout << "\n";
  std::cout << "What are the avoid nodes? (Use the id of the nodes, separate them by spaces)\n";
  std::cout << "Your choice: ";

  std::getline(std::cin, line);

  std::stringstream ss(line);
  std::string word;

  while (ss >> word) {
    try {
       int id = std::stoi(word);
       Vertex *vertex = graph->findVertex(id);
       if (vertex == nullptr){
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

Vertex* askIncludeNode(Graph* graph){
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
          if (includeNode == nullptr){
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

  while(true){

    std::cout << "Your choice: ";
    std::cin >> maxWalkTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
      std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }else{
      break;
    }
  }
  return maxWalkTime;
}

void runMenuMode(Graph* graph){
    int alg;

    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "1. Independent Route Planning\n";
    std::cout << "2. Restricted Route Planning\n";
    std::cout << "3. Best route for driving and walking\n";
    std::cout << "4. Exit\n";

    while (true) {

        std::cout << "Enter Choice: ";
        std::cin >> alg;

        if (std::cin.fail()) {
          std::cout << "Invalid input! You entered a non-integer value, please try again.\n";
          std::cin.clear();
          std::cin.ignore(1000, '\n');
        }else{
          if (alg < 1 || alg > 4){
            std::cout << "Invalid choice, please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }else{
            break;
          }
        }
    }
    Vertex* sourceNode,*destNode, *includeNode;
    int maxWalkTime = 0;
    switch (alg) {
      case 1:
        sourceNode = askSourceId(graph);
        destNode = askDestId(graph);
        independentRoute(graph, sourceNode, destNode);
        break;
      case 2:
        sourceNode = askSourceId(graph);
        destNode = askDestId(graph);
        askAvoidNodes(graph);
        askAvoidEdges(graph);
        includeNode = askIncludeNode(graph);
        restrictedRoute(graph, sourceNode, destNode, includeNode);
        break;
      case 3:
        sourceNode = askSourceId(graph);
        destNode = askDestId(graph);
        askAvoidNodes(graph);
        askAvoidEdges(graph);
        includeNode = askIncludeNode(graph);
        maxWalkTime = askMaxWalkTime(graph);
        bestRouteDrivingWalking(graph, sourceNode, destNode, includeNode, maxWalkTime);
        break;
      default:
        break;
    }
}