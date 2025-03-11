#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

void batchMode(Graph* g, int algorithm) {

    std::ifstream input_file("../Data/input.txt");

    if (!input_file.is_open()) {
        std::cerr << "Error opening input.txt.\n";
        exit(1);
    }

    std::string line;

    std::string mode = "";
    int sourceId = -1,destId = -1,includeNode = -1,maxWalkTime = -1;
    std::vector<int> avoidNodes;
    std::vector<std::pair<int,int>> avoidSegments;

    std::regex modePattern(R"(^Mode:\s*(\S+))");
    std::regex sourcePattern(R"(^Source:\s*(\d+))");
    std::regex destPattern(R"(^Destination:\s*(\d+))");
    std::regex includeNodePattern(R"(^IncludeNode:\s*(\d+))");
    std::regex maxWalkTimePattern(R"(^MaxWalkTime:\s*(\d+))");
    std::regex avoidNodesPattern(R"(^AvoidNodes:\s*(\d+(?:\s*,\s*\d+)*))");
    std::regex avoidSegmentsPattern(R"(^AvoidSegments:\s*(\((\d+)\s*,\s*(\d+)\)(?:\s*,\s*\((\d+)\s*,\s*(\d+)\))*)$)");

    while (std::getline(input_file, line)) {
        std::smatch match;

        if (std::regex_search(line, match, modePattern)) {
            mode = match[1].str();
        }

        else if (std::regex_search(line, match, sourcePattern)) {
            sourceId = std::stoi(match[1].str());
        }

        else if (std::regex_search(line, match, destPattern)) {
            destId = std::stoi(match[1].str());
        }

        else if (std::regex_search(line, match, includeNodePattern)) {
            includeNode = std::stoi(match[1].str());
        }

        else if (std::regex_search(line, match, maxWalkTimePattern)) {
            maxWalkTime = std::stoi(match[1].str());
        }

        else if (std::regex_search(line, match, avoidNodesPattern)) {
            std::string nodesStr = match[1].str();
            std::stringstream ss(nodesStr);
            std::string node;
            while (std::getline(ss, node, ',')) {
                avoidNodes.push_back(std::stoi(node));
            }
        }

        else if (std::regex_search(line, match, avoidSegmentsPattern)) {
            std::string edgesStr = match[1].str();
            std::regex edgePattern(R"(\((\d+)\s*,\s*(\d+)\))");
            std::sregex_iterator edgesBegin(edgesStr.begin(), edgesStr.end(), edgePattern);
            std::sregex_iterator edgesEnd;
            for (auto it = edgesBegin; it != edgesEnd; ++it) {
                int node1 = std::stoi((*it)[1].str());
                int node2 = std::stoi((*it)[2].str());
                avoidSegments.push_back({node1, node2});
            }
        }
        else {
            std::cerr << "Unrecognized line format: " + line << std::endl;
            exit(1);
        }
    }
    input_file.close();

    if ( g->findVertex(sourceId) == nullptr || g->findVertex(destId) == nullptr ) {
      std::cerr << "Source or Destination Nodes do not exist in graph." << std::endl;
      exit(1);
    }

    switch (algorithm) {
      case 1:
        //call normal algorithm
        break;
      case 2:

    }


    return;
}