#include <iostream>
#include <vector>
#include "pallet.h"
#include "truck.h"
#include "loadTruck.h"
#include "loadPallets.h"
#include "algorithms.h"
#include <chrono>
#include "displayResults.h"


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

        std::vector<bool> selectedPallets(pallets.size(), false);
        std::vector<bool> optimalPallets(pallets.size(), false);

        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;

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