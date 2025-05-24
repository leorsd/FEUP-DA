#include "algorithms.h"

#include <algorithm>
#include <chrono>

/**
 * @file algorithms.cpp
 * @brief This file contains the implementations of various algorithms for solving the pallet packing problem declared in algorithms.h.
 */


void bruteForceApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets) {
    int n = pallets.size();
    int maxProfit = 0;
    int maxNumberOfPallets = 0;
    int maxFirstPallet = n + 1;
    std::vector<bool> bestCombination(n, false);

    for (int mask = 0; mask < (1 << n); mask++) {
        int currentWeight = 0;
        int currentProfit = 0;
        int currentNumberOfPallets = 0;
        int firstPallet = n + 1;
        std::vector<bool> currentCombination(n, false);

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (i<firstPallet) {
                    firstPallet = i;
                }
                currentNumberOfPallets++;
                currentWeight += pallets[i].weight;
                currentProfit += pallets[i].profit;
                currentCombination[i] = true;
            }
        }

        if (currentWeight <= truck.capacity && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestCombination = currentCombination;
        }else if (currentWeight <= truck.capacity && currentProfit == maxProfit) {
            if (currentNumberOfPallets < maxNumberOfPallets) {
                maxNumberOfPallets = currentNumberOfPallets;
                bestCombination = currentCombination;
            } else if (currentNumberOfPallets == maxNumberOfPallets && firstPallet < maxFirstPallet) {
                maxFirstPallet = firstPallet;
                bestCombination = currentCombination;
            }
        }
    }
    selectedPallets = bestCombination;
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

    std::ofstream out("../SolverIlp/input.txt");
    out << truck.capacity << " " << pallets.size() << "\n";
    for (const auto& p : pallets)
        out << p.weight << " " << p.profit << "\n";
    out.close();

    std::system("python3 ../SolverIlp/knapsack_solver.py");

    selectedPallets.assign(pallets.size(), false);
    std::ifstream in("../SolverIlp/output.txt");
    for (size_t i = 0; i < pallets.size(); ++i) {
        int val;
        in >> val;
        selectedPallets[i] = (val == 1);
    }
    in.close();
}