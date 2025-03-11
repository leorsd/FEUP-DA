#include "loadGraph.h"

void loadGraph(const std::string& vertex_filename, const std::string& edge_filename, Graph* g) {
    std::ifstream vertex_file(vertex_filename);

    if(!vertex_file.is_open()) {
        std::cerr << "Error opening file " << vertex_filename << std::endl;
        exit(1);
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
        exit(1);
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

        if (!g->addBidirectionalEdge(vertex1, vertex2, drivingtime, walkingtime)) {
            std::cerr << "Edge contains vertex that not exists" << std::endl;
            exit(1);
        }
    }
    edge_file.close();
}
