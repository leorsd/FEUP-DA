#include "algorithms.h"

#include <algorithm>

/**
 * @file algorithms.cpp
 * @brief This file contains the implementations of various algorithms for solving the pallet packing problem declared in algorithms.h.
 */


void bruteForceApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::cout << "Brute Force Approach\n";
}


void backtrackingRecursion(Truck& truck, std::vector<Pallet>& pallets, int index,int currentValue, int currentWeight, int currentCount,int& bestValue,
    int& bestCount, std::vector<int>& remainValue,std::vector<bool>& currentPallets,std::vector<bool>& bestSelection) {

    if (index == truck.availablePallets) {
        if (currentValue > bestValue || (currentValue == bestValue && currentCount < bestCount)) {
            bestValue = currentValue;
            bestCount = currentCount;
            bestSelection = currentPallets;
        }
        return;
    }

    if ( currentValue + remainValue[index] < bestValue) {
        return;
    }

    backtrackingRecursion(truck, pallets, index + 1, currentValue, currentWeight, currentCount, bestValue, bestCount, remainValue, currentPallets, bestSelection);

    if ( currentWeight + pallets[index].weight <= truck.capacity) {
        currentPallets[index] = true;
        backtrackingRecursion(truck, pallets, index + 1, currentValue + pallets[index].profit, currentWeight + pallets[index].weight,
            currentCount + 1, bestValue, bestCount, remainValue, currentPallets, bestSelection);
        currentPallets[index] = false;
    }
}

void backtrackingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::vector<int> remainValue(truck.availablePallets, 0);
    for (int i = pallets.size()-1; i >=0 ; i--) {
        remainValue[i] = remainValue[i + 1] + pallets[i].profit;
    }

    std::vector<bool> currentSelected(pallets.size());
    int bestValue = 0;
    int bestCount = truck.availablePallets + 1;
    backtrackingRecursion(truck, pallets, 0, 0, 0, 0, bestValue, bestCount, remainValue, currentSelected, selectedPallets);
}



void greedyApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {

    std::sort(pallets.begin(), pallets.end(),
        [](Pallet& pallet1, Pallet& pallet2) {return (double)(pallet1.profit) / pallet1.weight > (double)(pallet2.profit)/pallet2.weight; });

        
    int selectedPalletsWeightSum = 0;
    for (int i = 0; i < pallets.size(); i++) {
        if (pallets[i].weight + selectedPalletsWeightSum <= truck.capacity ) {
            selectedPallets[i] = true;
            selectedPalletsWeightSum += pallets[i].weight;
        }else {
            selectedPallets[i] = false;
        }
    }
}



void dynamicProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    int n = truck.availablePallets;
    int W = truck.capacity;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int wt = pallets[i - 1].weight;
        int val = pallets[i - 1].profit;

        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];

            if (wt <= w) {
                int newProfit = val + dp[i - 1][w - wt];

                if (newProfit > dp[i][w]) {
                    dp[i][w] = newProfit;
                }
            }
        }
    }

    int w = W;
    for (int i = n; i > 0 && w >= 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedPallets[i - 1] = true;
            w -= pallets[i - 1].weight;
        }
    }
}

void integerLinearProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    std::cout << "Integer Linear Programming Approach\n";
}