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
 * @brief Function to display a message indicating that the input size is too big for the selected algorithm.
 *
 * @details This function informs the user that the input size is too big for the selected algorithm and suggests selecting a smaller input size.
 *          It also provides information about the maximum input size for the selected algorithm.
 * 
 * @param algorithm The algorithm used.
 * @param inputSize The size of the input.
 */
 void displayInputSizeToBig(int algorithm, int inputSize);

/**
 * @brief Function to display the results of the algorithm.
 * 
 * @details This function displays the results of the selected algorithm, including the algorithm used, the IDs of the selected pallets, their total weight and profit, and the running time of the algorithm used.
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