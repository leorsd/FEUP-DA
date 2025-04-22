#include "algorithms.h"

#include <algorithm>

/**
 * @file algorithms.cpp
 * @brief This file contains the implementations of various algorithms for solving the pallet packing problem declared in algorithms.h.
 */

void bruteForceApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::cout << "Brute Force Approach\n";
}

void backtrackingRecursion(Truck& truck, std::vector<Pallet>& pallets, int index, int currentValue, int currentWeigth, int& bestValue, std::vector<int>& remainValue, std::vector<bool>& currentPallets, std::vector<bool>& bestSelection) {

    if ( index == truck.availablePallets) {
        if (currentValue > bestValue) {
            bestValue = currentValue;
            bestSelection = currentPallets;
        }
        return;
    }

    if ( currentValue + remainValue[index] <= bestValue) {
        return;
    }

    backtrackingRecursion(truck, pallets, index + 1, currentValue, currentWeigth, bestValue, remainValue, currentPallets, bestSelection);

    if ( currentWeigth + pallets[index].weight <= truck.capacity) {
        currentPallets[index] = true;
        backtrackingRecursion(truck, pallets, index + 1, currentValue + pallets[index].profit, currentWeigth + pallets[index].weight, bestValue, remainValue, currentPallets, bestSelection);
        currentPallets[index] = false;
    }
}

void backtrackingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::vector<int> remainValue(truck.capacity + 1, 0);
    for (int i = pallets.size()-1; i >=0 ; i--) {
        remainValue[i] = remainValue[i + 1] + pallets[i].profit;
    }

    std::vector<bool> currentSelected(pallets.size());
    int bestValue = 0;
    backtrackingRecursion(truck, pallets, 0, 0, 0, bestValue, remainValue, currentSelected, selectedPallets);
}

void greedyApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::sort(pallets.begin(), pallets.end(),
        [](Pallet& pallet1, Pallet& pallet2) {return (double)(pallet1.profit) / pallet1.weight > (double)(pallet2.profit)/pallet2.weight; });

    int selectedPalletsWeightSum = 0;
    int numberOfPallets = 0;
    for (int i = 0; i< pallets.size(); i++) {
        if (numberOfPallets < truck.availablePallets) {
            if (pallets[i].weight + selectedPalletsWeightSum <= truck.capacity ) {
                selectedPallets[i] = true;
                selectedPalletsWeightSum += pallets[i].weight;
                numberOfPallets++;
            }
        }
    }
}

void dynamicProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::cout << "Dynamic Programming Approach\n";
}

void integerLinearProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::cout << "Integer Linear Programming Approach\n";
}