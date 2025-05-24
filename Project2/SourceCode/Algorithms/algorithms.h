#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "truck.h"
#include "pallet.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>


/**
 * @file algorithms.h
 * @brief This file contains the declarations of various algorithms for solving the pallet packing problem.
 */

/**
 * @brief Function to implement the brute force approach for the pallet packing problem.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void bruteForceApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the backtracking approach for the pallet packing problem.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void backtrackingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the greedy approach for the pallet packing problem.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void greedyApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the dynamic programming approach for the pallet packing problem.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void dynamicProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the integer linear programming approach for the pallet packing problem.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void integerLinearProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);

#endif // ALGORITHMS_H