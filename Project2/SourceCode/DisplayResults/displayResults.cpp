#include "displayResults.h"

/**
 * @file displayResults.cpp
 * @brief This file contains the implementation of the function to display the results of the algorithms declared in displayResults.h.
 */

 void displayInputSizeToBig(int algorithm, int inputSize){
    std::cout << "\n--- Delivery Truck Pallet Packing Optimization ---\n";
    std::cout << "\nThe input size of " << inputSize << " is to big for the";
    switch(algorithm){
        case 1:
            std::cout << " Brute Force Approach.\n";
            std::cout << "Due to the exponential complexity time of the brute force approach, it is limit to a maximum input size  of 25 pallets.\n";
            std::cout << "An input size bigger than 25 will take to much time to compute.\n";
            break;
        case 2:
            std::cout << " Backtracking Approach.\n";
            std::cout << "Due to the exponential complexity time of the backtracking approach, it is limit to a maximum input size of 25 pallets.\n";
            std::cout << "An input size bigger than 25 will take to much time to compute.\n";
            break;
        default:
            break;
    }
}    

void displayAlgorithmResult(int algorithm, Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets, std::vector<bool>& optimalPallets, double elapsedTime){
    std::cout << "\n--- Delivery Truck Pallet Packing Optimization ---\n";
    std::cout << "\n";
    std::cout << "Algorithm used: ";
    switch (algorithm){
        case 1:
            std::cout << "Brute Force Approach\n";
            break;
        case 2:
            std::cout << "Backtracking Approach\n";
            break;
        case 3:
            std::cout << "Greedy Approach\n";
            break;
        case 4:
            std::cout << "Dynamic Programming Approach\n";
            break;
        case 5:
            std::cout << "Integer Linear Programming Approach\n";
            break;
        default:
            break;
    }

    std::cout << "\n--Results of the selected algorithm--\n";
    std::cout << "Selected Pallets IDs: ";

    int totalWeight = 0;
    int totalProfit = 0;

    int maxProfit = 0;
    int maxWeight = 0;
    std::string optimalPalletsString = "Optimal Pallets IDs: ";

    for (size_t i = 0; i < pallets.size(); ++i){
        if (selectedPallets[i]){
            totalWeight += pallets[i].weight;
            totalProfit += pallets[i].profit;
            std::cout << pallets[i].id << " ";
        }
        if (optimalPallets[i]){
            maxProfit += pallets[i].profit;
            maxWeight += pallets[i].weight;
            optimalPalletsString += std::to_string(pallets[i].id) + " ";
        }
    }
    std::cout << "\n";
    std::cout << "Capacity used: " << totalWeight << " of " << truck.capacity << "\n";
    std::cout << "Total profit: " << totalProfit << "\n";
    std::cout << "Running time: " << elapsedTime << " microseconds\n";
    std::cout << "Running time: " << elapsedTime / 1000 << " milliseconds\n";
    std::cout << "Running time: " << elapsedTime / 1000000 << " seconds\n";

    if (totalProfit == maxProfit){
        std::cout << "\nFinal Result: The selected algorithm found the optimal solution.\n";
    }else{
        std::cout << "\n--Results of the optimal solution--\n";

        std::cout << optimalPalletsString << "\n";
        std::cout << "Capacity used: " << maxWeight << " of " << truck.capacity << "\n";
        std::cout << "Total profit: " << maxProfit << "\n";
        std::cout << "\nFinal Result: The selected algorithm did not find the optimal solution.\n";
    }
}