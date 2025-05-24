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
 * @details This function explores all possible combinations of pallets to find the optimal packing solution that maximizes profit while respecting the truck's weight capacity.
 * It uses bit manipulation to generate all subsets of pallets and checks each subset for its total weight and profit. This approach has a time complexity of O(2^n), where n is the number of pallets, making it suitable only for small datasets.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void bruteForceApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the backtracking approach for the pallet packing problem.
 * 
 * @details This function uses a backtracking algorithm to explore the solution space and choosing the best option. It recursively builds combinations of pallets, pruning branches that exceed the truck's weight capacity or that the remaining pallets will not reach the best solution found so far.
 * This approach is more efficient than brute force but still has a time complexity of O(2^n) in the worst case, but in practice, it is almost always way faster than the brute force due to pruning.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void backtrackingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the greedy approach for the pallet packing problem.
 * 
 * @details This function sorts the pallets based on their profit-to-weight ratio and iteratively selects pallets until the truck's weight capacity is reached. 
 * This approach is efficient with a time complexity of O(n log n) due to sorting, but it does not guarantee an optimal solution.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void greedyApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the dynamic programming approach for the pallet packing problem.
 * 
 * @details This function uses a dynamic programming table to store the maximum profit for each weight capacity and number of pallets. It builds the solution iteratively, ensuring that each pallet is considered only once.
 * This approach has a time complexity of O(nW), where n is the number of pallets and W is the truck's weight capacity. Even though it looks like a polynomial time complexity, it can still be computationally expensive for cases with a big capacity.
 * The weigth capacity is not related to the number of pallets, so it can be very high even though the number of pallets it's small, leading to a possible high running time for big capacities.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void dynamicProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);


/**
 * @brief Function to implement the integer linear programming approach for the pallet packing problem.
 * 
 * @details This function uses an external Python script to solve the pallet packing problem using integer linear programming. It generates an input file with the truck's capacity and pallets' data, runs the solver, and reads the output to determine which pallets are selected.
 * This approach is efficient and can handle larger datasets, but it requires Python and the appropriate libraries to be installed. The time complexity depends on the solver used, but it is generally efficient for practical use cases.
 * The Python script is located in the `SolverIlp` directory.
 * 
 * @param truck The truck structure containing truck data.
 * @param pallets A vector of pallets to be packed.
 * @param selectedPallets A vector of booleans indicating which pallets are selected.
 */
void integerLinearProgrammingApproach(Truck& truck, std::vector<Pallet>& pallets, std::vector<bool>& selectedPallets);

#endif // ALGORITHMS_H