#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include <set>
#include "graph.h"
#include "mutablePriorityQueue.h"

/**
 * @brief This file contains the function declarations for the algorithms used in the project.
 * This file also contians the RouteResult enum that is used to indicate the result of the bestRouteDrivingWalking function.
 * The algorithms are implemented in the algorithms.cpp file.
 */


/**
 * @brief RouteResult is an enum that represents the possible results of the bestRouteDrivingWalking function.
 * It is used to indicate the status of the route calculation.
 * The possible values are:
 * - NO_PARKING_AVAILABLE: There are not nodes with parking availability.
 * - WALKING_TIME_EXCEEDED: The walking time exceeded the maximum allowed time.
 * - INVALID_ROUTE: The route is invalid.
 * - NO_DRIVING_AVAILABLE: No driving available from the source to any arking node.
 * - NO_WALKING_AVAILABLE: No walking available from any parking node to the destination.
 * - VALID_ROUTE: The route is valid.
 */
enum RouteResult {
    NO_PARKING_AVAILABLE,
    WALKING_TIME_EXCEEDED,
    INVALID_ROUTE,
    NO_DRIVING_AVAILABLE,
    NO_WALKING_AVAILABLE,
    VALID_ROUTE,
};

/**
 * @brief The function relaxDriving is used to relax the edges of the graph for the driving algorithm.
 * @param edge The edge to be relaxed.
 * @return true if the edge was relaxed, false otherwise.
 */
bool relaxDriving(Edge *edge);

/**
 * @brief The function relaxWalking is used to relax the edges of the graph for the walking algorithm.
 * 
 * @param edge The edge to be relaxed.
 * @return true if the edge was relaxed, false otherwise.
 */
bool relaxWalking(Edge *edge);


/**
 * @brief The function dijkstraDriving is used to calculate the shortest path for driving from the source node to the destination node or to all nodes if the destNode is nullptr.
 * 
 * @details The algorithm is done to ignore the nodes or the edges that have the avoid flag set to true, so this nodes and edges will not be included in the route.
 * This is useful to avoid nodes that are not allowed to be used in the route, for example, nodes that need to be avoided due to the user restrictions or the nodes that were used for the best route and need to be avoided for the alternative route.
 * Asymptotic complexity: O( (V + E) log V) where E is the number of edges and V is the number of vertices.
 * 
 * @param g The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 */
void dijkstraDriving(Graph *g, Vertex *sourceNode, Vertex *destNode);

/**
 * @brief The function dijkstraWalking is used to calculate the shortest path for walking from the source node to the destination node or to all nodes if the destNode is nullptr.
 * The algorithm is done to ignore the nodes or the edges that have the avoid flag set to true, so this nodes and edges will not be included in the route. 
 * This is useful to avoid nodes that are not allowed to be used in the route, for example, nodes that need to be avoided due to the user restrictions or the nodes that were used for the best route and need to be avoided for the alternative route.
 * 
 * @details The algorithm is done to ignore the nodes or the edges that have the avoid flag set to true, so this nodes and edges will not be included in the route. 
 * This is useful to avoid nodes that are not allowed to be used in the route, for example, nodes that need to be avoided due to the user restrictions or the nodes that were used for the best route and need to be avoided for the alternative route.
 * Asymptotic complexity: O( (V + E) log V) where E is the number of edges and V is the number of vertices. 
 * 
 * @param g The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 */
void dijkstraWalking(Graph *g, Vertex *sourceNode, Vertex *destNode);


/**
 * @brief Executes the algorithm to compute the best route from the source node to the destination node and an alternative route that not includes the same nodes.
 * 
 * @details The algorithm uses Dijkstra's algorithm to compute the shortest path from the source node to the destination node, for each one of the nodes that are in the best route, the avoid flag is set to true and the Dijkstra's algorithm is executed again to compute the alternative route. 
 * The asymptotic complexity of the algorithm is set by the Dijkstra's algorithm for shortest paths, which is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 * 
 * @param graph The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 * @param bestRoute The list where the nodes resulting from the best route will be stored.
 * @param bestRouteTime The time of the best route.
 * @param alternativeRoute The list where the nodes resulting from the alternative route will be stored.
 * @param alternativeRouteTime The time of the alternative route. 
 * 
 * @return void
 */
void independentRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* bestRoute, int* bestRouteTime, std::list<int>* alternativeRoute, int* alternativeRouteTime);

/**
 * @brief Executes the algorithm to compute the best route from the source node to the destination node, with the provided restrictions.
 * 
 * @details The algorithm uses Dijkstra's algorithm to compute the shortest path from the source node to the destination node excluding the nodes and edges with the avoid flag set to true.
 * In order to include a certain node, the algorithm will compute the shortest path from the source node to the include node and then from the include node to the destination node.
 * 
 *  The asymptotic complexity of the algorithm is set by the Dijkstra's algorithm for shortest paths, which is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 * 
 * @param graph The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 * @param includeNode The node that must be included in the route.
 * @param restrictedRoute The list where the nodes resulting from the best route will be stored.
 * @param restrictedRouteTime The time of the best route.
 * 
 * @return void
 */
