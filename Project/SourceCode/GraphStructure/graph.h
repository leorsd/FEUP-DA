#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <limits>

/**
 * @file This file contains the definition of the graph structure used in the algorithms and its components.
 * The implementation of the graph structure is done in the graph.cpp file.
 */

#define INF std::numeric_limits<double>::max()

class Edge;

/************************* Vertex  **************************/

/**
 * @brief Class representing a vertex in the graph.
 * 
 * @details The Vertex class contains information about the vertex such as its id, location, code and parking availability. It also provides methods to manipulate edges and manage the state of the vertex during graph algorithms.
 */
class Vertex {
public:
    Vertex(std::string location, int id, std::string code, bool parking);

    bool operator<(const Vertex &vertex) const; // required by MutablePriorityQueue

    int getId() const;
    std::string getCode() const;
    std::string getLocation() const;
    bool getParking() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    bool getAvoid() const;

    void setId(int id);
    void setCode(std::string code);
    void setLocation(std::string location);
    void setParking(bool parking);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    void setAvoid(bool avoid);

    Edge *addEdge(Vertex *dest, double drivingTime, double walkingTime);
    bool removeEdge(const std::string &code);
    void removeOutgoingEdges();

    int queueIndex = 0;     // required by MutablePriorityQueue

protected:
    int id;                   // Unique identifier
    std::string location;      // Location name
    std::string code;          // Unique code
    bool parking;              // Parking availability
    bool avoid = false;       // Used for algorithsm that need to avoid vertexs

    std::vector<Edge *> adj;   // Outgoing edges

    // Auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree = 0;
    double dist = 0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming; // Incoming edges

    void deleteEdge(const Edge *edge) const;
};

/********************** Edge  ****************************/

/**
 * @brief Class representing an edge in the graph.
 * 
 * @details The Edge class contains information about the edge such as its origin and destination vertices, driving time, walking time and whether it should be avoided. It also provides methods to manipulate the state of the edge during graph algorithms.
 */
class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double drivingTime, double walkingTime);

    Vertex *getOrig() const;
    Vertex *getDest() const;
    double getDrivingTime() const;
    double getWalkingTime() const;
    bool getAvoid() const;

    bool isSelected() const;
    Edge *getReverse() const;

    void setDrivingTime(double drivingTime);
    void setWalkingTime(double walkingTime);
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setAvoid(bool avoid);

protected:
    Vertex *orig;  // Origin vertex
    Vertex *dest;  // Destination vertex
    double drivingTime;     // Driving time of the edge
    double walkingTime;     // Walking time of the edge
    bool avoid = false;    // Used for algorithms that need to avoid edges

    // Auxiliary fields
    bool selected = false;
    Edge *reverse = nullptr;
};

/********************** Graph  ****************************/

/**
 * @brief Class representing the graph structure.
 * 
 * @details The Graph class contains a collection of vertices and provides methods to manipulate the graph such as adding and removing vertices and edges, and retrieving vertex information. It also provides methods to get the number of vertices and the set of vertices in the graph.
 */
class Graph {
public:
    Vertex *findVertex(const std::string &code) const;
    Vertex *findVertex(int id) const;
    bool addVertex(const std::string &location, int id, const std::string &code, bool parking);
    bool removeVertex(const std::string &code);

    bool addEdge(const std::string &source, const std::string &dest, double drivingTime, double walkingTime);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &source, const std::string &dest, double drivingTime, double walkingTime);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

protected:
    std::vector<Vertex *> vertexSet;
};
#endif

