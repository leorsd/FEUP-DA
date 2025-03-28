#include <iostream>
#include "loadGraph.h"
#include "batch.h"
#include "menu.h"


int askForMode(){
    std::string line;
    std::cout << "\n--- Route Planner Menu ---\n";
    std::cout << "\n";
    std::cout << "What method you want to use?\n";
    std::cout << "1. Batch Mode (reads from a input.txt)\n";
    std::cout << "2. Menu Mode (user-friendly)\n";
    std::cout << "3. Exit\n";

    while (true){
        std::cout << "Enter Choice: ";
        try{
            getline(std::cin, line);
            if ( line.empty()){
                std::cout << "Invalid input! An action needs to be chosen.\n";
            }else{
                int choice = std::stoi(line);
                if (choice < 1 || choice > 3){
                    std::cout << "Invalid input! Please enter a number between 1 and 3.\n";
                }else{
                    return choice;
                }
            }
        } catch (...){
            std::cout << "You entered a non-integer value, please try again.\n";
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