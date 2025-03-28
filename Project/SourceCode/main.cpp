#include <iostream>
#include "loadGraph.h"
#include "batch.h"
#include "menu.h"


/**
 * @brief Asks the user for the mode of operation.
 * 
 * @details The function displays a menu with three options: Batch Mode, Menu Mode, and Exit. It prompts the user to enter their choice and validates the input. If the input is invalid, it will ask again until a valid choice is made.
 * 
 * @return int Returns the user's choice (1 for Batch Mode, 2 for Menu Mode, 3 for Exit).
 */
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


/**
 * @brief Main function of the program. It loads the graph from the CSV files, asks the user for the mode of operation, and runs the selected mode.
 * 
 * @details The program will ask the user for the mode of operation, either batch mode or menu mode. In batch mode, the program will read from a input.txt file, while in menu mode, the user will be prompted to enter the data manually. The program will then call the appropriate function to run the selected mode.
 * 
 * @return int Returns 0 if the program runs successfully.
 */
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