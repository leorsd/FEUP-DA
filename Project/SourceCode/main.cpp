#include <iostream>
#include "loadGraph.h"
#include "batch.h"
#include "menu.h"

/**
 * @mainpage
 *
 * # DA2025_PRJ1_T04G02
 * 
 * Welcome to the documentation of the **Route Planner**.
 * This project implements several algorithms for route planning and optimization.
 * It provides two main modes of operation: Batch Mode and Menu Mode.
 * In Batch Mode, the program reads input from a file and processes it automatically.
 * In Menu Mode, the user can interactively input data and receive results.
 * 
 * ## Features
 * - **Algorithm 1**: Independent route, for finding the shortest path between two locations.
 * - **Algorithm 2**: Restricted route, for finding the shortest path between two locations with restrictions.
 * - **Algorithm 3**: Driving-Walking combined route, for finding the shortest path, with restrictions, between two locations with a combination of driving and walking segments.
 * - **Algorithm 4**: Aproximate route after a Driving-Walking failure.
 * 
 * ## Usage
 * - To use the program, compile the source code and run the executable.
 * - To compile the source code and run it, use the following commands:
 *  ```
 * cmake ..
 * make
 * ./DA_Project
 * ```
 * - The first command generates the build files, the second command compiles the source code, and the last command runs the program.
 * - The program will start and the user will be available to interact with it.
 *
 * ### Authors:
 * - Afonso Miguel Almeida Pereira, up202305652@up.pt
 * - Leandro Filipe Pais Resende, up202306343@up.pt
 * - Mo'men Sami Ahmad Alhammadin, up202411533@up.pt
 *
 */

/**
 * @file main.cpp
 * @brief Main file for the Route Planner program.
 * 
 * This file contains the main function that initializes the graph, asks the user for the mode of operation, and runs the selected mode.
 */


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