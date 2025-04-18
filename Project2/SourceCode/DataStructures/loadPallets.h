#include "pallet.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @file loadPallets.h
 * @brief Function declaration for loading pallets data from a CSV file.
 * 
 * This file contains the function declaration for reading pallets data from a CSV file and populating a vector of Pallet structs. 
 * The corresponding function implementation is in loadPallets.cpp.
 */

/**
 * @brief Loads Pallets data from a CSV file.
 * 
 * @param choice The dataset choice.
 * @param n_pallets The number of pallets to load.
 * @param pallets Reference to a vector of Pallet structures to be populated.
 * @return true if the pallets data was loaded successfully, false otherwise.
 */
bool loadPallets(int choice, int n_pallets, std::vector<Pallet>& pallets);