#include <iostream>
#include "GraphStructure/Graph.h"
#include "GraphStructure/loadGraph.h"
#include "batchMode.h"

int main(){
    Graph graph;
    loadGraph("../Data/Locations.csv", "../Data/Distances.csv", &graph);
    int mode;
    while (true) {
        std::cout << "\n--- Route Planner Menu ---\n";
        std::cout << "1. Batch Mode (automated)\n";
        std::cout << "2. User-Friendly Mode\n";
        std::cout << "3. Exit\n";

        std::cout << "Enter Choice: ";
        std::cin >> mode;
        if (mode == 1) {
            batchMode(&graph);
            break;
        }
        if (mode == 2) {
            std::cout << "user-friendly";
            break;
        }
        if (mode == 3) {
            break;
        }
        std::cout << "Invalid choice, please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}