void restrictedRoute(Graph* graph, Vertex* sourceNode, Vertex* destNode, Vertex* includeNode, std::list<int>* restrictedRoute, int* restrictedRouteTime);


/**
 * @brief Executes the algorithm to compute the best route from the source node to the destination node, including a driving segment, a parking node and a walking segment.
 * 
 * @details The algorithm is divided in 3 parts:
 * 1. Compute the shortest path from the source node to all the parking nodes. It is used 1 Dijkstra's algorithm to compute all the shortest paths from the source node to all the parking nodes. This paths are stored in a list.
 * 2. Compute the shortest path from all the parking nodes to the destination node. It is used 1 Dijkstra's algorithm to compute all the shortest paths from all the parking nodes to the destination node. This paths are stored in a list.
 * 3. The best combination of the driving paths and walking paths is done, garanting that the time of the walking path is less than the maximum time allowed for walking and the end of the driving segments is the same as the start of the walking segment. The best combination is the one that has the minimum time of driving and walking.
 * 
 * The asymptotic comlexity of this algorithm is easily divided in 2 parts, the Dijkstra's algorithm for the driving or the walking segment and the computation of the best combination of driving and walking segments. 
 * The complexity of the Dijkstra's algorithm is O((V + E) log V), where V is the number of vertices and E is the number of edges. 
 * The complexity of the combination of driving and walking segments is O(n^2), where n is the number of parking nodes, that in the worst case is V.
 * So, in the worst case, the complexity of the algorithm is dominated by the dijkstra's algorithm, which is O((V + E) log V), where E can be V^2. So in the worst case, the complexity is O(V^2 log V).
 * In case of sparse graphs, the dijkstra's algorithm can be (V log V), when the number of edges is less than V^2. In this scenario, the complexity of the algorithm is dominated by the combination of driving and walking segments, which is O(n^2), where n is the number of parking nodes and in the worst case, n is V.
 * In the end, in the worst cases, the complexity of the algorithm is O(V² log V) for dense graphs and O(V²) for sparse graphs.
 * 
 * @param graph The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 * @param maxWalkTime The maximum time allowed for walking.
 * @param drivingRoute The list where the nodes resulting from the best route will be stored.
 * @param drivingTime The time of the best route.
 * @param walkingRoute The list where the nodes resulting from the best route will be stored.
 * @param walkingTime The time of the best route.
 * 
 * @return RouteResult The result of the route calculation, that is used to determine if an aproximate solution is possible or not.
 */
RouteResult bestRouteDrivingWalking(Graph* graph, Vertex* sourceNode, Vertex* destNode, int maxWalkTime, std::list<int>* drivingRoute, int* drivingTime, std::list<int>* walkingRoute, int* walkingTime);

/**
 * @brief Executes the algorithm to compute the best aproximate solution after the failing of the best route with driving and walking segments.
 * 
 * @details The algorithm is similar to the bestRouteDrivingWalking algorithm. The only differente is in the computation of the best combination of driving and walking segments.
 * The algorithm will compute the best combination of driving and walking segments, but this time, the algorithm will not check if the time of the walking segment is less than the maximum time allowed for walking.
 * This way, the best combinations found will have the less time of driving and walking segments, but the time of the walking segment can be greater than the maximum time allowed for walking.
 * 
 * The asymptotic comlexity of this algorithm is exacty the same as the bestRouteDrivingWalking algorithm, as the only difference in the computation of the best combination does not affect the complexity of the algorithm.
 * 
 * @param graph The graph to be used.
 * @param sourceNode The source node.
 * @param destNode The destination node.
 * @param drivingRoute1 The list where the nodes resulting from the best driving segment will be stored.
 * @param drivingTime1 The time of the best driving segment.
 * @param walkingRoute1 The list where the nodes resulting from the best walking segment will be stored.
 * @param walkingTime1 The time of the best walking segment.
 * @param drivingRoute2 The list where the nodes resulting from the second best driving segment will be stored.
 * @param drivingTime2 The time of the second best driving segment.
 * @param walkingRoute2 The list where the nodes resulting from the second best walking segment will be stored.
 * @param walkingTime2 The time of the second best walking segment.
 * 
 * @return void
 */
void aproximateSolution(Graph* graph, Vertex* sourceNode, Vertex* destNode, std::list<int>* drivingRoute1, int* drivingTime1, std::list<int>* walkingRoute1, int* walkingTime1, std::list<int>* drivingRoute2, int* drivingTime2, std::list<int>* walkingRoute2, int* walkingTime2);

#endif //ALGORITHMS_H
