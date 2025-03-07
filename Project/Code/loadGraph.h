#ifndef LOADGRAPH_H
#define LOADGRAPH_H

#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"

bool loadGraph(const std::string& vertex_filename, const std::string& edge_filename, Graph* g) {
    std::ifstream vertex_file(vertex_filename);

    if(!vertex_file.is_open()) {
        std::cerr << "Error opening file " << vertex_filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(vertex_file, line);  //skip the first line

    while(std::getline(vertex_file, line)) {
        std::stringstream ss(line);

        std::string location;
        int id;
        std::string code;
        bool parking;

        std::getline(ss, location, ',');

        std::getline(ss, line, ',');
        std::stringstream id_stream(line);
        id_stream >> id;

        std::getline(ss, code, ',');

        std::string string_parking;
        std::getline(ss, string_parking,',');
        parking = (string_parking == "1");

        g->addVertex(location, id, code, parking);
    }

    vertex_file.close();

    std::ifstream edge_file(edge_filename);

    if (!edge_file.is_open()) {
        std::cerr << "Error opening file " << edge_filename << std::endl;
        return false;
    }

    std::getline(edge_file, line); // skip the first line

    while (std::getline(edge_file, line)) {
        std::stringstream ss(line);
        std::string vertex1, vertex2;
        double drivingtime, walkingtime;

        std::getline(ss, vertex1, ',');

        std::getline(ss, vertex2, ',');

        std::getline(ss, line, ',');
        if (line == "X") {
            drivingtime = INF;
        }else {
            std::stringstream drive(line);
            drive >> drivingtime;
        }

        std::getline(ss, line, ',');
        std::stringstream walk(line);
        walk >> walkingtime;

        if (g->findVertex(vertex1)==nullptr || g->findVertex(vertex2)==nullptr) {
            std::cerr << "Edge contains vertex that not exists" << std::endl;
            return false;
        }
        g->addEdge(vertex1, vertex2, drivingtime, walkingtime);
    }
    edge_file.close();
    return true;
}
#endif
