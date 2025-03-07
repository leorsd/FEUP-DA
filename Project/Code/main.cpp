#include <iostream>
#include "loadGraph.h"

int main(){
    Graph graph;
    if(!loadGraph("../Locations.csv", "../Distances.csv", &graph)){
      return 0;
    }
    for (Vertex* a : graph.getVertexSet()) {
        for (Edge* b: a->getAdj()) {
            if (b->getDrivingTime()==INF)std::cout<<b->getOrig()->getCode()<<" "<<b->getDest()->getCode()<<" "<<b->getDrivingTime()<<" "<<b->getWalkingTime()<<std::endl;
        }
    }
    return 0;
}