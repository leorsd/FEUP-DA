#include "graph.h"

/************************* Vertex  **************************/

Vertex::Vertex(std::string location, int id, std::string code, bool parking) {
    this->location = location;
    this->id = id;
    this->code = code;
    this->parking = parking;
}

Edge *Vertex::addEdge(Vertex *dest, const double drivingTime, const double walkingTime) {
    auto newEdge = new Edge(this, dest, drivingTime, walkingTime);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(const std::string &code) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getCode() == code) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true;
        } else {
            ++it;
        }
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool Vertex::operator<(const Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const { return this->id; }
std::string Vertex::getLocation() const { return this->location; }
std::string Vertex::getCode() const { return this->code; }
bool Vertex::getParking() const { return this->parking; }
std::vector<Edge *> Vertex::getAdj() const { return this->adj; }
bool Vertex::isVisited() const { return this->visited; }
bool Vertex::isProcessing() const { return this->processing; }
unsigned int Vertex::getIndegree() const { return this->indegree; }
double Vertex::getDist() const { return this->dist; }
Edge *Vertex::getPath() const { return this->path; }
std::vector<Edge *> Vertex::getIncoming() const { return this->incoming; }

void Vertex::setId(int id) { this->id = id; }
void Vertex::setLocation(std::string location) { this->location = location; }
void Vertex::setCode(std::string code) { this->code = code; }
void Vertex::setParking(bool parking) { this->parking = parking; }
void Vertex::setVisited(bool visited) { this->visited = visited; }
void Vertex::setProcessing(bool processing) { this->processing = processing; }
void Vertex::setIndegree(unsigned int indegree) { this->indegree = indegree; }
void Vertex::setDist(double dist) { this->dist = dist; }
void Vertex::setPath(Edge *path) { this->path = path; }

void Vertex::deleteEdge(const Edge *edge) const {
    Vertex *dest = edge->getDest();
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getCode() == code) {
            it = dest->incoming.erase(it);
        } else {
            ++it;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double drivingTime, double walkingTime) {
    this->orig = orig;
    this->dest = dest;
    this->drivingTime = drivingTime;
    this->walkingTime = walkingTime;
}

Vertex *Edge::getDest() const { return this->dest; }
double Edge::getDrivingTime() const { return this->drivingTime; }
double Edge::getWalkingTime() const { return this->walkingTime; }
Vertex *Edge::getOrig() const { return this->orig; }
Edge *Edge::getReverse() const { return this->reverse; }
bool Edge::isSelected() const { return this->selected; }
void Edge::setSelected(bool selected) { this->selected = selected; }
void Edge::setReverse(Edge *reverse) { this->reverse = reverse; }
void Edge::setDrivingTime(double drivingTime) { this->drivingTime = drivingTime; }
void Edge::setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }

/********************** Graph  ****************************/

int Graph::getNumVertex() const {
    return vertexSet.size();
}
std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex *Graph::findVertex(const std::string &code) const {
    for (auto v : vertexSet)
        if (v->getCode() == code)
            return v;
    return nullptr;
}

Vertex *Graph::findVertex(int id) const{
  for (auto v : vertexSet)
    if (v->getId() == id)
      return v;
  return nullptr;
}

bool Graph::addVertex(const std::string &location, int id, const std::string &code, bool parking) {
    if (findVertex(code) != nullptr) return false;
    vertexSet.push_back(new Vertex(location, id, code, parking));
    return true;
}

bool Graph::removeVertex(const std::string &code) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getCode() == code) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const std::string &source, const std::string &dest, const double drivingTime, const double walkingTime) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, drivingTime, walkingTime);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const std::string &sourc, const std::string &dest) {
    Vertex* srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Graph::addBidirectionalEdge(const std::string &sourc, const std::string &dest, double drivingTime, double walkingTime) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, drivingTime, walkingTime);
    auto e2 = v2->addEdge(v1, drivingTime, walkingTime);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}
