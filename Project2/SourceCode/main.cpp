#include <iostream>
#include <vector>
#include "pallet.h"
#include "truck.h"
#include "loadTruck.h"
#include "loadPallets.h"
#include "algorithms.h"
#include <chrono>
#include "displayResults.h"

/**
 * @mainpage
 *
 * # DA2025_PRJ2_T04G2
 * 
 * Welcome to the documentation of the **Delivery Truck Pallet Packing Optimization** project.
 * This project implements and compares several algorithms for efficiently loading pallets onto a delivery truck.
 * It provides an interactive menu for users to select datasets and algorithms.
 * 
 * ## Features
 * - **Brute Force Approach**: Finds the optimal pallet arrangement by checking all possibilities (for small datasets).
 * - **Backtracking Approach**: Systematically explores possible arrangements, pruning invalid options.
 * - **Greedy Approach**: Selects pallets based on a heuristic for fast, approximate solutions.
 * - **Dynamic Programming Approach**: Efficiently computes the optimal arrangement using subproblem solutions.
 * - **Integer Linear Programming Approach**: Uses mathematical optimization to find the best solution.
 * 
 * ## Usage
 * - To use the program, compile the source code and run the executable.
 * - Make sure you are in a build directory, if not create one in the SourceCode directory.
 * - To compile and run, use the following commands:
 *   ```
 *   cmake ..
 *   make
 *   ./DA_Project
 *   ```
 * - The first command generates build files, the second compiles the code, and the last runs the program.
 * - Follow the on-screen menu to select a dataset and algorithm.
 *
 * ### Authors:
 * - Afonso Miguel Almeida Pereira, up202305652@up.pt
 * - Leandro Filipe Pais Resende, up202306343@up.pt
 * - Mo'men Sami Ahmad Alhammadin, up202411533@up.pt
 *
 */


/**
 * @brief Asks the user for a dataset choice.
 * 
 * @details This function prompts the user to select a dataset from 1 to 10 or exit by entering 0. It validates the input and returns the chosen dataset number.
 * 
 * @return int The chosen dataset number (1-10) or 0 to exit.
 */
int askForDataSet(){
    std::string line;
    std::cout << "\n--- Delivery Truck Pallet Packing Optimization ---\n";
    std::cout << "\n";
    std::cout << "What dataset you want to use? Please enter a number between 1 and 10, 0 to exit!\n";

    while (true){
        std::cout << "Enter Choice: ";
        try{
            getline(std::cin, line);
            if ( line.empty()){
                std::cout << "Invalid input! A dataset needs to be chosen, please try again.\n";
            }else{
                int choice = std::stoi(line);
                if (choice < 0 || choice > 10){
                    std::cout << "Invalid input! Please enter a number between 1 and 10, please try again.\n";
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
 * @brief Asks the user for an algorithm choice.
 * 
 * @details This function prompts the user to select an algorithm from a list of options or exit. It validates the input and returns the chosen algorithm number.
 * 
 * @return int The chosen algorithm number (1-6) or 6 to exit.
 */
int askForAlgorithm(){
    std::string line;
    std::cout << "\n--- Delivery Truck Pallet Packing Optimization ---\n";
    std::cout << "\n";
    std::cout << "What algorithm you want to use?\n";
    std::cout << "1. Brute Force Approach\n";
    std::cout << "2. Backtracking Approach\n";
    std::cout << "3. Greedy Approach\n";
    std::cout << "4. Dynamic Programming Approach\n";
    std::cout << "5. Integer Linear Approach\n";
    std::cout << "6. Exit\n";

    while (true){
        std::cout << "Enter Choice: ";
        try{
            getline(std::cin, line);
            if ( line.empty()){
                std::cout << "Invalid input! An algorithm needs to be chosen, please try again.\n";
            }else{
                int choice = std::stoi(line);
                if (choice < 1 || choice > 6){
                    std::cout << "Invalid input! Please enter a number between 1 and 6, please try again.\n";
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
 * @brief Main function to run the Delivery Truck Pallet Packing Optimization program.
 * 
 * @details This function serves as the entry point of the program. It continuously prompts the user to select a dataset and an algorithm, executes the chosen algorithm, and displays the results. The program runs until the user chooses to exit.
 * 
 * @return int Returns 0 on successful execution or 1 if an error occurs.
 */
int main(){
    while(true){
        
        int choice = askForDataSet();

        if (choice == 0){
            return 0;
        }

        Truck truck;
        if (!loadTruck(choice, truck)){
            return 1;
        }

        std::vector<Pallet> pallets;
        if (!loadPallets(choice,truck.availablePallets,pallets)){
            return 1;
        }

        int algorithmChoice = askForAlgorithm();

        if (algorithmChoice == 6){
            return 0;
        }

        // Initialize vectors to keep track of selected pallets and optimal pallets
        std::vector<bool> selectedPallets(pallets.size(), false);
        std::vector<bool> optimalPallets(pallets.size(), false);

        // Initialize variables to measure the execution time of the algorithms
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;

        // For the selected algorithm, it will execute the corresponding approach and measure the time taken, then display the results
        switch (algorithmChoice){
            case 1:
                if (truck.availablePallets > 25){
                    displayInputSizeToBig(1, truck.availablePallets);
                }
                else{
                    start = std::chrono::high_resolution_clock::now();
                    bruteForceApproach(truck, pallets, selectedPallets);
                    end = std::chrono::high_resolution_clock::now();

                    optimalPallets = selectedPallets; // Assuming brute force gives the optimal solution

                    displayAlgorithmResult(1, truck, pallets, selectedPallets, optimalPallets, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                }
                break;
            case 2:
                if (truck.availablePallets > 25){
                    displayInputSizeToBig(2, truck.availablePallets);
                }else{
                    start = std::chrono::high_resolution_clock::now();
                    backtrackingApproach(truck, pallets, selectedPallets);
                    end = std::chrono::high_resolution_clock::now();

                    optimalPallets = selectedPallets; // Assuming backtracking gives the optimal solution

                    displayAlgorithmResult(2, truck, pallets, selectedPallets, optimalPallets, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                }
                break;
            case 3:
                start = std::chrono::high_resolution_clock::now();
                greedyApproach(truck, pallets, selectedPallets);
                end = std::chrono::high_resolution_clock::now();

                dynamicProgrammingApproach(truck, pallets, optimalPallets); // Uses dynamic programming to find the optimal solution and compatare with greedy

                displayAlgorithmResult(3, truck, pallets, selectedPallets, optimalPallets, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                break;
            case 4:
                start = std::chrono::high_resolution_clock::now();
                dynamicProgrammingApproach(truck, pallets, selectedPallets);
                end = std::chrono::high_resolution_clock::now();

                optimalPallets = selectedPallets; // Assuming dynamic programming gives the optimal solution

                displayAlgorithmResult(4, truck, pallets, selectedPallets, optimalPallets, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                break;
            case 5:
                start = std::chrono::high_resolution_clock::now();
                integerLinearProgrammingApproach(truck, pallets, selectedPallets);
                end = std::chrono::high_resolution_clock::now();

                optimalPallets = selectedPallets; // Assuming integer linear programming gives the optimal solution

                displayAlgorithmResult(5, truck, pallets, selectedPallets, optimalPallets, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                break;
            default:
                break;
        }

        std::cout << "\nPress enter to go back to the menu.";
        std::string wait;
        std::getline(std::cin, wait);
    }    
}