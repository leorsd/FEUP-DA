#ifndef DISPLAYRESULTS_H
#define DISPLAYRESULTS_H

#include <iostream>
#include <vector>
#include "truck.h"
#include "pallet.h"

/**
 * @file displayResults.h
 * @brief This file contains the declaration of the function to display the results of the algorithms.
 */

/**
 * @brief Function to display the results of the algorithm.
 * 
 * @param algorithm The algorithm used (1-5).
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 * @param optimalPallets A vector of booleans indicating which pallets are part of the optimal solution.
 * @param elapsedTime The time taken by the algorithm to execute.
 */
void displayAlgorithmResult(int algorithm, Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets, std::vector<bool>& optimalPallets, double elapsedTime);

#endif // DISPLAYRESULTS_H