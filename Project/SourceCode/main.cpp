#include <iostream>
#include "loadGraph.h"
#include "batch.h"
#include "menu.h"


int askForMode(){
    int choice;
    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What method you want to use?\n";
    std::cout << "1. Batch Mode (reads from a input.txt)\n";
    std::cout << "2. Menu Mode (user-friendly)\n";
    std::cout << "3. Exit\n";

    while (true){
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid choice, please enter a number between 1 and 3\n";
        } else if(choice < 1 || choice > 3) {
            std::cout << "Invalid choice, please try again\n";
        } else {
            return choice;
        }
    }
}


int main(){
    Graph graph;
    loadGraph("../Data/Locations.csv", "../Data/Distances.csv", &graph);

    int mode = askForMode();
    if ( mode == 1 ){
      runBatchMode(&graph);
    }else if ( mode == 2 ){
      runMenuMode(&graph);
    }
    return 0;
}